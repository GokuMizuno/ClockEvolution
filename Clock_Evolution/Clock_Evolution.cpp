#include "stdfax.h"
#include "Population.h"

varData GetWorldData();

int main()
{
	//Initialize random number generator from cstdlib
	srand(time(NULL));

	/*See if it is a new run, or loading from a file.*/

	varData worldData;
	/*New data*/
	worldData = GetWorldData();
	/*From file*/
	/*Get the bloody thing working first, then get save/load working*/
	//worldData = SaveLoad(1); //0 for save, 1 for load
	/*Need to return both world data, as well as a vector of clocks*/

	/*There are X clocks in the pool, and we will call a generation done once X matings have been performed.
	The program will terminate after X generations.  Matings will be done via straight up competition.  We take
	thee clocks and arrange them in their ability to tell time.  The worst of the three is destroyed, and an offspring
	of the two better ones is created in its stead.  The offspring is given a random mutation or two, its generation
	number is updated, and all three are returned to the pool.  Rinse and repeat until done.*/
	/*Since this will eventually be multithreaded and CUDAfied, there should be a way to lock a clock to a core, so
	the same clock is not used more than once in a given comparison*/
	//Save every 10 generations

	Population clockPop(worldData, 0);
	
	while(worldData.currentGeneration < worldData.numGenerations) //generation
	{
		clockPop.mate(worldData);
		if (worldData.currentGeneration & 0x8)
			clockPop.showClock(2); //shows clock #2 every 8th generation
		clockPop.outputVitals(worldData);
		worldData.currentGeneration++;
	}

	return 0;
}

varData GetWorldData()
{
	varData data;
	bool flag = true;
	int num;
	/*Defaults*/
	data.currentGeneration = 0;
	data.numGenerations = 1000;
	data.genomeSize = 10;
	data.mutationRate = 0.1;
	data.populationSize = 1000;
	strcpy_s(data.fileloc, "clockdata.dat");

	do
	{
		std::cout << "Type the number in front of the data you would like to change.  0 begins the simulation.\n";
		std::cout << "1 = Number of generations " << data.numGenerations << std::endl;
		std::cout << "2 = Size of the population " << data.populationSize << std::endl;
		std::cout << "3 = Size of the genome " << data.genomeSize << std::endl;
		std::cout << "4 = The mutation rate is " << data.mutationRate << std::endl;
		std::cout << "5 = Name and relative path of save file " << data.fileloc << std::endl;
		std::cin >> num;
		switch (num)
		{
		case 1:
			std::cout << "Please enter the number of generations.\n";
			std::cin >> num;
			if (num <= 0)
			{
				std::cout << "Haha.  Loading a trunk monkey in your car.\n";
				data.numGenerations = 1;
			}
			else
			{
				data.numGenerations = num;
			}
			break;
		case 2:
			//This needs to be changed to accomodate number of cores
			std::cout << "Please enter the size of the population.\n";
			std::cin >> num;
			if (num <= 0)
			{
				std::cout << "Haha.  Loading a trunk monkey in your car.\n";
				data.populationSize = 3;
			}
			else
			{
				data.populationSize = num;
			}
			break;
		case 3:
			std::cout << "Please enter the size of the genome.\n";
			std::cin >> num;
			if (num <= 0)
			{
				std::cout << "Haha.  Loading a trunk monkey in your car.\n";
				data.genomeSize = 1;
			}
			else
			{
				data.genomeSize = num;
			}
			break;
		case 4:
			std::cout << "Please enter the mutation rate as a whole number.  (rate of 0.5 is entered as 50.)\n";
			std::cin >> num;
			if ((num <= 0) || (num > 100))
			{
				std::cout << "Haha.  Loading a trunk monkey in your car\n";
				data.mutationRate = 0.1;
			}
			else
			{
				data.mutationRate = (double)num / 100;
			}
			break;
		case 5:
			char input[255];
			std::cout << "For ease of access, the save file should be in the same directory as the program."
				<< "  If you want to change the name of the file, feel free to do so here.\n";
			std::cin >> input;
			std::cin.ignore(80, '\n');
			strcpy_s(data.fileloc, input);
			break;
		case 0:
		default:
			flag = false;
			break;
		}
	} while (flag);

	return data;
}
