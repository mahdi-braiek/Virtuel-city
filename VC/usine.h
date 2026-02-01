#ifndef USINE_H
#define USINE_H

#include "batiment.h"

class Usine : public Batiment
{
private:
    double productionRessources;
    double pollution;

public:
    Usine();
    Usine(int id, string nom);

    double produireRessources();
    void afficherDetails();
    void calculerImpactRessources(double& eau, double& electricite) override;
    
    double getPollution() override { return pollution; }

    double getProductionRessources() { return productionRessources; }
};

#endif
