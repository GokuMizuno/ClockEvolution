#ifndef CLOCK_H
#define CLOCK_H
#include "stdfax.h"
/*This holds the declarations of the clock class, which is in Clock.cpp*/
/*Best practices:
  Include header guards
  Do not declare non constant vars in headers.
  Headers should only be used for declarations.
  Do not define functions.
  Headers should have a specific purpose.*/

class ClockPiece
{
	friend class Clock;
private:
	enum parts { pnull, ratchet, spring, gear, hand, pendulum};
	int numUniqueParts = 6;
	int minGearTeeth = 4;
	//static const int timeInterval[3] = { 60, 3600, 43200 }; //min,hr,day
	const static int timeInterval[3];
	int PieceType;
	double PendulumLength; //less than 1
	double PieceInterval;  //pendulum and gear rotational period
	int numTeeth;
	bool isPowered;
	bool isAttachedtoHand; //if a gear is attached to a hand (powers hand)
public:
	bool isConnected;
	int getPieceType()  { return PieceType; };
	double getPendulumLength() { return PendulumLength; };
	double getPieceInterval() { return PieceInterval; };
	int getNumTeeth() { return numTeeth; };
	bool getIsPowered() { return isPowered; };
	bool getIsAtHand() { return isAttachedtoHand; };
	void setPieceInterval(double pieceInterval) { PieceInterval = pieceInterval; };
	void setIsPowered(bool ispowered) { isPowered = ispowered; };
	void setIsAttoHand(bool isathand) { isAttachedtoHand = isathand; };
	ClockPiece();
};
class Clock
{
public:
	/*flag:  0 = free, 1 = being used (compared, mated, or mutated.)
	  Lock when starting to use, unlock when done.*/
	Clock(int);	//constructor
	Clock(Clock, Clock);
	double Score();
	double scorediff(double, double);
	void setMutationRate(double mRate) { mutationRate = mRate; };
	ClockPiece getClockPiece(int x, int y) { return clockGenome[x][y]; };
	ClockPiece getBestPendulum() { return bestPendulum; };
	ClockPiece getTimeGear(int index) { return geartrain[index]; };
	int getNotNullPieces() { return notNullPieces; };
	//double getSurvivalScore() {return score;};
	int getNumHands() { return numHands; };
	bool hasGearTrain() { timeGears[0].getPieceInterval() > 0 || timeGears[1].getPieceInterval() > 0 || timeGears[2].getPieceInterval() > 0; };
	~Clock();	//destructor
	void show();//debugging
	int generation();
	void generation(int);
	bool isLocked();
	void Lock();
	void unLock();
protected:
	int genesize;
	double mutationRate;
	bool flag;
private:
	std::vector<std::vector<ClockPiece>> clockGenome;
	std::vector<ClockPiece> geartrain;
	ClockPiece bestPendulum;
	ClockPiece timeGears[3]; //stores the second, minute, and hour gears
	int numHands;
	int notNullPieces;  //num of genome spots that are filled with ClockPieces
	/*Next three are contained in doPhysics()*/
	void checkPieceConn(int, int);
	double checkPendulum(int, int);
	bool isPendonTrain(int, int);
	bool checkRatchet(int, int);
	void calcGearInfo(int, int, double);
	bool checkMainspringorHand(int, int);
	double mrand();  //from here on out, is old work
	void doPhysics();
	int isBound;
	int gen;
	int pendula;
	int arms;
	double score;
};

#endif