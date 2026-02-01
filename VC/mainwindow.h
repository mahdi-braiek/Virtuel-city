#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QPushButton>
# include <map>
# include "ville.h"
# include "simulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void supprimerBatiment();
    void demarrerCycle();
    void runNCycles();
    void saveToFile();
    void ouvrirDialogCharger();
    void loadFromFile(const QString& path);
    void afficherDetails();
    void ouvrirDialogMaison();
    void ouvrirDialogUsine();
    void ouvrirDialogParc();
    void ouvrirDialogModifier();
    void afficherEvenementDetails(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;

    Ville* ville;
    Simulation* simulation;

    void mettreAJourAffichage();
    void ajouterLog(const QString& message);
    void afficherDialog(QString typePreSelectionne);
    std::map<QString, Evenement> historiqueEvenements;
};

#endif
