#include "maison.h"
#include <iostream>

Maison::Maison() : Batiment() {
    capaciteHabitants = 0;
    habitantsActuels = 0;
}

Maison::Maison(int id, string nom, int capacite)
    : Batiment(id, nom, "Habitation", 10.0, 15.0, 5, 50000.0) {
    capaciteHabitants = capacite;
    habitantsActuels = 0;
}

bool Maison::ajouterHabitants(int nb) {
    if (habitantsActuels + nb <= capaciteHabitants) {
        habitantsActuels += nb;
        return true;
    }
    return false;
}

bool Maison::retirerHabitants(int nb) {
    if (habitantsActuels >= nb) {
        habitantsActuels -= nb;
        return true;
    }
    return false;
}

void Maison::mettreAJour() {
    if (habitantsActuels == 0 && capaciteHabitants > 0) {
        ajouterHabitants(capaciteHabitants);
    }
}

void Maison::afficherDetails() {
    Batiment::afficherDetails();
    cout << "Capacite Habitants: " << capaciteHabitants << endl;
    cout << "Habitants Actuels: " << habitantsActuels << endl;
}

void Maison::calculerImpactRessources(double& eau, double& electricite) {
    Batiment::calculerImpactRessources(eau, electricite);
}
