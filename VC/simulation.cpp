#include "simulation.h"
#include <iostream>

Simulation::Simulation() {
    cycleActuel = 0;
    ville = nullptr;
    initialiserEvenements();
}

Simulation::Simulation(Ville* v) {
    cycleActuel = 0;
    ville = v;
    initialiserEvenements();
}

void Simulation::initialiserEvenements() {
    Evenement e1 = {"Nuee de Pigeons", "Une nuee de pigeons geants envahit la ville!", -15, 0, 0, 5, -500.0};
    evenements.push_back(e1);

    Evenement e2 = {"Panne de Courant", "Une panne de courant fait grimper la consommation!", -10, 0, -50, 0, -200.0};
    evenements.push_back(e2);

    Evenement e3 = {"Greve des Jardiniers", "Les jardiniers sont en greve!", -20, 0, 0, 3, 0.0};
    evenements.push_back(e3);

    Evenement e4 = {"Festival de la Ville", "Un festival ameliore le moral!", 25, -10, -20, -5, -1000.0};
    evenements.push_back(e4);

    Evenement e5 = {"Subvention Gouvernementale", "La ville recoit une aide financiere!", 10, 50, 50, 0, 5000.0};
    evenements.push_back(e5);

    Evenement e6 = {"Journee Ensoleille", "Beau temps, tout le monde est heureux!", 15, 0, 0, -3, 0.0};
    evenements.push_back(e6);
}

void Simulation::demarrerCycle() {
    cycleActuel++;
    dernierEvenement = {"", "", 0, 0.0, 0.0, 0.0, 0.0};
    cout << "\n=== Debut du Cycle " << cycleActuel << " ===" << endl;

    if (ville != nullptr) {
        double productionEau = 10.0;
        double productionElec = 15.0;

        ville->mettreAJourRessources(productionEau, productionElec);

        cout << "Ressources mises a jour." << endl;
        cout << "Eau: " << ville->getEau() << endl;
        cout << "Electricite: " << ville->getElectricite() << endl;
        cout << "Pollution: " << ville->getPollution() << endl;
        cout << "Satisfaction: " << ville->getSatisfaction() << "%" << endl;
    }
}

void Simulation::terminerCycle() {
    cout << "=== Fin du Cycle " << cycleActuel << " ===" << endl;

    int chance = rand() % 100;
    if (chance < 70) {
        declencherEvenement();
    }
}

Evenement Simulation::declencherEvenement() {
    Evenement vide = {"", "", 0, 0, 0, 0, 0.0};

    if (evenements.size() == 0 || ville == nullptr) {
        return vide;
    }

    int index = rand() % evenements.size();
    Evenement evt = evenements[index];

    cout << "\n    EVENEMENT: " << evt.nom << " ***" << endl;
    cout << evt.description << endl;

    ville->ajouterBonusSatisfaction(evt.impactSatisfaction);
    ville->ajouterBonusPollution(evt.impactPollution);
    ville->ajouterBudget(evt.impactBudget);

    double nouvelleEau = ville->getEau() + evt.impactEau;
    if (nouvelleEau < 0.0) nouvelleEau = 0.0;
    ville->setEau(nouvelleEau);

    double nouvelleElec = ville->getElectricite() + evt.impactElectricite;
    if (nouvelleElec < 0.0) nouvelleElec = 0.0;
    ville->setElectricite(nouvelleElec);

    
    ville->calculerSatisfaction();
    ville->calculerPollutionTotale();

    cout << "Nouvelle Satisfaction: " << ville->getSatisfaction() << "%" << endl;
    cout << "Nouveau Budget: " << ville->getBudget() << endl;

    dernierEvenement = evt;
    return evt;
}

