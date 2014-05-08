#include "Clock.h"
#include <cmath>  //needed for rand()
#include <iostream> //needed for debugging in Clock::show()

Clock::Clock() //default constructor
{
	/*The cells of the matrix are loaded with mrand(), and manipulated to read 1.0, 2.0, or 0.0 as needed.
	Using a standard mrand() Gaussian distro, all objects with > 3 sigma are given a value of 2.0,
	cells < 3 sigma, but > 2 sigma from norm are given 1.0, and all others are 0.0.  Thus, 95% of
	all cells, that is, gears, ratchets, et al, will do nothing, nor connect to anything.

	In the original paper, rand() is a value between [0,1], and 0.06 or less became 1, whilst
	0.06 to 0.10 became 2, and everything else mapped to 0.  Each gear gets between 4 and 100 teeth.

	Structure of the clock matrix
				row			column
	30 gears:	0:29		0:39	for connectivity
							40		number of teeth
	7 hands		30:36		0:39	connectivity
	1 ratchet	37			0:39	connectivity
	1 spring	38			0:39	connectivity
	1 base		39			0:39	connectivity
	*/

	/*Check gears to make sure number of teeth are greater than items connected to them.
	For k<row, genome[j][k] = genome[k][j]*/

	//This is merely the create function below
	generation = 1;
	flag = 0;
	int cless = columns;
	cless--;
	for(int j=0;j<rows;j++) //rows
	{
		for(int k=0;k<columns;k++) //columns
		{
			if(k == cless)
			{
				genome[j][k] = (rand()%100); //# of teeth per gear <=100
				if(genome[j][k] < 4)
					genome[j][k] = 4;
				for(int l=0;l<columns;l++)
				{
					double sum=0;
					sum += genome[j][l];
					if(genome[j][cless] < sum)
						genome[j][cless] = sum;
				}
			}
			else
			{
				genome[j][k] = mrand();
				if(genome[j][k] > 0.997)
				{
					genome[j][k] = 2.0;
					genome[k][j] = 2.0;
				}
				else if(genome[j][k] > 0.954)
				{
					genome[j][k] = 1.0;
					genome[k][j] = 1.0;
				}
				else
				{
					genome[j][k] = 0.0;
					genome[k][j] = 0.0;
				}
			}
			
		}
	}
}

Clock::~Clock()
{

}

void Clock::show(void)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			std::cout << genome[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

int Clock::Generation()  {  return generation;  }
bool Clock::isLocked()  {  return flag;  }
void Clock::Lock()  {  flag = 1;  }
void Clock::Unlock()  {  flag = 0;  }

double Clock::Score()
{
	/*An arm is worth more than a pendula
	  A pendula is worth more than nothing
	  A perfectly accurate pendula is worth 1.0
	  Bound gears make score == 0
	  Each arm/pendula is worth some multiplier* how accurate it is*/
	//this must return a value, for the moment, it returns 6;
	return 6.0;
}

double Clock::mrand()
{
	double u,v,r;
	do
	{
		u = ((double)rand()/(RAND_MAX))*2-1;
		v = ((double)rand()/(RAND_MAX))*2-1;
		r = u*u + v*v;
	}while(r>1);
	return r;
}