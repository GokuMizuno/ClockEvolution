#include "stdfax.h"
using std::vector;

int main()
{
	//Initialize random number generator from cstdlib
	srand(time(NULL));

	int proj, generation;
	generation = 0;

	/*Clocklist holds a pointer to each clock.  Compare(*float,*float,*float) draws 3 pointers from this list
	  Using a vector allows for linear element searching
	  Each pointer should have a flag that marks each clock as being used or free.
	  Flag is Clock.flag().  0 = free, 1 = used*/
	vector<Clock> clocklist;  //or is it vector<int> clocklist
	clocklist.reserve(10000);

	/*See if the project is new, or being loaded
	  If loaded, get load function from SaveLoad.cpp*/

	/*There are 10000 clocks in the pool, and we will call a generation done once 10000 matings have been performed.
	The program will terminate after 10,000 generations.  Matings will be done via straight up competition.  We take
	thee clocks and arrange them in their ability to tell time.  The worst of the three is destroyed, and an offspring
	of the two better ones is created in its stead.  The offspring is given a random mutation or two, its generation
	number is updated, and all three are returned to the pool.  Rinse and repeat until done.*/
	/*Since this will eventually be multithreaded and CUDAfied, there should be a way to lock a clock to a core, so
	the same clock is not used more than once in a given time*/
	//Save every 10 generations
	//replace while loop with a for loop; title of save file contains gen. name.
/*	while (gen < 10001)
	{
		//per thread
		int clk_nums[3] = {mrand()*1000, mrand()*1000, mrand*1000};

		do
		{
			if((clk_nums[0] == clk_nums[1])||(clk_nums[0] == clk_nums[2]))
				clk_nums[0] = mrand()*1000;
			else if(clk_nums[1] == clk_nums[2])
				clk_nums[1] = mrand()*1000;
			else
				break;

		/*for each of the three clocks, the number of objects the hands, ratchets, and springs is attached to
		must be checked, as well as the existance of a pendula.  The damn things must then be tested for time
		accuracy, placed in order, then the two best mated.  This must all take place within this while loop,
		due to the scope of the clk_nums.*/
/*		}
		while(1);

		aaa;
	}
*/

	//cout << "Press the t key, then enter, to continue...\n";
	//cin >> proj;
	return 0;
}
