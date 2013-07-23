
#include "population.h"

using namespace std;

Population::Population( )
{
	organisms.assign(populationSize,Organism());
}

void Population::Generation()
{  
	// generate 'numChildren' children, 
	std::vector<Organism> children;
	children.reserve(numChildren);

	for (int i =0; i<numChildren;i++){ //todo, this should favour the fittest
		int ind1 = rand()%populationSize;
		int ind2 = ind1;
		while (ind2==ind1) {
			ind2 = rand()%populationSize;
		}
		Organism child = organisms[ind1].Mate(organisms[ind2]);
		child.Mutate();
		children.push_back(child);
	}

	// sort children by fitness
	std::sort(children.begin(),children.end());

	// kill weakest
	children.resize(populationSize);

	// reasign population to new child population
	organisms = children;
	
	return;
}

void Population::Randomise(){
	for (int i =0; i<populationSize;i++){ 
		organisms[i].Randomise();
	}
}

Organism Population::GetOrganism(int n){
	 return organisms[n];
}

Organism Population::GetBestOrganism(){
	 return GetOrganism(0);
}

int Population::populationSize = 50;  
int Population::numGenerations = 50;  
int Population::numChildren = 100;   

