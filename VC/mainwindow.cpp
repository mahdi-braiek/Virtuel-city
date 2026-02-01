#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maison.h"
#include "usine.h"
#include "parc.h"
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>


static QString defaultSavePath();



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ville = new Ville("Ma Ville Virtuelle", 500000.0);
    simulation = new Simulation(ville);
    loadFromFile(defaultSavePath());
    ui->label_name->setText("🏙️ " + QString::fromStdString(ville->getNom()));

    connect(ui->btnAjouterMaison, &QPushButton::clicked, this, &MainWindow::ouvrirDialogMaison);
    connect(ui->btnAjouterUsine, &QPushButton::clicked, this, &MainWindow::ouvrirDialogUsine);
    connect(ui->btnAjouterParc, &QPushButton::clicked, this, &MainWindow::ouvrirDialogParc);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerBatiment);
    connect(ui->btnCycle, &QPushButton::clicked, this, &MainWindow::demarrerCycle);
    connect(ui->btnRunNCycles, &QPushButton::clicked, this, &MainWindow::runNCycles);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::ouvrirDialogCharger);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(ui->btnModify, &QPushButton::clicked, this, &MainWindow::ouvrirDialogModifier);
    connect(ui->listeBatiments, &QListWidget::currentItemChanged, this, &MainWindow::afficherDetails);
    connect(ui->btnQuit, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    if (ui->listWidget_events) {
        connect(ui->listWidget_events, &QListWidget::itemClicked, this, &MainWindow::afficherEvenementDetails);
    }

    ajouterLog("Bienvenue dans VirtualCity!");
    ajouterLog("Construisez votre ville et gerez ses ressources.");

    mettreAJourAffichage();
}

MainWindow::~MainWindow()
{
    delete simulation;
    delete ville;
    delete ui;
}

void MainWindow::ouvrirDialogMaison()
{
    afficherDialog("Maison");
}

void MainWindow::ouvrirDialogUsine()
{
    afficherDialog("Usine");
}

void MainWindow::ouvrirDialogParc()
{
    afficherDialog("Parc");
}

void MainWindow::supprimerBatiment()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erreur", "Selectionnez un batiment a supprimer");
        return;
    }

    int id = -1;
    QVariant d = item->data(Qt::UserRole);
    if (d.isValid()) id = d.toInt();
    if (id == -1) {
        QString text = item->text();
        id = text.split(" ")[1].toInt();
    }

    if (ville->supprimerBatiment(id)) {
        ajouterLog("Batiment #" + QString::number(id) + " supprime");
        mettreAJourAffichage();
    }
}

void MainWindow::demarrerCycle()
{
    simulation->demarrerCycle();
    simulation->terminerCycle();
    ajouterLog("=== Cycle " + QString::number(simulation->getCycleActuel()) + " termine ===");
    mettreAJourAffichage();

    if (ui->listWidget_events) {
        Evenement evt = simulation->getDernierEvenement();
        if (evt.nom != "") {
            QString titre = QString::fromStdString(evt.nom) + " (Cycle " + QString::number(simulation->getCycleActuel()) + ")";
            historiqueEvenements[titre] = evt;
            ui->listWidget_events->addItem(titre);
            ui->listWidget_events->setCurrentRow(ui->listWidget_events->count() - 1);
            ajouterLog("⚠️ Événement: " + titre);
        }
    }
}

void MainWindow::runNCycles()
{
    bool ok = false;
    int n = QInputDialog::getInt(this, "Lancer N cycles", "Nombre de cycles:", 10, 1, 100000, 1, &ok);
    if (!ok) return;

    for (int i = 0; i < n; ++i) {
        simulation->demarrerCycle();
        simulation->terminerCycle();
        ajouterLog("=== Cycle " + QString::number(simulation->getCycleActuel()) + " termine ===");
        mettreAJourAffichage();
        Evenement evt = simulation->getDernierEvenement();
        QString eventStr = evt.nom.empty() ? "" : QString::fromStdString(evt.nom);
        if (!eventStr.isEmpty()) {
            if (ui->listWidget_events) {
                QString titre = eventStr + " (Cycle " + QString::number(simulation->getCycleActuel()) + ")";
                historiqueEvenements[titre] = evt;
                ui->listWidget_events->addItem(titre);
                ui->listWidget_events->setCurrentRow(ui->listWidget_events->count() - 1);
            }
            ajouterLog("⚠️ Événement: " + eventStr);
        }
    }
}

static QString defaultSavePath()
{
    return QCoreApplication::applicationDirPath() + "/save_state.txt";
}

void MainWindow::saveToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Sauvegarder l'état", "", "Fichiers texte (*.txt);;Tous les fichiers (*)");
    if (filePath.isEmpty()) return;

    QString content;
    QTextStream mem(&content);
    mem << "Ville:" << QString::fromStdString(ville->getNom()) << "\n";
    mem << "Cycle:" << simulation->getCycleActuel() << "\n";
    mem << "Budget:" << ville->getBudget() << "\n";
    mem << "Eau:" << ville->getEau() << "\n";
    mem << "Electricite:" << ville->getElectricite() << "\n";
    mem << "Pollution:" << ville->getPollution() << "\n";
    mem << "BonusSatisfaction:" << ville->getBonusSatisfaction() << "\n";
    mem << "BonusPollution:" << ville->getBonusPollution() << "\n";
    mem << "Satisfaction:" << ville->getSatisfaction() << "\n";
    mem << "ProchainId:" << ville->getProchainId() << "\n";
    mem << "Batiments:" << "\n";
    vector<Batiment*>& bats = ville->getBatiments();
    for (int i = 0; i < bats.size(); ++i) {
        Batiment* b = bats[i];
        string type = b->getType();
        if (type == "Habitation") {
            mem << "Maison," << b->getId() << "," << QString::fromStdString(b->getNom()) << "," << b->getCapaciteHabitants() << "," << b->getHabitantsActuels() << "\n";
        } else if (type == "Ressource") {
            mem << "Usine," << b->getId() << "," << QString::fromStdString(b->getNom()) << "\n";
        } else if (type == "Service") {
            mem << "Parc," << b->getId() << "," << QString::fromStdString(b->getNom()) << "," << b->getSurface() << "\n";
        } else {
            mem << "Batiment," << b->getId() << "," << QString::fromStdString(b->getNom()) << "\n";
        }
    }

    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour écriture.");
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();

    QString defaultPath = defaultSavePath();
    QDir d;
    QString defDir = QFileInfo(defaultPath).path();
    if (!d.exists(defDir)) d.mkpath(defDir);
    QFile defF(defaultPath);
    if (defF.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream o(&defF);
        o << content;
        defF.close();
    }

    ajouterLog("Etat sauvegardé dans: " + filePath);
}

void MainWindow::ouvrirDialogCharger()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Charger l'état", "", "Fichiers texte (*.txt);;Tous les fichiers (*)");
    if (filePath.isEmpty()) return;
    
    loadFromFile(filePath);
    ajouterLog("Etat chargé depuis: " + filePath);
}

void MainWindow::loadFromFile(const QString& path)
{
    QFile file(path);
    if (!file.exists()) return;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    vector<Batiment*>& bats = ville->getBatiments();
    for (size_t i = 0; i < bats.size(); ++i) delete bats[i];
    bats.clear();

    QString line;
    int maxId = 0;
    while (!in.atEnd()) {
        line = in.readLine();
        if (line.startsWith("Ville:")) {
            ville->setNom(line.mid(6).toStdString());
            ui->label_name->setText("🏙️ " + QString::fromStdString(ville->getNom()));
        } else if (line.startsWith("Cycle:")) {
            simulation->setCycleActuel(line.mid(6).toInt());
        } else if (line.startsWith("Budget:")) {
            ville->setBudget(line.mid(7).toDouble());
        } else if (line.startsWith("Eau:")) {
            ville->setEau(line.mid(4).toDouble());
        } else if (line.startsWith("Electricite:")) {
            ville->setElectricite(line.mid(12).toDouble());
        } else if (line.startsWith("Pollution:")) {
            ville->setPollution(line.mid(10).toDouble());
        } else if (line.startsWith("BonusSatisfaction:")) {
            ville->ajouterBonusSatisfaction(line.mid(18).toDouble() - ville->getBonusSatisfaction());
        } else if (line.startsWith("BonusPollution:")) {
            ville->ajouterBonusPollution(line.mid(15).toDouble() - ville->getBonusPollution());
        } else if (line.startsWith("Satisfaction:")) {
            ville->setSatisfaction(line.mid(13).toInt());
        } else if (line.startsWith("ProchainId:")) {
        } else if (line.startsWith("Maison,")) {
            QStringList parts = line.split(',');
            if (parts.size() >= 5) {
                int id = parts[1].toInt();
                Maison* m = new Maison(id, parts[2].toStdString(), parts[3].toInt());
                m->setHabitantsActuels(parts[4].toInt());
                bats.push_back(m);
                if (id > maxId) maxId = id;
            }
        } else if (line.startsWith("Usine,")) {
            QStringList parts = line.split(',');
            if (parts.size() >= 3) {
                int id = parts[1].toInt();
                QString name = parts[2];
                Usine* u = new Usine(id, name.toStdString());
                bats.push_back(u);
                if (id > maxId) maxId = id;
            }
        } else if (line.startsWith("Parc,")) {
            QStringList parts = line.split(',');
            if (parts.size() >= 4) {
                int id = parts[1].toInt();
                QString name = parts[2];
                double surf = parts[3].toDouble();
                Parc* p = new Parc(id, name.toStdString(), surf);
                bats.push_back(p);
                if (id > maxId) maxId = id;
            }
        }
    }

    
    while (ville->getProchainId() <= maxId) {
        ville->incrementerProchainId();
    }

    ville->calculerPopulationTotale();
    ville->calculerPollutionTotale();
    ville->calculerSatisfaction();

    file.close();
    mettreAJourAffichage();
}

void MainWindow::afficherDialog(QString typePreSelectionne)
{
    bool ok;
    QString defaultName = typePreSelectionne + " #" + QString::number(ville->getProchainId());
    QString name = QInputDialog::getText(this, "Ajouter " + typePreSelectionne, 
                                         "Nom du batiment:", QLineEdit::Normal, 
                                         defaultName, &ok);
    if (!ok) return;
    if (name.isEmpty()) name = defaultName;

    int id = ville->getProchainId();
    if (typePreSelectionne == "Maison") {
        int cap = QInputDialog::getInt(this, "Ajouter Maison", "Capacité (habitants):", 4, 1, 1000, 1, &ok);
        if (ok) {
            ville->ajouterBatiment(new Maison(id, name.toStdString(), cap));
        } else return;
    } else if (typePreSelectionne == "Usine") {
        ville->ajouterBatiment(new Usine(id, name.toStdString()));
    } else if (typePreSelectionne == "Parc") {
        double surf = QInputDialog::getDouble(this, "Ajouter Parc", "Surface (m2):", 100.0, 1.0, 1000000.0, 1, &ok);
        if (ok) {
            ville->ajouterBatiment(new Parc(id, name.toStdString(), surf));
        } else return;
    }

    ville->incrementerProchainId();
    ajouterLog(typePreSelectionne + " construite (ID: " + QString::number(id) + ")");
    mettreAJourAffichage();
}

void MainWindow::ouvrirDialogModifier()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erreur", "Selectionnez un batiment a modifier");
        return;
    }
    int id = -1;
    QVariant d = item->data(Qt::UserRole);
    if (d.isValid()) id = d.toInt();
    if (id == -1) {
        QString text = item->text();
        id = text.split(" ")[1].toInt();
    }
    Batiment* b = ville->trouverBatiment(id);
    if (!b) return;

    bool ok;
    QString name = QInputDialog::getText(this, "Modifier Batiment", 
                                         "Nouveau nom:", QLineEdit::Normal, 
                                         QString::fromStdString(b->getNom()), &ok);
    if (!ok) return;
    b->setNom(name.toStdString());

    string type = b->getType();
    if (type == "Habitation") {
        Maison* m = dynamic_cast<Maison*>(b);
        if (m) {
            int cap = QInputDialog::getInt(this, "Modifier Maison", "Nouvelle capacité:", m->getCapaciteHabitants(), 1, 1000, 1, &ok);
            if (ok) m->setCapaciteHabitants(cap);
        }
    } else if (type == "Service") {
        Parc* p = dynamic_cast<Parc*>(b);
        if (p) {
            double surf = QInputDialog::getDouble(this, "Modifier Parc", "Nouvelle surface:", p->getSurface(), 1.0, 1000000.0, 1, &ok);
            if (ok) p->setSurface(surf);
        }
    }

    ajouterLog("Batiment #" + QString::number(id) + " modifié");
    mettreAJourAffichage();
}

void MainWindow::afficherEvenementDetails(QListWidgetItem* item)
{
    if (!item || !ui->plainTextEdit_eventDetails) return;
    QString title = item->text();
    
    if (historiqueEvenements.count(title)) {
        Evenement evt = historiqueEvenements[title];
        QString det = "━━━━━━━━━━━━━━━━━━━━━\n";
        det += " 🚨 ÉVÉNEMENT : " + QString::fromStdString(evt.nom).toUpper() + "\n";
        det += "━━━━━━━━━━━━━━━━━━━━━\n\n";
        det += "📝 " + QString::fromStdString(evt.description) + "\n\n";
        
        det += "� IMPACTS SUR LA VILLE\n";
        det += "─────────────────────\n";
        det += "😊 Satisfaction :   " + (evt.impactSatisfaction >= 0 ? QString("+") : QString("")) + QString::number(evt.impactSatisfaction) + "%\n";
        det += "💧 Eau          :   " + (evt.impactEau >= 0 ? QString("+") : QString("")) + QString::number(evt.impactEau) + " L\n";
        det += "⚡ Électricité  :   " + (evt.impactElectricite >= 0 ? QString("+") : QString("")) + QString::number(evt.impactElectricite) + " kWh\n";
        det += "☁️ Pollution    :   " + (evt.impactPollution >= 0 ? QString("+") : QString("")) + QString::number(evt.impactPollution) + "\n";
        
        ui->plainTextEdit_eventDetails->setPlainText(det);
    } else {
        ui->plainTextEdit_eventDetails->clear();
    }
}

void MainWindow::afficherDetails()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item || !ui->plainTextEdit_batimentDetails) return;

    int id = -1;
    QVariant d = item->data(Qt::UserRole);
    if (d.isValid()) id = d.toInt();
    
    if (id == -1) {
        QString text = item->text();
        id = text.split(" ")[1].toInt();
    }

    Batiment* batiment = ville->trouverBatiment(id);
    if (batiment != nullptr) {
        QString details = "━━━━━━━━━━━━━━━━━━━━━\n";
        details += " �️ " + QString::fromStdString(batiment->getNom()).toUpper() + "\n";
        details += "━━━━━━━━━━━━━━━━━━━━━\n\n";
        details += "� ID      : " + QString::number(batiment->getId()) + "\n";
        details += "🧩 Type    : " + QString::fromStdString(batiment->getType()) + "\n\n";
        
        details += "� RESSOURCES & CONSO.\n";
        details += "─────────────────────\n";
        details += "💧 Eau     : " + QString::number(batiment->getConsommationEau()) + " L\n";
        details += "⚡ Élec    : " + QString::number(batiment->getConsommationElectricite()) + " kWh\n";
        details += "😊 Bonheur : " + QString::number(batiment->getEffetSatisfaction()) + "\n\n";

        QString type = QString::fromStdString(batiment->getType());
        if (type == "Habitation") {
            details += "🏠 CAPACITÉ HABITANTS\n";
            details += "─────────────────────\n";
            details += "👥 Max     : " + QString::number(batiment->getCapaciteHabitants()) + "\n";
            details += "👨‍👩‍👧‍👦 Actuel  : " + QString::number(batiment->getHabitantsActuels()) + "\n";
        } else if (type == "Ressource") {
            details += "🏭 PRODUCTION\n";
            details += "─────────────────────\n";
            details += "📦 Quantité: " + QString::number(batiment->getCapaciteHabitants()) + "\n"; // On peut ajouter getProduction si besoin, pour l'instant on garde la logique
            details += "☁️ Pollution: " + QString::number(batiment->getPollution()) + "\n";
        } else if (type == "Service") {
            details += "🌳 ESPACE VERT\n";
            details += "─────────────────────\n";
            details += "📐 Surface : " + QString::number(batiment->getSurface()) + " m2\n";
            details += "✨ Bien-être: " + QString::number(batiment->getCapaciteHabitants()) + "\n"; // On simplifie
        }

        ui->plainTextEdit_batimentDetails->setPlainText(details);
    } else {
        ui->plainTextEdit_batimentDetails->clear();
    }
}

void MainWindow::mettreAJourAffichage()
{
    ui->labelCycle->setText("📅 Cycle: " + QString::number(simulation->getCycleActuel()));
    ui->labelBudget->setText("💰 Budget: " + QString::number(ville->getBudget(), 'f', 0) + " $");
    ui->labelPopulation->setText("👥 Population: " + QString::number(ville->getPopulation()));
    
    int sat = ville->getSatisfaction();
    QString satEmoji = sat >= 70 ? "😊" : (sat >= 40 ? "😐" : "😫");
    ui->labelSatisfaction->setText(satEmoji + " Satisfaction: " + QString::number(sat) + "%");
    
    ui->labelEau->setText("💧 Eau: " + QString::number(ville->getEau(), 'f', 1) + " L");
    ui->labelElectricite->setText("⚡ Électricité: " + QString::number(ville->getElectricite(), 'f', 1) + " kWh");
    ui->labelPollution->setText("☁️ Pollution: " + QString::number(ville->getPollution(), 'f', 1));

    int selectedId = -1;
    QListWidgetItem* curr = ui->listeBatiments->currentItem();
    if (curr) selectedId = curr->data(Qt::UserRole).toInt();

    ui->listeBatiments->clear();
    vector<Batiment*>& batiments = ville->getBatiments();
    for (int i = 0; i < batiments.size(); i++) {
        Batiment* b = batiments[i];
        QString name = QString::fromStdString(b->getNom());
        QString type = QString::fromStdString(b->getType());
        QString displayType;
        if (type == "Habitation") displayType = "🏠 Maison";
        else if (type == "Ressource") displayType = "🏭 Usine";
        else if (type == "Service") {
            displayType = "🌳 Parc";
        } else {
            displayType = type;
        }

        QString line = name + " (" + displayType + ")";

        QListWidgetItem* item = new QListWidgetItem(line);
        item->setData(Qt::UserRole, b->getId());
        item->setToolTip("ID " + QString::number(b->getId()));
        ui->listeBatiments->addItem(item);

        if (b->getId() == selectedId) {
            ui->listeBatiments->setCurrentItem(item);
        }
    }

    if (!ui->listeBatiments->currentItem() && ui->plainTextEdit_batimentDetails) {
        ui->plainTextEdit_batimentDetails->clear();
    }

    if (sat >= 70) {
        ui->labelSatisfaction->setStyleSheet("color: #a6e3a1; font-weight: bold;");
    } else if (sat >= 40) {
        ui->labelSatisfaction->setStyleSheet("color: #f9e2af; font-weight: bold;");
    } else {
        ui->labelSatisfaction->setStyleSheet("color: #f38ba8; font-weight: bold;");
    }
}

void MainWindow::ajouterLog(const QString& message)
{
    ui->logText->append("ℹ️ " + message);
}
