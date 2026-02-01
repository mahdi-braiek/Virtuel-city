#ifndef VILLE_H
#define VILLE_H

#include "batiment.h"
#include <vector>
#include <string>
using namespace std;

class Ville
{
private:
    string nom;
    double budget;
    int population;
    int satisfaction;
    vector<Batiment*> batiments;
    double eau;
    double electricite;
    double pollution;
    double bonusSatisfaction; 
    double bonusPollution;
    int prochainId;

public:
    Ville();
    Ville(string nom, double budgetInitial);
    ~Ville();

    void ajouterBatiment(Batiment* batiment);
    bool supprimerBatiment(int id);
    Batiment* trouverBatiment(int id);

    void calculerConsommationTotale(double& totalEau, double& totalElec);
    void calculerPopulationTotale();
    int calculerSatisfaction();
    void calculerPollutionTotale();
    void mettreAJourRessources(double prodEau, double prodElec);

    string getNom() { return nom; }
    double getBudget() { return budget; }
    int getPopulation() { return population; }
    int getSatisfaction() { return satisfaction; }
    double getEau() { return eau; }
    double getElectricite() { return electricite; }
    double getPollution() { return pollution; }
    double getBonusSatisfaction() { return bonusSatisfaction; }
    double getBonusPollution() { return bonusPollution; }
    int getProchainId() { return prochainId; }
    vector<Batiment*>& getBatiments() { return batiments; }

    void setNom(const string& n) { nom = n; }
    void setBudget(double val) { budget = val; }
    void ajouterBudget(double montant) { budget += montant; }
    void setSatisfaction(int val) { satisfaction = val; }
    void ajouterBonusSatisfaction(double val) { bonusSatisfaction += val; }
    void setEau(double val) { eau = val; }
    void setElectricite(double val) { electricite = val; }
    void setPollution(double val) { pollution = val; }
    void ajouterBonusPollution(double val) { bonusPollution += val; }
    void incrementerProchainId() { prochainId++; }
};

#endif
