#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "gene.h"
#include "organism.h"
#include "population.h"
#include "config.h"

// forward declaration
//template <class T> class TGene;

double fitness(std::vector<TGene<double>*> * genome)
{
    return 1.0;
}

int main()
{    
	// test templated classes
    TConfig<double> tcfg;
    tcfg.numGenes = 2;
    tcfg.init = 2.0;
    tcfg.fitness = &fitness;

    TOrganism<double> torg(&tcfg);

    std::cout<<"Fitness:"<<torg.GetFitness()<<std::endl;

    Config cfg;
    // pop config
    cfg.populationSize = 50;  
    cfg.numGenerations = 10;  
    cfg.numChildren = 100;   

    // organism config
    cfg.numGenes = 2;

    // gene config
    cfg.mutProb = 5;
    cfg.max = 100.;
    cfg.min = -100.;
    cfg.mutAmount = 10.;

    // create population (this initialises the first generation)
    Population A(&cfg);
    
    // shuffle starting population
    A.Randomise();

    for (int i =0; i<cfg.numGenerations; i++){
        A.Generation();
        double x0,x1;
        A.GetBestOrganism()->GetGene(0)->Value(x0);
        A.GetBestOrganism()->GetGene(1)->Value(x1);
        std::cout<<"Generation:"<<i
                 <<"\tbest:"<<A.GetBestOrganism()->GetFitness()
                 <<"\tgenome:"<<x0<<","<<x1<<std::endl;
    }

}
