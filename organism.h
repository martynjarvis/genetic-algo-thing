/* 

  organism.h

*/

#ifndef organism_h
#define organism_h

#include <vector>
#include <iostream>

extern int g_numGenes;
extern int g_mutationRate;
extern double g_mutationAmt;

class Organism
{
    public:
        Organism();
        void Mutate();
		double Fitness();
		Organism Mate(Organism &partner);
		void Randomise();
		bool operator< ( Organism &b){return Fitness() < b.Fitness();}
		std::vector<double> genome;// this should be private

		// static parameters 
		static int numGenes;
		static double geneMin;
		static double geneMax;
		static int mutationRate;// 1 = 1%
		static double mutationAmt;
		static double (*_fitness)(std::vector<double> genome);

    private:
		double fitness;// cached fitness to avoid recalculating
};
#endif