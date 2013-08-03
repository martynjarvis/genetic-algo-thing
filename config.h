/* 
  config.h
*/

#ifndef config_h
#define config_h

#include <iostream>
#include <random>

class Config
{
    public:
        Config(){
            // init something?
            // seed random num gen?
            std::cout<<"config loaded"<<std::endl;
        }
 
        // pop config
        int populationSize;  
        int numGenerations;  
        int numChildren;   
        bool geometricMating;
        double geometricMatingParam;

        // organism config
        int numGenes;

        // gene config
        // todo, these should be separate for each gene
        // and what about other types URGH!
        int mutProb;
        double max;
        double min;
        double mutAmount;

        // this is awful
        int mutAmountInt;
        int maxInt;
        int minInt;

        // keep track of my random number generator
        std::minstd_rand g;
};

#endif