#include "stdfax.h"

/*Mating involves taking the genome of two clocks, and merging them somehow.
  Some ideas are LHs of c1, RHs c2, top c1, bottom c2, completely random
  Try and get an even mix of both parents.
  
  Aftr mating, apply a mutation to the child's genome.*/
Clock mate(Clock c1, Clock c2)
{
	int i,j,k;
	int generation;
	generation = (c1.Generation() > c2.Generation()) ? c1.Generation() : c2.Generation();
	generation++; //gen is one older than the highest gen parent.

};