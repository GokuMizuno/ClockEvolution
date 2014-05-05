#include "stdfax.h"
/*This file has both the mating and mutating functions for the clocks.
  Since both are working with the genome of the function, both are
  friends, and hence, it seems natural they go together.*/


/*Mating involves taking the genome of two clocks, and merging them somehow.
  Some ideas are LHs of c1, RHs c2, top c1, bottom c2, completely random
  Try and get an even mix of both parents.
  
  Aftr mating, apply a mutation to the child's genome.*/
Clock mate(Clock c1, Clock c2)
{
	int i,j,k;
	int generation;
	generation = (c1.Generation() > c2.Generation()) ? c1.Generation() : c2.Generation();
	generation++; //gen is one higher than the highest gen parent.
	return c1; //this function should return the child, c3, but as we haven't set that up, it throws an error

};

Clock mutate(Clock &ck3)
{
	//I will be able to fill this once I figure out how cdk007's code
	//does the mutating.
//	return &ck3;
	return ck3;
}