#ifndef SIMULATION_H
#define SIMULATION_H

#include "ville.h"
#include <string>
#include <vector>
using namespace std;

struct Evenement {
    string nom;
    string description;
    int impactSatisfaction;
    double impactEau;
    double impactElectricite;
    double impactPollution;
    double impactBudget;
};

class Simulation
{
private:
    int cycleActuel;
    Ville* ville;
    vector<Evenement> evenements;
    Evenement dernierEvenement;

    void initialiserEvenements();

public:
    Simulation();
    Simulation(Ville* v);

    void demarrerCycle();
    void terminerCycle();
    Evenement declencherEvenement();
    Evenement getDernierEvenement() { return dernierEvenement; }

    int getCycleActuel() { return cycleActuel; }
    Ville* getVille() { return ville; }

    void setCycleActuel(int c) { cycleActuel = c; }

    void setVille(Ville* v) { ville = v; }
};

#endif
