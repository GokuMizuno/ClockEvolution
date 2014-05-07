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
	0.06 to 0.10 became 2, and everything else mapped to 0.
	*/

	/*Check gears to make sure number of teeth are greater than items connected to them.
	For k<40, genome[j][k] = genome[k][j]*/
/*	new int num, gen;
	new float genome[40][41];
	new float time, score[7];*/
	//This is merely the create function below
	for(int j=0;j<rows;j++) //rows
	{
		for(int k=0;k<columns;k++) //columns
		{
			if(k >= 40)
			{
				genome[j][k] = (rand()%100); //# of teeth per gear <=100
				for(int l=0;l<40;l++)
				{
					double sum=0;
					sum += genome[j][l];
					if(genome[j][40] < sum)
						genome[j][40] = sum;
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
//	delete float genome[40][41];
//	delete int gen, num;
//	delete float time, score[6];
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

/*float Clock::eval(void)
{
	/*score[0] stores the total number of intersections between components.  More intersections mean more complexity
	and more complexity means more energy goes into building the device.  All else being equal. the Clock with the
	less complexity wins
	Scores 1-6 are used to hold the object d'art's scores for seconds, minutes, hours, days, weeks, and years.
	The more accurate, the higher the score.  Pendula are base ranked, and hands provide a score modifier.  The
	pendulum provides the base motion, without one, there is no Clock.  Circuits are evaluated to modify gear
	ratios as evolutionary advantagious to provide a better Clock.*/
/*	bool pendula = false;

	//aaa;
}*/

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
	double u = ((float)rand()/(RAND_MAX))*2-1;
	double v = ((float)rand()/(RAND_MAX))*2-1;
	double r = u*u + v*v;
	if ((r==0)||(r>1))  return r;
	double c = sqrt(-2 * log(r)/r);
	return c;
}