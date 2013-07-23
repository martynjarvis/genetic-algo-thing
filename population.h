/* 
  population.h
*/

#ifndef population_h
#define population_h

#include <vector>
#include <algorithm> 
#include <iostream>

#include "organism.h"

class Population
{
    public:
        Population();
        void Generation();	
        void Randomise();
        Organism GetOrganism(int n);	
		Organism GetBestOrganism();
		static int populationSize;  
		static int numGenerations;  
		static int numChildren;   

    private:
        std::vector<Organism> organisms;
        int fittest;
		double topFitness;
		double sumFitness;
};

#endif