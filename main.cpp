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
    std::uniform_real_distribution<> dist(-Organism<double>::mutAmount, Organism<double>::mutAmount);
    *gene += dist(GA<Organism<double>>::g);
    return;
}

int main()
{    
    // config
    GA<Organism<double>>::populationSize = 50;  
    GA<Organism<double>>::numGenerations = 100;  
    GA<Organism<double>>::numChildren = 100;   

	Organism<double>::mutProb = 0.1; // only mutation for this example
	Organism<double>::mutAmount = 1.0;

    Organism<double>::numGenes = 2;
    Organism<double>::init.push_back(1.0); // values to initialise

    Organism<double>::fitfunc = &fitness;
    Organism<double>::mutfunc = &mutate;

    GA<Organism<double>> tpop;
	 
	for (int i =0; i< GA<Organism<double>>::numGenerations; i++){
		tpop.NewGeneration();
		tpop.GetBestOrganism()->PrintGenome();
	}

	system("PAUSE");
}
