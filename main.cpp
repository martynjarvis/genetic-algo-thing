#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "gene.h"
#include "organism.h"
#include "population.h"
#include "config.h"

// forward declaration
//template <class T> class TGene;

double fitness(std::vector<TGene<int>*> * genome)
{
    return 1.0;
}

int main()
{    
	// test templated classes
    TConfig<int> tcfg;
    tcfg.numGenes = 4;
    tcfg.init.push_back(1);
    tcfg.init.push_back(2);
    tcfg.init.push_back(3);
    tcfg.init.push_back(4);

    tcfg.fitness = &fitness;

    TOrganism<int> torg(&tcfg);
    torg.PrintGenome();

    torg.Swap(1,2);
    torg.PrintGenome();

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
