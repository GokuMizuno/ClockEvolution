#include "stdfax.h";
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

/*	cout << "Is this:\n (1)A new project\n (2)An existing project?\n";
	cin >> proj;
	if (proj == 2)
	{  Load();  }
	else if (proj == 1)*/
		fstream myfile;
	myfile.open("matrix test.txt", ios::out);
	if(myfile)
	{
		for(int i=1;i<3;i++)
		{
			Clock clk(0,i);
			myfile << clk.show();
		}
	}
	myfile.close();
/*	else
	{
		cout << "Input unexpected, terminating.  Oh those poor, wasted CPU cycles.\n";
		_exit(1);
	}*/

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
	

float mrand()
{
	float u = ((float)rand()/(RAND_MAX))*2-1;
	float v = ((float)rand()/(RAND_MAX))*2-1;
	float r = u*u + v*v;
	if ((r==0)||(r>1))
		return r;
	float c = sqrt(-2 * log(r)/r);
	return r;
}