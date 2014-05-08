#include "stdfax.h"
/*This file has both the mating and mutating functions for the clocks.
  Since both are working with the genome of the function, both are
  friends, and hence, it seems natural they go together.*/

/*Mating involves taking the genome of two clocks, and merging them.
  cdk007 uses a random matrix, mapped to either 0 or 1, and if 0, then
  get genome from father, 1, get genome from mother.
  
  Aftr mating, apply a mutation to the child's genome.*/

//change all of this to deal with pointers

double round(double);
/*
Clock mate(Clock &c1, Clock &c2, Clock &c3)
{
	int i,j,k;
	int generation;
	generation = (c1.Generation() >= c2.Generation()) ? c1.Generation() : c2.Generation();
	generation++; //gen is one higher than the highest gen parent.
	for(int i=0;i<Clock::rows;i++)
	{
		for(int j=0;j<Clock::columns;j++)
		{
			if(round((double)(rand()/RAND_MAX)) == 0)
				c3.genome[i][j] = c1.genome[i][j];
			else
				c3.genome[i][j] = c2.genome[i][j];
		}
	}
	c3.generation = generation;
	mutate(&c3);

	return &c3; //this function should return the child, c3, but as we haven't set that up, it throws an error
};

Clock mutate(Clock &ck3)
{
	//I will be able to fill this once I figure out how cdk007's code
	//does the mutating.
//	return &ck3;
	int i,j;
	i = rand() %(Clock::rows-1);
	j = rand() %(Clock::columns-1);
	if(round((double)(rand()/RAND_MAX)) <= 0.05)
		c3.genome[i][j] = 1;
	else if((round((double)(rand()/RAND_MAX)) <= 0.1)&&(round((double)(rand()/RAND_MAX)) >= 0.05))
		c3.genome[i][j] = 2;
	else
		c3.genome[i][j] = 0;
	return ck3;  //needs to be &c3
}
*/
