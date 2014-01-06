#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "organism.h"
#include "population.h"

// function that returns the fitness of a given genome
double fitness(std::vector<double*> * genome)
{
    int a = 2;
    int b = -16;
    int c = 30;
    double retVal = 0.0;
    double x1 = *genome->at(0);
	double x2 = *genome->at(1);
    retVal+= fabs(a*x1*x1 + b*x1 + c);
    retVal+= fabs(a*x2*x2 + b*x2 + c);
    retVal+= 1.0/(fabs(x1-x2));// punish equal roots
    return retVal;
}

// function that mutates a gene
void mutate(double* gene)
{
    std::uniform_real_distribution<> dist(-TOrganism<double>::mutAmount, TOrganism<double>::mutAmount);
    *gene += dist(TPopulation<TOrganism<double>>::g);
    return;
}

int main()
{    
    
    TPopulation<TOrganism<double>>::populationSize = 50;  
    TPopulation<TOrganism<double>>::numGenerations = 100;  
    TPopulation<TOrganism<double>>::numChildren = 100;   

	TOrganism<double>::mutProb = 0.1;
	TOrganism<double>::swapProb = 0.05; // TODO can I add this to header
	TOrganism<double>::invProb = 0.00;
	TOrganism<double>::insProb = 0.00;
	TOrganism<double>::mutAmount = 1.0;

    TOrganism<double>::numGenes = 2;
    TOrganism<double>::init.push_back(10.0);
    TOrganism<double>::init.push_back(20.0);

    TOrganism<double>::fitfunc = &fitness;
    TOrganism<double>::mutfunc = &mutate;

    TPopulation<TOrganism<double>> tpop;

	 
	for (int i =0; i< TPopulation<TOrganism<double>>::numGenerations; i++){
		tpop.NewGeneration();
		tpop.GetBestOrganism()->PrintGenome();
    }

	system("PAUSE");

}
