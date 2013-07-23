//#include <cstdlib> 
//#include <ctime> 
//#include <iostream>
//#include <stdio.h>
//#include <assert.h>

#include "organism.h"

using namespace std;

Organism::Organism( )
{
	genome.assign(numGenes,1.);
	fitness = -999.;
}


Organism Organism::Mate(Organism &partner){
	// randomly pick genes from self or partner
	Organism child;
	for (int i=0; i<numGenes; i++){
		int a = rand()%2;
		if (a == 0){
			child.genome[i] = genome[i];
		}
		else{
			child.genome[i] = partner.genome[i];
		}
	}
	return child;
}

double Organism::Fitness()
{
	// A low fitness is good
	// if fitness has been calculated return that
	if (fitness>-1.){
		return fitness;
	}
	fitness = _fitness(genome);
	return fitness;
}

void Organism::Mutate()
{	
	// randomly choose to randomly shift each gene
	for (int i=0; i<numGenes; i++){
		if (rand()%100<mutationRate){
			double range = (geneMax-geneMin)*mutationAmt; // ammount value can be changed
			double newValue = genome[i] + (-1.+2.0*double(rand()%1000)/1000)*range;
			newValue = max(newValue,geneMin);
			newValue = min(newValue,geneMax);
			genome[i] = newValue;
		}
	}
	return;
}

void Organism::Randomise(){
	// randomly shift all gene
	for (int i=0; i<numGenes; i++){
			double range = (geneMax-geneMin);
			genome[i] = geneMin + range*double(rand()%2000)/1000;
	}
	return;
}

double defaultFitness(std::vector<double> genome){
	// calculate fitness
	double retVal = 0.0;
	for (unsigned int i=0; i<genome.size(); i++){
		retVal+=genome[i]*genome[i];
	}
	return retVal;
}

double (*Organism::_fitness)(std::vector<double> genome) = defaultFitness;

int Organism::numGenes = 2;
double Organism::geneMin = -1.;
double Organism::geneMax = +1.;
int Organism::mutationRate = 1;// 1 = 1%
double Organism::mutationAmt = 0.1;