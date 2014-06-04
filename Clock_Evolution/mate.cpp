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

//void mate(Clock ptr) //error:  cannot pass an array of references.
void mate(Clock ck0, Clock ck1, Clock ck2)
//mate(vector<int> ptrlist)
{
//	Clock *spl[3]; //sorted plist

/*if (x < y)
  { if (z < x) swap(x,z); 
  } 
  else 
  { if (y < z) swap(x,y); 
    else swap(x,z); 
  }
  if(z<y) swap(y,z); 

	if(ck0.score() < ck1.score)
	{
		if(plist[2].score() < plist[0].score())
			spl[2] = plist[2];
		else
			spl[2] = plist[0];
	}
	else
		spl[2] = plist[0];

	//*plist[2] = ;//actual mating
	
	int i,j,k;
	int generation;
	generation = (*spl[0].Generation() >= spl[1].Generation()) ? spl[0].Generation() : spl[1].Generation();
	generation++; //gen is one higher than the highest gen parent.
	for(int i=0;i<Clock::rows;i++)
	{
		for(int j=0;j<Clock::columns;j++)
		{
			if(round((double)(rand()/RAND_MAX)) == 0)
				spl[2].genome[i][j] = spl[0].genome[i][j];
			else
				spl[2].genome[i][j] = spl[1].genome[i][j];
		}
	}
	spl[2].generation = generation;
	mutate(&spl[2]);
	*/
}

void mutate(Clock &ck3)
{
	for(int i = (Clock::rows-2); i>=0;i--)
		for(int j = (Clock::columns-2);j>=0;j--)
		{
			double mutround = round((double)(rand()/RAND_MAX));
				if(mutround <= 0.05)
					ck3.genome[i][j] = 1;
				else if((mutround <= 0.1)&&(mutround >= 0.05))
					ck3.genome[i][j] = 2;
				/*else
					ck3.genome[i][j] = ck3.genome[i][j];*/
		}
		ck3.doPhysics();
	//return ck3;  //needs to be &ck3
	/*If dealing with pointers, make return type void, and let pointers change ck3 dynaimcally*/
}
