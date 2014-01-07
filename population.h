/* 
  population.h
*/

#ifndef population_h
#define population_h

#include <vector>
#include <algorithm> 
#include <iostream>
#include <random>

//#include "organism.h"

template <class T> struct TCmp
{
    bool operator() (T * p1, T * p2) const
    {
        if (p1->GetFitness() != p2->GetFitness()) return p1->GetFitness() < p2->GetFitness();
        return false;
    }
};

template <class T> class GA
{
    public:
        GA() {
            for (int i =0; i<populationSize;i++)
            {
                population.push_back(new T());
            }
        }
        ~GA() {
            while(!population.empty())
            {
                delete population.back();
                population.pop_back();
            }
        }
        T * GetOrganism(int n){
            return population.at(n);
        }
        T * GetBestOrganism(){
            return GetOrganism(0);
        }
        void NewGeneration(){
            // generate 'numChildren' children, 
            std::vector<T*> children;
            children.reserve(numChildren);

			// RNG distributions
			std::uniform_real_distribution<> uniformDist(0.0,1.0);
			std::uniform_int_distribution<> geneInd(0, T::numGenes-1);
            std::uniform_int_distribution<> popDist(0, GA<T>::populationSize-1);

            //TODO check num child > pop size
            for (int i=0; i<GA<T>::numChildren;i++){ 
                // pick two at random  //TODO, this should favour the fittest
                int ind1 = popDist(g);//
                int ind2 = ind1;
                while (ind2==ind1) {
                    ind2 = popDist(GA<T>::g);
                }
                // mate them
                T * child = new T(population.at(ind1),population.at(ind2));

				// Genetic Operators
				if (uniformDist(g) < T::mutProb){// mutate
					child->Mutate(geneInd(g));
				}
				if (uniformDist(g)<	T::swapProb){// swap
					child->Swap(geneInd(g),geneInd(g));
				}
				if (uniformDist(g)<	T::invProb){// invert
					child->Invert(geneInd(g),geneInd(g));
				}
				if (uniformDist(g)<	T::insProb){// insert
					child->Insert(geneInd(g),geneInd(g));
				}
				
                // add to list
                children.push_back(child);
            }

            // sort children by fitness
            std::sort(children.begin(),children.end(),TCmp<T>());

            // cull weakest, leaving only 'populationSize'
            while(children.size()>GA<T>::populationSize)// warning unsigned int
            {
                delete children.back();
                children.pop_back();
            }

            // reasign population to new child population
            population.swap(children);
    
            // delete previous population (now in children)
            while(!children.empty())
            {
                delete children.back();
                children.pop_back();
            }
            return;
        }
        static int populationSize;  
        static int numGenerations;  
        static int numChildren;   
        static std::minstd_rand g;

    private:
        std::vector<T*> population;
};

// static member definitions
template <class T> int GA<T>::populationSize;
template <class T> int GA<T>::numChildren;   
template <class T> int GA<T>::numGenerations;  
template <class T> std::minstd_rand GA<T>::g;

#endif
