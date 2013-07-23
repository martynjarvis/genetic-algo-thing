
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
	// calculate fitness
	fitness = _fitness(&genome);
	return fitness;
}

void Organism::Mutate()
{	
	// randomly choose to shift each gene
	for (int i=0; i<numGenes; i++){
		if (rand()%100<mutationRate){
			double range = (geneMax-geneMin)*mutationAmt; 
			double newValue = genome[i] + (-1.+2.0*double(rand())/RAND_MAX)*range; // rand() limits the granularity
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
			genome[i] = geneMin + range*2.0*double(rand())/RAND_MAX;
	}
	return;
}

double defaultFitness(std::vector<double> * genome){
	// calculate fitness
	double retVal = 0.0;
	for (unsigned int i=0; i<genome->size(); i++){
		retVal+=genome->at(i)*genome->at(i);
	}
	return retVal;
}

double (*Organism::_fitness)(std::vector<double> * genome) = defaultFitness;

int Organism::numGenes = 2;
double Organism::geneMin = -1.;
double Organism::geneMax = +1.;
int Organism::mutationRate = 1;// 1 = 1%
double Organism::mutationAmt = 0.1;