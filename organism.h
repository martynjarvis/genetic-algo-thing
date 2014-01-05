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

template <class T> class TOrganism
{
    public:
        TOrganism(TConfig<T> * _cfg)
        {
            cfg = _cfg;
            for (int i=0; i<cfg->numGenes; i++)
            {
                genome.push_back(new TGene<T>(cfg));
            }
            fitness = -999.;
        }
        
        TOrganism(TOrganism<T> * mother, TOrganism<T> * father, TConfig<T> * _cfg)
        {
            cfg = _cfg;
            // copy genes from father or mother
            // TODO, add cross over
            std::uniform_int_distribution<> dist(0, 1);
            for (int i=0; i<cfg->numGenes; i++)
            {
                if (dist(cfg->g) == 0)
                {
                    genome.push_back(mother->GetGene(i)->Copy());
                }
                else
                {
                    genome.push_back(father->GetGene(i)->Copy());
                }
            }
            fitness = -999.;
        }

        ~TOrganism()
        {
            //clean up genome
            while(!genome.empty())
            {
                delete genome.back();
                genome.pop_back();
            }
        }

        TGene<T> * GetGene(int i)
        {
            // returns a pointer to gene
            return genome.at(i);
        }

        void Mutate(){
            return;
        }

        void Swap(int a, int b){
            T temp = genome.at(a);
            genome.at(a) = genome.at(b);
            genome.at(b) = temp;
            return;
        }

        void Invert(int a, int b){
            while (a<b){
                Swap(a,b);
                a++;
                b--;
            }
            return;
        }

        void Insert(int a, int b){
            // insert b at a and shift everything down
            while (a<b){
                Swap(b,b-1);
                b--;
            }
            return;
        }

        double GetFitness()
        {
            // A low fitness is good
            // if fitness has been calculated return that
            if (fitness>-1.)
            {
                return fitness;
            }
            // or calculate, store and return fitness
            fitness = cfg->fitness(&genome);
            return fitness;
        }

    private:
        std::vector<TGene<T>*> genome; 
        double fitness;
        TConfig<T> * cfg;
};

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

    private:
        std::vector<Gene*> genome;
        double fitness;
        Config * cfg;
};

#endif
