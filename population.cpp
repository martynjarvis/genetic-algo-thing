
#include "population.h"

using namespace std;


struct Cmp
{
    bool operator() (Organism * p1, Organism * p2) const
    {
        if (p1->GetFitness() != p2->GetFitness()) return p1->GetFitness() < p2->GetFitness();
        return false;
    }
};

Population::Population(Config * _cfg)
{
	cfg = _cfg;
	for (int i =0; i<cfg->populationSize;i++)
	{
		//Organism a(_cfg);
		organisms.push_back(new Organism(_cfg));
	}
}

Population::~Population()
{
	while(!organisms.empty())
	{
		delete organisms.back();
		organisms.pop_back();
	}
}


void Population::Generation()
{  
	// generate 'numChildren' children, 
	std::vector<Organism*> children;
	children.reserve(cfg->numChildren);

	//TODO check num child > pop size

	for (int i =0; i<cfg->numChildren;i++){ 
		// pick two at random
		std::uniform_int_distribution<> popDist(0, cfg->populationSize-1);//todo, this should favour the fittest
		int ind1 = popDist(cfg->g);//
		int ind2 = ind1;
		while (ind2==ind1) {
			ind2 = popDist(cfg->g);
		}
		// mate them
		Organism * child = new Organism(organisms[ind1],organisms[ind2],cfg);
		// mutate offspring
		child->Mutate();
		// add to list
		children.push_back(child);
	}

	// sort children by fitness
	std::sort(children.begin(),children.end(),Cmp());

	// kill weakest, leaving only 'populationSize'
	while(children.size()>cfg->populationSize)
	{
		delete children.back();
		children.pop_back();
	}

	// reasign population to new child population
	organisms = children;
	
	return;
}

void Population::Randomise(){
	for (int i =0; i<cfg->populationSize;i++){ 
		organisms[i]->Randomise();
	}
}

Organism * Population::GetOrganism(int n){
	 return organisms[n];
}

Organism * Population::GetBestOrganism(){
	 return GetOrganism(0);
}


