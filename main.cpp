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
    
    TPopulation<TOrganism<int>>::populationSize = 50;  
    TPopulation<TOrganism<int>>::numGenerations = 10;  
    TPopulation<TOrganism<int>>::numChildren = 100;   

    TOrganism<int>::numGenes = 4;
    TOrganism<int>::init.push_back(1);
    TOrganism<int>::init.push_back(2);
    TOrganism<int>::init.push_back(3);
    TOrganism<int>::init.push_back(4);
    //TOrganism<int>::fitfunc = &fitness;

    // TODO I would rather specify:

    //TOrganism<int> torg;
    //torg.PrintGenome();
    
    TPopulation<TOrganism<int>> tpop;
    tpop.GetBestOrganism()->PrintGenome();

    //std::cout<<tpop.GetBestOrganism()->GetFitness()<<std::endl;
    //tpop.NewGeneration();
    //tpop.GetBestOrganism()->PrintGenome();

}
