#include "stdfax.h"

ClockPiece::ClockPiece()
{
//	const static int timeInterval[3] = { 60, 3600, 43200 };
	PieceType = rand() % numUniqueParts;
	PieceInterval = 0;
	PendulumLength = 0;
	numTeeth = minGearTeeth;
	isConnected = false;
	isPowered = false;
	isAttachedtoHand = false;

	if (pendulum == PieceType)
	{  PendulumLength = (double)rand() / RAND_MAX;	}
	else if (gear == PieceType)
	{
		numTeeth = rand();
		if (numTeeth < minGearTeeth)
			numTeeth = minGearTeeth;
	}
}

Clock::Clock(int genomeSize)
{
	clockGenome.resize(genomeSize);
	score = 0;
	numHands = 0;
	genesize = genomeSize; //to pass down to children clocks

	/*Fill the genome with random pieces, including null*/
	for (int i = 0; i < genomeSize; i++)
	{
		clockGenome[i].resize(genomeSize);
		for (int j = 0; j < genomeSize; j++)
		{
			ClockPiece temp;
			clockGenome[i][j] = temp;
		}
	}
}

Clock::Clock(Clock Dad, Clock Mom)
{
	score = 0;
	numHands = 0;
	genesize = Dad.genesize;
	clockGenome.resize(genesize);
	mutationRate = Dad.mutationRate;

	for (int i = 0; i < genesize; i++)
	{
		clockGenome[i].resize(genesize);
		for (int j = 0; j < genesize; j++)
		{
			//get genetic code from either mom or dad
			if ((double)rand() / RAND_MAX > 0.5)
			{
				clockGenome[i][j] = Dad.clockGenome[i][j];
			}
			else
			{
				clockGenome[i][j] = Mom.clockGenome[i][j];
			}
			//mutate the sucker
			if (((double)rand() / RAND_MAX) > (1 - (mutationRate / 100)))
			{
				ClockPiece temp;
				clockGenome[i][j] = temp;
			}
			clockGenome[i][j].isConnected = false;
			clockGenome[i][j].setIsPowered(false);
			clockGenome[i][j].setIsAttoHand(false);
			clockGenome[i][j].setPieceInterval(0);
		}
	}
}

double Clock::Score()
{
	int i, j, k, connectedPieces;
	connectedPieces = 0;
	notNullPieces = 0;
	const int timeInterval[3] = { 60, 3600, 43200 };
	bool pendConflict = false;
	bool bestPendonTrain = false;
	const int numScanTimes = 3;
	bool isBroken = false;
	double returnScore = 0.0;
	double pendScore = 0.0;
	double totalGearScore = 0.0;
	double gearScore[3] = { 0, 0, 0 };

	bool isTrainPowered = false;  //gear train powered by a spring

	for (i = 0; i < genesize; i++)
		for (j = 0; j < genesize; j++)
			clockGenome[i][j].setPieceInterval(0);

	//if a piece is alone, then the clock is broken
	for (i = 0; i < genesize && !isBroken; i++)
		for (j = 0; j < genesize; j++)
			if (clockGenome[i][j].getPieceType() != ClockPiece::pnull)
			{
				checkPieceConn(i, j);
				isBroken = true;
				break;
			}

	/*On first scan, count up the total pieces and connected pieces
	  On second scan, check all pendula
	  On third scan, check gear train.  This requires connectedPieces() from first scan*/
	for (k = 1; k <= numScanTimes; k++)
	{
		isBroken = false;
		for (i = 0; i < genesize && !isBroken; i++)
		{
			for (j = 0; j < genesize; j++)
			{
				if (1 == k)
				{
					notNullPieces += (clockGenome[i][j].getPieceType() !=ClockPiece::pnull);
					connectedPieces += (clockGenome[i][j].isConnected && clockGenome[i][j].getPieceType() != ClockPiece::pnull);
				}
				else if (2 == k)
				{
					if (clockGenome[i][j].getPieceType() == ClockPiece::pendulum)
					{
						double currentPendScore = checkPendulum(i, j);
						pendConflict += (bestPendonTrain && isPendonTrain(i, j));

						if (!bestPendonTrain)
						{
							if (currentPendScore > pendScore)
							{
								pendScore = currentPendScore;
								bestPendulum = clockGenome[i][j];
								bestPendonTrain = isPendonTrain(i, j);
							}
						}
					}
				}
				else if (3 == k)
				{
					if (clockGenome[i][j].getPieceType() == ClockPiece::gear && clockGenome[i][j].getPieceInterval() != 0)
					{
						double PendInterval = clockGenome[i][j].getPieceInterval() / (double)clockGenome[i][j].getNumTeeth();
						calcGearInfo(i, j, PendInterval);
						isBroken = true;
						break;
					}
				}
			}
		}
	}

	if (geartrain.size() > 0)
	{
		for (i = 0; i < (signed int)geartrain.size(); i++)
		{
			if (pendConflict)
			{
				totalGearScore = 0;
				gearScore[0] = 0;
				gearScore[1] = 0;
				gearScore[2] = 0;
				geartrain.clear();
				break;
			}
			else
			{
				//only one gear, and powered by spring
				isTrainPowered += geartrain[i].getIsPowered();
				for (j = 0; j < 3; j++)
				{
					double currentGearScore = scorediff(geartrain[i].getPieceInterval(), timeInterval[j]);

					//hand mod
					if (geartrain[i].getIsAtHand())
						currentGearScore *= 100; //changed this value?
					if (currentGearScore > gearScore[j]
						&& timeGears[0].getPieceInterval() != geartrain[i].getPieceInterval()
						&& timeGears[1].getPieceInterval() != geartrain[i].getPieceInterval()
						&& timeGears[2].getPieceInterval() != geartrain[i].getPieceInterval())
					{
						gearScore[j] = currentGearScore;
						timeGears[j] = geartrain[i];
					}
				}
			}
		}
	}

	/*Store number of working hands*/
	numHands = timeGears[0].getIsAtHand() + timeGears[1].getIsAtHand() + timeGears[2].getIsAtHand();

	totalGearScore = gearScore[0] + gearScore[1] + gearScore[2];

	//if the train is powered, add a score multiplier
	if (isTrainPowered)
		totalGearScore *= 100;

	//if gear train exists, add a score multiplier
	if (geartrain.size() > 0)
		totalGearScore *= 10;

	returnScore += totalGearScore;
	returnScore += pendScore;
	returnScore += (geartrain.size() / 100);
	returnScore -= (notNullPieces / 100);

	if (returnScore < 0)
		returnScore = 0;

	score = returnScore;
	geartrain.clear();
	return returnScore;
}

/*
bool hasGearTrain()
{
	return (this.timeGear[0].getPieceInterval() > 0
		|| this.timeGear[1].getPieceInterval() > 0
		|| this.timeGear[2].getPieceInterval() > 0);
}*/

void Clock::checkPieceConn(int x, int y)
{
	clockGenome[x][y].isConnected = true;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
					if (clockGenome[x + i][y + j].getPieceType() != ClockPiece::pnull && clockGenome[x + i][y + j].isConnected == false)
						checkPieceConn(x + i, y + j);
}

double Clock::checkPendulum(int x, int y)
{
	int numConnections = 0;
	double returnScore = 0;

	/*We check to see if the pendula can swing freely by checking adj. pieces*/
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
					if (clockGenome[x + i][y + j].getPieceType() != ClockPiece::pnull)
						numConnections++;
	if (numConnections != 1)
		return 0;
	else
	{
		double pendPeriod = 2 * Pi* sqrt(clockGenome[x][y].getPendulumLength() / g);
		returnScore = scorediff(pendPeriod, (double)1);
		clockGenome[x][y].setPieceInterval(pendPeriod);
		return returnScore;
	}
}

bool Clock::checkRatchet(int x, int y)
{
	int workingPendulums = 0;
	int gears = 0;
	int nullPieces = 0;
	int attachedGearX = 0;
	int attachedGearY = 0;
	int attachedPendulumX = 0;
	int attachedPendulumY = 0;

	/*Check to see if ratchet is attached to only one gear and one pendula*/
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((0 == i) != (0 == j))
			{
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
				{
					if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::pnull)
					{
						nullPieces++;
					}
					if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::pendulum && clockGenome[x + i][y + j].getPieceInterval() != 0)
					{
						workingPendulums++;
						attachedPendulumX = x + i;
						attachedPendulumY = y + j;
					}
					if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::gear)
					{
						gears++;
						attachedGearX = x + i;
						attachedGearY = y + j;
					}
				}
			}
		}
	}

	/*If attached to one working gear, and one pendulum, only*/
	if (workingPendulums == 1 && gears == 1 && nullPieces == 2)
	{
		double attachedPendulumInterval = clockGenome[attachedPendulumX][attachedPendulumY].getPieceInterval();
		int attachedGearNumTeeth = clockGenome[attachedGearX][attachedGearY].getNumTeeth();
		clockGenome[attachedGearX][attachedGearY].setPieceInterval(attachedGearNumTeeth*attachedPendulumInterval);
		return true;
	}
	return false;
}

void Clock::calcGearInfo(int x, int y, double attachedPendulumInterval)
{
	bool ispowered = false;
	bool isconntohand = false;
	double gearInterval = 0;
	
	gearInterval = (double)clockGenome[x][y].getNumTeeth()*attachedPendulumInterval;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
				{
					if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::spring && !ispowered)
						ispowered = checkMainspringorHand(x + i, y + j);
					else if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::hand && !isconntohand)
						isconntohand = checkMainspringorHand(x + i, y + j);
				}

	//is it powered? attached to a hand?  what is the interval?
	clockGenome[x][y].setIsPowered(ispowered);
	clockGenome[x][y].setIsAttoHand(isconntohand);
	clockGenome[x][y].setPieceInterval(gearInterval);

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
					if (clockGenome[x + i][y + j].getPieceType() != ClockPiece::gear && clockGenome[x + i][y + j].getPieceInterval() == 0)
						calcGearInfo(x + i, y + j, attachedPendulumInterval);
	geartrain.push_back(clockGenome[x][y]);
}

bool Clock::checkMainspringorHand(int x, int y)
{
	int attachedPieceCount = 0;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
					attachedPieceCount += (clockGenome[x + i][y + j].getPieceType() != ClockPiece::pnull);
	return (1 == attachedPieceCount);
}

bool Clock::isPendonTrain(int x, int y)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if ((0 == i) != (0 == j))
				if (x + i < genesize && x + i >= 0 && y + j < genesize && y + j >= 0)
					if (clockGenome[x + i][y + j].getPieceType() == ClockPiece::ratchet)
						if (checkRatchet(x + i, y + j))
							return true;
	return false;
}

double Clock::scorediff(double num1, double num2)
{
	double difference = num1 - num2;
	if (difference < 0)
		difference = -difference;
	if (difference < 0.00001)  //account for rounding errors
	{
		difference = 5000000.0;
		return difference;
	}
	return (1/difference);
}

void Clock::show(int num)
{
	for (int x = 0; x < clockGenome.size(); x++)
	{
		for (int y = 0; y < clockGenome.size(); y++)
		{
			ClockPiece output = getClockPiece(x, y);
			if (output.getPieceType() != ClockPiece::pnull)
			{
				if (output.getPieceType() == ClockPiece::ratchet)
					std::cout << "R";
				if (output.getPieceType() == ClockPiece::gear)
					std::cout << "G";
				if (output.getPieceType() == ClockPiece::spring)
					std::cout << "S";
				if (output.getPieceType() == ClockPiece::hand)
					std::cout << "H";
				if (output.getPieceType() == ClockPiece::pendulum)
					std::cout << "P";
			}
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Clock " << num << "has a score of " << Score() << '\n';
	if (0 != Score())
	{
		std::cout << "Pendulum interval:  " << bestPendulum.getPieceInterval() << '\n';
		std::cout << "Second gear interval:  " << getTimeGear(0).getPieceInterval() << '\n';
		std::cout << "Minute gear interval:  " << getTimeGear(1).getPieceInterval() << '\n';
		std::cout << "Hour gear interval:  " << getTimeGear(2).getPieceInterval() << '\n';
		std::cout << "Working second hand:  " << getTimeGear(0).getIsAtHand() << '\n';
		std::cout << "Working minute hand:  " << getTimeGear(1).getIsAtHand() << '\n';
		std::cout << "Working hour hand:  " << getTimeGear(2).getIsAtHand() << '\n';
		std::cout << "Number of pieces: " << notNullPieces << std::endl;
	}
}
