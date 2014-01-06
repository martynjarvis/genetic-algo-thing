/* 
  organism.h
    Base organism
*/

#ifndef organism_h
#define organism_h

#include <vector>
#include <iostream>
#include <random>

#include "population.h"

template <class T> class TOrganism
{
    public:
        TOrganism()
        {
            for (int i=0; i<numGenes; i++)
            {
                genome.push_back(new T(init.at(i)));
            }
            fitness = -999.;
        }
        
        TOrganism(TOrganism<T> * mother, TOrganism<T> * father)
        {
            // copy genes from father or mother
            std::uniform_int_distribution<> dist(0, 1);
            for (int i=0; i<numGenes; i++)
            {
                if (dist(TPopulation<T>::g) == 0) 
                {
                    genome.push_back(new T(*mother->GetGene(i)));
                }
                else
                {
                    genome.push_back(new T(*father->GetGene(i)));
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

        void PrintGenome(){
            std::cout<<"Fitness: "<<GetFitness()<<"\tGenome:";
            for (int i=0; i<numGenes; i++){
                std::cout<<' '<<(*genome.at(i));
            }
            std::cout<<std::endl;
        }

        T * GetGene(int i)
        {
            // returns a pointer to gene
            return genome.at(i);
        }

        void Mutate(int a){
            mutfunc(genome.at(a));
        }

        void Swap(int a, int b){
			if (a!=b){
				std::swap(genome.at(a),genome.at(b));
			}
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
            // This is not very efficient using swap, but looks nice
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
            fitness = fitfunc(&genome);
            return fitness;
        }
        static int numGenes;
        static double mutProb;
        static double swapProb;
        static double insProb;
        static double invProb;
        static T max;
        static T min;
        static std::vector<T> init;
        static T mutAmount;
        static double (*fitfunc)(std::vector<T*> * genome);
        static void (*mutfunc)(T* gene);

    private:
        std::vector<T*> genome; 
        double fitness;
};

template <class T> int TOrganism<T>::numGenes;
template <class T> double TOrganism<T>::mutProb;
template <class T> double TOrganism<T>::swapProb;
template <class T> double TOrganism<T>::invProb;
template <class T> double TOrganism<T>::insProb;
template <class T> T TOrganism<T>::max;
template <class T> T TOrganism<T>::min;
template <class T> std::vector<T> TOrganism<T>::init;
template <class T> T TOrganism<T>::mutAmount;
template <class T> double (*TOrganism<T>::fitfunc)(std::vector<T*> * genome);
template <class T> void (*TOrganism<T>::mutfunc)(T* gene);

#endif
