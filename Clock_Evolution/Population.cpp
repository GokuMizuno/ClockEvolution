#include "stdfax.h"

class Population
{
	individuals = new Clock[popsize];
	void Population(int popsize, bool init)
	{
		if (init)
		{
			for (int i = 0; i < popsize; i++)
			{
				Clock individual = new Clock();
				individual.generate();
				saveIndividual(i, individuals);
			}
		}
	}
	Clock getIndividual(int index)
	{
		return individuals[index];
	}
	Clock getWorst(Clock c1, Clock c2, Clock c3)
	//change this to take three random Clocks, return the worst one, mate other two
	{
		return c1.Score() > (c2.Score() > c3.Score() ? c2 : c3) ? c1 : (c2.Score() > c3.Score() ? c2 : c3);
	}
	void saveIndividual(int index, Clock indy)
	{
		individuals[index] = indy;
	}

};
