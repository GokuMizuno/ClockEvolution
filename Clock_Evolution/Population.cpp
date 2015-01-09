//#include "stdfax.h"
#include "Population.h"
Population::Population(varData worldData, bool init)
{
	  individuals.reserve(worldData.populationSize);
//	if (init)
//	{
		for (int i = 0; i < worldData.populationSize; i++)
		{
			//Create an individual clock, and push onto the population vector, which we cleverly call individuals
			Clock individual(worldData.genomeSize);
			individual.setMutationRate(worldData.mutationRate);
			individuals.push_back(individual);
		}
//	}
};

void Population::mate(varData worldData)
{

	const int numCompetingClocks = 3;
	const int c1 = 0;
	const int c2 = 1;
	const int leastAccurate = 2;
	//this array holds the indexes and scores of competing clocks
	int clockIndex[numCompetingClocks];
	double clockScores[numCompetingClocks];
	//stupid sexy swapping variables
	int tempIndex;
	double tempScore;

	//holds selected clocks
	int selectedClocks[numCompetingClocks - 1] = { -1, 1 };
	int randClock = 0;

	//in a population of x clocks, a generation is defined by x matings
	for (int competition = 0; competition < worldData.populationSize; competition++)
	{
		for (int i = 0; i < numCompetingClocks; i++)
		{
			//is this do-while loop needed?
			do
			{
				randClock = rand() % worldData.populationSize;

			} while (selectedClocks[0] == randClock || selectedClocks[1] == randClock);
			//don't forget to lock the clock
			if (i != numCompetingClocks)
			{
				selectedClocks[i] = randClock;
			}
			clockIndex[i] = randClock;
//			clockScores[i] = individuals[clockIndex[i]].Score();
			clockScores[i] = individuals[randClock].Score();
			//unlock the clock
		}
		//sorts the clocks by score
		for (int j = 0; j < numCompetingClocks; j++)
		{
			for (int k = 0; k < numCompetingClocks; k++)
			{
				//put in order, both score and index
				if (clockScores[j] < clockScores[k])
				{
					tempScore = clockScores[k];
					clockScores[k] = clockScores[j];
					clockScores[j] = tempScore;

					tempIndex = clockIndex[k];
					clockIndex[k] = clockIndex[j];
					clockIndex[j] = tempIndex;
				}
			}
		}

		//rewrite the least accurate clock with a mated clock from from the more accurate ones
		Clock childClock(individuals[clockIndex[c1]], individuals[clockIndex[c2]]);
		individuals[clockIndex[leastAccurate]] = childClock;
	}
}

void Population::outputVitals(varData worldData)
{
	//need to lock cout stream with a mutex
	std::cout.precision(5);
	double bestPend = 0, secGearInt = 0, minGearInt = 0, hrGearInt = 0,
		avgWorkingParts = 0, secGearHand = 0, minGearHand = 0, hrGearHand = 0,
		avgScore = 0, numDead = 0, numPend = 0, numGear = 0;
	std::vector<int> numHandsClock;
	numHandsClock.reserve(5);

	for (int i = 0; i < worldData.populationSize; i++)
	{
		avgScore += individuals[i].Score();
		if (individuals[i].Score() != 0)
		{
			bestPend += individuals[i].getBestPendulum().getPieceInterval();
			secGearInt += individuals[i].getTimeGear(0).getPieceInterval();
			minGearInt += individuals[i].getTimeGear(1).getPieceInterval();
			hrGearInt += individuals[i].getTimeGear(2).getPieceInterval();
			secGearHand += individuals[i].getTimeGear(0).getIsAtHand();
			minGearHand += individuals[i].getTimeGear(1).getIsAtHand();
			hrGearHand += individuals[i].getTimeGear(2).getIsAtHand();
			avgWorkingParts += individuals[i].getNotNullPieces();
		}
		numDead += (individuals[i].Score() == 0);
		if (individuals[i].getBestPendulum().getPieceInterval() != 0 && individuals[i].getNumHands() == 0)
			numGear++;
		numHandsClock[individuals[i].getNumHands()] += 1;
	}

	//Get the averages
	avgScore /= (worldData.populationSize - numDead);
	bestPend /= (worldData.populationSize - numDead);
	secGearInt /= (worldData.populationSize - numDead);
	minGearInt /= (worldData.populationSize - numDead);
	hrGearInt /= (worldData.populationSize - numDead);
	secGearHand /= (worldData.populationSize - numDead);
	minGearHand /= (worldData.populationSize - numDead);
	hrGearHand /= (worldData.populationSize - numDead);
	avgWorkingParts /= (worldData.populationSize - numDead);
	
	std::cout << "Average score for generation: " << worldData.currentGeneration << " is " << avgScore << '\n';
	std::cout << "Average pendulum accuracy: " << bestPend << '\n';
	std::cout << "Average second gear accuracy: " << secGearInt << '\n';
	std::cout << "Average minute gear accuracy: " << minGearInt << '\n';
	std::cout << "Average hour gear accuracy: " << hrGearInt << '\n';
	std::cout << "Average second hands: " << secGearHand << '\n';
	std::cout << "Average minute hands: " << minGearHand << '\n';
	std::cout << "Average hour hands: " << hrGearHand << '\n';
	for (int j = 0; j < numHandsClock.size(); j++)
		std::cout << "Average number of clocks with " << j << " hands: " << numHandsClock[j] << '\n';
	std::cout << "Average number of working parts: " << avgWorkingParts << std::endl;
};
