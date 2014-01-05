#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "organism.h"
#include "population.h"

double fitness(std::vector<int*> * genome)
{
    return 1.0;
}

void mutate(int*)
{
    return;
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
    TOrganism<int>::fitfunc = &fitness;
    TOrganism<int>::mutfunc = &mutate;

    TPopulation<TOrganism<int>> tpop;
    tpop.GetBestOrganism()->PrintGenome();
    //tpop.GetBestOrganism()->Mutate(2);
    //std::cout<<tpop.GetBestOrganism()->GetFitness()<<std::endl;
    tpop.NewGeneration();
    tpop.GetBestOrganism()->PrintGenome();
    //tpop.GetBestOrganism()->PrintGenome();

}
