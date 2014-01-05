#include "organism.h"


Organism::Organism(Config * _cfg)
{
    cfg = _cfg;
    // overwrite this to set up organism
    // temporary example
    // no reason that the genome can't contain multiple types
    for (int i=0; i<cfg->numGenes; i++)
    {
        genome.push_back(new RealGene(cfg));
    }
    fitness = -999.;
}

Organism::~Organism()
{
    //clean up genome
    while(!genome.empty())
    {
        delete genome.back();
        genome.pop_back();
    }
}

Organism::Organism(Organism * mother,Organism * father,Config * _cfg )
{
    cfg = _cfg;
    // copy genes from father or mother
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

Gene * Organism::GetGene(int i)
{
    // returns a pointer to gene
    return genome.at(i);
}


double Organism::GetFitness()
{
    // A low fitness is good
    // if fitness has been calculated return that
    if (fitness>-1.)
    {
        return fitness;
    }
    // or calculate, store and return fitness
    fitness = CalcFitness();
    return fitness;
}

double Organism::CalcFitness()
{
    // overwrite this to set up organism
    /*return 1.;*/
    // temproary example
    // quadratic equation, roots = 3,5
    int a = 2;
    int b = -16;
    int c = 30;
    double retVal = 0.0;
    double x1,x2;
    genome.at(0)->Value(x1);
    genome.at(1)->Value(x2);
    retVal+= fabs(a*x1*x1 + b*x1 + c);
    retVal+= fabs(a*x2*x2 + b*x2 + c);
    retVal+= 1.0/(fabs(x1-x2));// punish equal roots
    return retVal;
}

void Organism::Mutate()
{    
    // randomly choose to shift each gene
    for (int i=0; i<cfg->numGenes; i++)
    {
        genome[i]->Mutate();
    }
    return;
}

void Organism::Randomise()
{    
    // randomly choose to shift each gene
    for (int i=0; i<cfg->numGenes; i++)
    {
        genome[i]->Randomise();
    }
    return;
}


