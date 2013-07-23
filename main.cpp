#include <cstdlib> 
#include <iostream>
#include <stdio.h>

#include "population.h"
#include "organism.h"

// quadratic equation, roots = 3,5
double quad(std::vector<double> genome){
	int a = 2;
	int b = -16;
	int c = 30;
	double retVal = 0.0;
	double x1 = genome[0];
	double x2 = genome[1];
	retVal+= fabs(a*x1*x1 + b*x1 + c);
	retVal+= fabs(a*x2*x2 + b*x2 + c);
	retVal+= 1.0/(fabs(x1-x2));// punish equal roots
	return retVal;
}

int main()
{
	// Set Organism paramaters
	Organism::numGenes = 2;
	Organism::geneMin = -100.;
	Organism::geneMax = 100.;
	Organism::mutationRate = 5;// 1 = 1%
	Organism::mutationAmt = 0.05;
	Organism::_fitness = quad;

	// Set Population paramaters	
	Population::populationSize=50;
	Population::numGenerations=500;
	Population::numChildren = 100;  

	// create population (this initialises the first generation)
	Population A;
	
	// shuffle starting population
	A.Randomise();

	for (int i =0; i<Population::numGenerations; i++){
		A.Generation();
		std::cout<<"Generation:"<<i
			<<", best:"<<A.GetBestOrganism().Fitness()
			<<", genome:"<<A.GetBestOrganism().genome[0]
			<<","<<A.GetBestOrganism().genome[1]<<std::endl;
	}

	system("PAUSE");
}//end of main()
