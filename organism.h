/* 
  organism.h
    Base organism
*/

#ifndef organism_h
#define organism_h

#include <vector>
#include <iostream>
#include <random>

#include "gene.h"
#include "config.h"

class Organism
{
    public:
        Organism(Config * _cfg);
        Organism(Organism * mother, Organism * father, Config * _cfg);
        ~Organism();
        Gene * GetGene(int i);
        void Mutate();
        double GetFitness();
        double CalcFitness();
        void Randomise();
        //bool operator< (Organism &b){
        //    return GetFitness() < b.GetFitness();
        //}

    private:
        std::vector<Gene*> genome;
        double fitness;
        Config * cfg;
};

#endif