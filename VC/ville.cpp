#include "ville.h"
#include <iostream>
#include "maison.h"
#include "usine.h"
#include "parc.h"

Ville::Ville() {
    nom = "";
    budget = 0.0;
    population = 0;
    satisfaction = 50;
    eau = 1000.0;
    electricite = 1000.0;
    pollution = 0.0;
    bonusSatisfaction = 0.0;
    bonusPollution = 0.0;
    prochainId = 1;
}

Ville::Ville(string n, double budgetInit) {
    nom = n;
    budget = budgetInit;
    population = 0;
    satisfaction = 50;
    eau = 1000.0;
    electricite = 1000.0;
    pollution = 0.0;
    bonusSatisfaction = 0.0;
    bonusPollution = 0.0;
    prochainId = 1;
}

Ville::~Ville() {
    for (int i = 0; i < batiments.size(); i++) {
        delete batiments[i];
    }
    batiments.clear();
}

void Ville::ajouterBatiment(Batiment* batiment) {
    if (budget >= batiment->getCoutConstruction()) {
        batiments.push_back(batiment);
        budget -= batiment->getCoutConstruction();
        batiment->mettreAJour();
        calculerPopulationTotale();
        calculerPollutionTotale();
        calculerSatisfaction();
        cout << "Batiment " << batiment->getNom() << " construit!" << endl;
    } else {
        cout << "Budget insuffisant!" << endl;
    }
}

bool Ville::supprimerBatiment(int id) {
    for (int i = 0; i < batiments.size(); i++) {
        if (batiments[i]->getId() == id) {
            budget += batiments[i]->getCoutConstruction() * 0.5;
            
            delete batiments[i];
            batiments.erase(batiments.begin() + i);
            calculerPopulationTotale();
            calculerPollutionTotale();
            calculerSatisfaction();
            return true;
        }
    }
    return false;
}

Batiment* Ville::trouverBatiment(int id) {
    for (int i = 0; i < batiments.size(); i++) {
        if (batiments[i]->getId() == id) {
            return batiments[i];
        }
    }
    return nullptr;
}

void Ville::calculerConsommationTotale(double& totalEau, double& totalElec) {
    totalEau = 0.0;
    totalElec = 0.0;
    for (int i = 0; i < batiments.size(); i++) {
        totalEau += batiments[i]->getConsommationEau();
        totalElec += batiments[i]->getConsommationElectricite();
    }
}

void Ville::calculerPopulationTotale() {
    population = 0;
    for (int i = 0; i < batiments.size(); i++) {
        population += batiments[i]->getHabitantsActuels();
    }
}

int Ville::calculerSatisfaction() {
    int satisfactionTotale = 50;

    for (int i = 0; i < batiments.size(); i++) {
        satisfactionTotale += batiments[i]->getEffetSatisfaction();
    }

    if (pollution > 50.0) {
        satisfactionTotale -= (int)(pollution / 10.0);
    }

    if (eau < 0 || electricite < 0) {
        satisfactionTotale -= 20;
    }

    if (satisfactionTotale < 0) satisfactionTotale = 0;
    if (satisfactionTotale > 100) satisfactionTotale = 100;


    satisfactionTotale += (int)bonusSatisfaction;
    
    if (satisfactionTotale < 0) satisfactionTotale = 0;
    if (satisfactionTotale > 100) satisfactionTotale = 100;

    satisfaction = satisfactionTotale;
    return satisfaction;
}

void Ville::calculerPollutionTotale() {
    pollution = bonusPollution;
    for (int i = 0; i < batiments.size(); i++) {
        pollution += batiments[i]->getPollution();
    }
}

void Ville::mettreAJourRessources(double prodEau, double prodElec) {
    eau += prodEau;
    electricite += prodElec;
    for (int i = 0; i < batiments.size(); i++) {
        batiments[i]->calculerImpactRessources(eau, electricite);
    }

    calculerPollutionTotale();
    calculerPopulationTotale();
    calculerSatisfaction();
}
