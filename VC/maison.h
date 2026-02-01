#ifndef MAISON_H
#define MAISON_H

#include "batiment.h"

class Maison : public Batiment
{
private:
    int capaciteHabitants;
    int habitantsActuels;

public:
    Maison();
    Maison(int id, string nom, int capacite);

    bool ajouterHabitants(int nb);
    bool retirerHabitants(int nb);
    void afficherDetails() override;
    void calculerImpactRessources(double& eau, double& electricite) override;
    void mettreAJour() override;

    int getHabitantsActuels() override { return habitantsActuels; }
    int getCapaciteHabitants() override { return capaciteHabitants; }

    void setHabitantsActuels(int nb) { habitantsActuels = nb; }
    void setCapaciteHabitants(int c) { capaciteHabitants = c; }
};

#endif
