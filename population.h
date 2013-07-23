/* 
  population.h
*/



#ifndef population_h
#define population_h

//#define        GPOPSIZE 100

#include <vector>
#include <algorithm>    // std::sort
#include <iostream>


#include "organism.h"

extern int g_populationsize;
extern int g_numgenerations;


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