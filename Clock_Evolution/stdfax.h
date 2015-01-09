#ifndef STDFAX_H
#define STDFAX_H
#include <time.h> //seed rand with srand(time(NULL))
//#include <string> //needed for string to store user data, save file location
#include <iostream> //replace later with fstream
//#include <fstream>
#include <cstdlib> //rand()
#include <vector>
#include "clock.h"
#include "Population.h"

struct varData
{
	varData();
	int numGenerations;
	int currentGeneration;
	int genomeSize;
	int populationSize;
	double mutationRate;
	char fileloc[255];
};

#ifndef Pi
#define Pi 3.14159265358979323846
#endif
#ifndef g
#define g 9.81
#endif

#endif