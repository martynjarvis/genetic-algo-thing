#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "population.h"
#include "organism.h"
#include "config.h"

// quadratic equation, roots = 3,5

int main()
{	
	Config cfg;
	// pop config
	cfg.populationSize = 50;  
	cfg.numGenerations = 1000;  
	cfg.numChildren = 100;   

	// organism config
	cfg.numGenes = 2;

	// gene config
	cfg.mutProb = 5;
	cfg.max = 100.;
	cfg.min = -100.;
	cfg.mutAmount = 2.;

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
			<<"\tgenome:"<<x0
			<<","<<x1<<std::endl;
	}

	system("PAUSE");
}
