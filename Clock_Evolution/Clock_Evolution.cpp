#include "stdfax.h"
using std::vector;

double round(double);

int main()
{
	//Initialize random number generator from cstdlib
	srand(time(NULL));

	int fromfile, generation, total_clocks, current_mating;
	generation = 0;
	current_mating = 0;
	total_clocks = 100;  //debugging.  Allow to change

	/*Clocklist holds a pointer to each clock.  Compare(*float,*float,*float) draws 3 pointers from this list
	  Using a vector allows for linear element searching
	  Each pointer should have a flag that marks each clock as being used or free.
	  Flag is Clock.flag().  0 = free, 1 = used*/
	//vector<Clock> clocklist;  //or is it vector<int> clocklist
	//clocklist.reserve(10000);

	/*See if the project is new, or being loaded
	  this is what the fromfile variable is for.  Currently not implemented.
	  If loaded, get load function from SaveLoad.cpp*/

	/*There are X clocks in the pool, and we will call a generation done once X matings have been performed.
	The program will terminate after X generations.  Matings will be done via straight up competition.  We take
	thee clocks and arrange them in their ability to tell time.  The worst of the three is destroyed, and an offspring
	of the two better ones is created in its stead.  The offspring is given a random mutation or two, its generation
	number is updated, and all three are returned to the pool.  Rinse and repeat until done.*/
	/*Since this will eventually be multithreaded and CUDAfied, there should be a way to lock a clock to a core, so
	the same clock is not used more than once in a given time*/
	//Save every 10 generations
	//replace while loop with a for loop; title of save file contains gen. name.

	Clock *foo;
	foo = new Clock[total_clocks];
	for(int n=0;n<2;++n)
	{
		std::cout << "Clock " << n << std::endl;
		foo[n].show();
	}

	mutate(foo[0]);
	foo[0].show();
	/*
	while(generation < total_clocks) //generation
	{
		while(current_mating < total_clocks) //matings per generation
		{
			vector<int> nums;
			Clock plist[3]; //replace with array that holds addresses, and pass that array?
			Clock *ptr = plist;
			for(int i=0;i<3;i++)
			{
				nums.push_back(rand()%total_clocks);
				if(foo[nums.at(i)].isLocked() == 0)
				{
					foo[i].Lock();
					plist[i] = foo[i];
				}
				else
					i--;  //repeat
			}
			mate(plist[0],plist[1],plist[2]);//the list of the three locked clocks.
			for(int i=0;i<3;++i)
				foo[i].Unlock();

			current_mating++;
		}
		generation++;
	}*/

	delete[] foo;
	return 0;
}

double round(double num)
{
	/*Theoretically, num will be between [0,1], but we all know how well
	  theory and reality mesh...
	  (double)(rand()/RAND_MAX) will always return a value betwen [0,1]*/
	if(num <= 0.5)  return 0.0;
	else  return 1.0;
}
