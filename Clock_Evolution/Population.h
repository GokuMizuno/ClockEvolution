#ifndef POPULATION_H
#define POPULATION_H
#include "stdfax.h"

class Population
{
private:
	std::vector<Clock> individuals;
public:
	//Population();
	Population(varData, bool);
	void mate(varData);
	void outputVitals(varData);
	void showClock(int);
};

#endif
