/* 
  population.h
*/

#ifndef population_h
#define population_h

#include <vector>
#include <algorithm> 
#include <iostream>

#include "organism.h"
#include "config.h"

class Population
{
    public:
        Population(Config * cfg);
		~Population();
        void Generation();	
        void Randomise();
        Organism * GetOrganism(int n);	
		Organism * GetBestOrganism();

    private:
        std::vector<Organism*> organisms;
		Config * cfg;
};

#endif