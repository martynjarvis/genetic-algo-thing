/* 
  gene.h
*/

#ifndef gene_h
#define gene_h

#include <iostream>
#include <random>

#include "config.h"

template <class T> class TGene
{
    public:
		T value;
        TGene(TConfig<T> * _cfg, T initval)
        {
            cfg = _cfg;
            value = initval; // TODO copy?
        }
        void Mutate()
        {
			std::uniform_int_distribution<> amountDist(-10,10);
			const int j = sizeof(T)/sizeof(int);
			union {
				T input;
				unsigned int output[j];
			} data;
			data.input = value;
			for (int i=0; i<j; i++){
				data.output[i] = data.output[i] += amountDist(cfg->g);
			}
			value = data.input;
            return;// TODO rather than +- an ammount, flip a bit
        };
        TGene * Copy()
        {
            // implement this
            return 0;
        };
        // return functions
        T GetValue(){
			return value;
		}
        void SetValue(T newValue){
			value = newValue;
		}

    protected:
        TConfig<T> * cfg;
};



class Gene
{
    public:
        Gene(Config * _cfg)
        {
            cfg = _cfg;
            Randomise();
        }
        virtual void Randomise()
        {
            // implement this in base classes
            return;
        }
        virtual int Mutate()
        {
            // implement this in base classes
            return 0;
        };
        virtual Gene * Copy()
        {
            // implement this in base classes
            return 0;
        };
        // return functions
        virtual void Value(bool & ret){return;}
        virtual void Value(int & ret){return;}
        virtual void Value(double & ret){return;}

    protected:
        Config * cfg;
};

class IntGene : public Gene
{
    public: 
        IntGene(Config * _cfg) : Gene(_cfg)
        {
            // do I need anything here?
        }
        void Randomise()
        {
             std::uniform_int_distribution<> dist(cfg->minInt, cfg->maxInt);
             value = dist(cfg->g);
        }
      
        int Mutate()
        {
             std::uniform_int_distribution<> mutateDist(0, 100);
             if (mutateDist(cfg->g) < cfg->mutProb)
             {
                std::uniform_int_distribution<> amountDist(-cfg->mutAmountInt, cfg->mutAmountInt);
                value += amountDist(cfg->g);
                value = std::max(value,cfg->minInt);
                value = std::min(value,cfg->maxInt);
                return 1;
             }
             return 0;
        }
        IntGene * Copy()
        {
            return new IntGene(*this);
        };        
        void Value(int & ret)
        {
            ret = value;
            return;
        }
    private:
        int value;
};

class RealGene : public Gene
{
    public:
        RealGene(Config * _cfg):Gene(_cfg)
        {
            // do I need anything here?
        }
        void Randomise()
        {
             std::uniform_real_distribution<> dist(cfg->min, cfg->max);
             value = dist(cfg->g);
        }
      
        int Mutate()
        {
            std::uniform_int_distribution<> mutateDist(0, 100);
            if (mutateDist(cfg->g) < cfg->mutProb)
            {
                std::uniform_real_distribution<> dist(-cfg->mutAmount, cfg->mutAmount);
                value += dist(cfg->g);
                value = std::max(value,cfg->min);
                value = std::min(value,cfg->max);
                return 1;
            }
            return 0;
        }
        RealGene * Copy()
        {
            return new RealGene(*this);
        };       
        void Value(double & ret)
        {
            ret = value;
            return;
        }
    private:
        double value;
};


#endif
