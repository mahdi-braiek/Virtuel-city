/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftVBox;
    QGroupBox *batimentGroup;
    QHBoxLayout *batimentSplit;
    QListWidget *listeBatiments;
    QPlainTextEdit *plainTextEdit_batimentDetails;
    QGroupBox *eventsGroup;
    QVBoxLayout *eventsVBox;
    QHBoxLayout *eventsSplit;
    QListWidget *listWidget_events;
    QPlainTextEdit *plainTextEdit_eventDetails;
    QGroupBox *logGroup;
    QVBoxLayout *logVBox;
    QTextEdit *logText;
    QHBoxLayout *buttonsHBox;
    QPushButton *btnAjouterMaison;
    QPushButton *btnAjouterUsine;
    QPushButton *btnAjouterParc;
    QPushButton *btnSupprimer;
    QPushButton *btnModify;
    QVBoxLayout *rightVBox;
    QHBoxLayout *cycleHBox;
    QPushButton *btnCycle;
    QPushButton *btnRunNCycles;
    QGroupBox *statusGroup;
    QVBoxLayout *statusVBox;
    QLabel *label_name;
    QLabel *labelBudget;
    QLabel *labelPopulation;
    QLabel *labelSatisfaction;
    QLabel *labelEau;
    QLabel *labelElectricite;
    QLabel *labelPollution;
    QLabel *labelCycle;
    QHBoxLayout *bottomButtonsHBox;
    QPushButton *btnLoad;
    QPushButton *btnSave;
    QPushButton *btnQuit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(946, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget { background-color: #1a1b26; color: #a9b1d6; font-family: 'Segoe UI', 'San Francisco', sans-serif; }\n"
"\n"
"QMainWindow, QDialog { background-color: #1a1b26; }\n"
"\n"
"QPushButton { \n"
"  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2e3440, stop:1 #24283b); \n"
"  border: 1px solid #414868; border-radius: 8px; padding: 10px 18px; color: #c0caf5; \n"
"  font-weight: 600; font-size: 13px; \n"
"} \n"
"QPushButton:hover { background: #414868; border-color: #7aa2f7; color: #fff; } \n"
"QPushButton:pressed { background: #3d59a1; } \n"
"\n"
"#btnCycle { \n"
"  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3d59a1, stop:1 #7aa2f7); \n"
"  color: white; font-size: 14px; font-weight: bold; border: none; min-height: 40px; padding: 0 25px; \n"
"} \n"
"#btnCycle:hover { background: #7aa2f7; } \n"
"\n"
"QListWidget, QPlainTextEdit, QTextEdit, QLineEdit, QListView { \n"
"  background-color: #24283b; border: 1px solid #414868; border-radius: 12px; \n"
"  padding: 10px; color: #c0caf5; s"
                        "election-background-color: #3d59a1; \n"
"} \n"
"QListWidget::item { padding: 10px; border-bottom: 1px solid #2f334d; margin: 2px 0; } \n"
"QListWidget::item:selected { background-color: #3d59a1; border-radius: 8px; color: white; } \n"
"\n"
"QGroupBox { \n"
"  background-color: #1f2335; border: 1px solid #414868; border-radius: 15px; \n"
"  margin-top: 25px; padding-top: 20px; font-weight: bold; color: #7aa2f7; \n"
"} \n"
"QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px; background-color: #1a1b26; } \n"
"\n"
"QLabel { background-color: transparent; color: #a9b1d6; font-size: 14px; } \n"
"#label_name { font-size: 20px; color: #7aa2f7; font-weight: 900; } \n"
"\n"
"QScrollBar:vertical { border: none; background: #1a1b26; width: 8px; margin: 0; } \n"
"QScrollBar::handle:vertical { background: #414868; min-height: 20px; border-radius: 4px; } \n"
"QScrollBar::handle:vertical:hover { background: #7aa2f7; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        leftVBox = new QVBoxLayout();
        leftVBox->setObjectName("leftVBox");
        batimentGroup = new QGroupBox(centralwidget);
        batimentGroup->setObjectName("batimentGroup");
        batimentSplit = new QHBoxLayout(batimentGroup);
        batimentSplit->setObjectName("batimentSplit");
        listeBatiments = new QListWidget(batimentGroup);
        listeBatiments->setObjectName("listeBatiments");

        batimentSplit->addWidget(listeBatiments);

        plainTextEdit_batimentDetails = new QPlainTextEdit(batimentGroup);
        plainTextEdit_batimentDetails->setObjectName("plainTextEdit_batimentDetails");
        plainTextEdit_batimentDetails->setReadOnly(true);

        batimentSplit->addWidget(plainTextEdit_batimentDetails);


        leftVBox->addWidget(batimentGroup);

        eventsGroup = new QGroupBox(centralwidget);
        eventsGroup->setObjectName("eventsGroup");
        eventsVBox = new QVBoxLayout(eventsGroup);
        eventsVBox->setObjectName("eventsVBox");
        eventsSplit = new QHBoxLayout();
        eventsSplit->setObjectName("eventsSplit");
        listWidget_events = new QListWidget(eventsGroup);
        listWidget_events->setObjectName("listWidget_events");

        eventsSplit->addWidget(listWidget_events);

        plainTextEdit_eventDetails = new QPlainTextEdit(eventsGroup);
        plainTextEdit_eventDetails->setObjectName("plainTextEdit_eventDetails");
        plainTextEdit_eventDetails->setReadOnly(true);

        eventsSplit->addWidget(plainTextEdit_eventDetails);


        eventsVBox->addLayout(eventsSplit);


        leftVBox->addWidget(eventsGroup);

        logGroup = new QGroupBox(centralwidget);
        logGroup->setObjectName("logGroup");
        logVBox = new QVBoxLayout(logGroup);
        logVBox->setObjectName("logVBox");
        logText = new QTextEdit(logGroup);
        logText->setObjectName("logText");
        logText->setReadOnly(true);

        logVBox->addWidget(logText);


        leftVBox->addWidget(logGroup);

        buttonsHBox = new QHBoxLayout();
        buttonsHBox->setObjectName("buttonsHBox");
        btnAjouterMaison = new QPushButton(centralwidget);
        btnAjouterMaison->setObjectName("btnAjouterMaison");

        buttonsHBox->addWidget(btnAjouterMaison);

        btnAjouterUsine = new QPushButton(centralwidget);
        btnAjouterUsine->setObjectName("btnAjouterUsine");

        buttonsHBox->addWidget(btnAjouterUsine);

        btnAjouterParc = new QPushButton(centralwidget);
        btnAjouterParc->setObjectName("btnAjouterParc");

        buttonsHBox->addWidget(btnAjouterParc);

        btnSupprimer = new QPushButton(centralwidget);
        btnSupprimer->setObjectName("btnSupprimer");

        buttonsHBox->addWidget(btnSupprimer);

        btnModify = new QPushButton(centralwidget);
        btnModify->setObjectName("btnModify");

        buttonsHBox->addWidget(btnModify);


        leftVBox->addLayout(buttonsHBox);


        horizontalLayout->addLayout(leftVBox);

        rightVBox = new QVBoxLayout();
        rightVBox->setObjectName("rightVBox");
        cycleHBox = new QHBoxLayout();
        cycleHBox->setObjectName("cycleHBox");
        btnCycle = new QPushButton(centralwidget);
        btnCycle->setObjectName("btnCycle");

        cycleHBox->addWidget(btnCycle);

        btnRunNCycles = new QPushButton(centralwidget);
        btnRunNCycles->setObjectName("btnRunNCycles");

        cycleHBox->addWidget(btnRunNCycles);


        rightVBox->addLayout(cycleHBox);

        statusGroup = new QGroupBox(centralwidget);
        statusGroup->setObjectName("statusGroup");
        statusVBox = new QVBoxLayout(statusGroup);
        statusVBox->setObjectName("statusVBox");
        label_name = new QLabel(statusGroup);
        label_name->setObjectName("label_name");

        statusVBox->addWidget(label_name);

        labelBudget = new QLabel(statusGroup);
        labelBudget->setObjectName("labelBudget");

        statusVBox->addWidget(labelBudget);

        labelPopulation = new QLabel(statusGroup);
        labelPopulation->setObjectName("labelPopulation");

        statusVBox->addWidget(labelPopulation);

        labelSatisfaction = new QLabel(statusGroup);
        labelSatisfaction->setObjectName("labelSatisfaction");

        statusVBox->addWidget(labelSatisfaction);

        labelEau = new QLabel(statusGroup);
        labelEau->setObjectName("labelEau");

        statusVBox->addWidget(labelEau);

        labelElectricite = new QLabel(statusGroup);
        labelElectricite->setObjectName("labelElectricite");

        statusVBox->addWidget(labelElectricite);

        labelPollution = new QLabel(statusGroup);
        labelPollution->setObjectName("labelPollution");

        statusVBox->addWidget(labelPollution);

        labelCycle = new QLabel(statusGroup);
        labelCycle->setObjectName("labelCycle");

        statusVBox->addWidget(labelCycle);


        rightVBox->addWidget(statusGroup);

        bottomButtonsHBox = new QHBoxLayout();
        bottomButtonsHBox->setObjectName("bottomButtonsHBox");
        btnLoad = new QPushButton(centralwidget);
        btnLoad->setObjectName("btnLoad");

        bottomButtonsHBox->addWidget(btnLoad);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");

        bottomButtonsHBox->addWidget(btnSave);

        btnQuit = new QPushButton(centralwidget);
        btnQuit->setObjectName("btnQuit");

        bottomButtonsHBox->addWidget(btnQuit);


        rightVBox->addLayout(bottomButtonsHBox);


        horizontalLayout->addLayout(rightVBox);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VirtualCity - GUI", nullptr));
        batimentGroup->setTitle(QCoreApplication::translate("MainWindow", "B\303\242timents de la ville", nullptr));
        plainTextEdit_batimentDetails->setPlaceholderText(QCoreApplication::translate("MainWindow", "Cliquez sur un b\303\242timent pour voir ses d\303\251tails...", nullptr));
        eventsGroup->setTitle(QCoreApplication::translate("MainWindow", "Ev\303\251nements", nullptr));
        logGroup->setTitle(QCoreApplication::translate("MainWindow", "Journal", nullptr));
        btnAjouterMaison->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240 Ajouter Maison", nullptr));
        btnAjouterUsine->setText(QCoreApplication::translate("MainWindow", "\360\237\217\255 Ajouter Usine", nullptr));
        btnAjouterParc->setText(QCoreApplication::translate("MainWindow", "\360\237\214\263 Ajouter Parc", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer", nullptr));
        btnModify->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        btnCycle->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200 D\303\251marrer Cycle", nullptr));
        btnRunNCycles->setText(QCoreApplication::translate("MainWindow", "\342\217\251 Lancer N Cycles", nullptr));
        statusGroup->setTitle(QCoreApplication::translate("MainWindow", "Etat de la ville", nullptr));
        label_name->setText(QCoreApplication::translate("MainWindow", "Ville: -", nullptr));
        labelBudget->setText(QCoreApplication::translate("MainWindow", "Budget: -", nullptr));
        labelPopulation->setText(QCoreApplication::translate("MainWindow", "Population: -", nullptr));
        labelSatisfaction->setText(QCoreApplication::translate("MainWindow", "Satisfaction: -", nullptr));
        labelEau->setText(QCoreApplication::translate("MainWindow", "Eau: -", nullptr));
        labelElectricite->setText(QCoreApplication::translate("MainWindow", "Electricit\303\251: -", nullptr));
        labelPollution->setText(QCoreApplication::translate("MainWindow", "Pollution: -", nullptr));
        labelCycle->setText(QCoreApplication::translate("MainWindow", "Cycle: 0", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 Charger", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 Sauvegarder", nullptr));
        btnQuit->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Quitter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
