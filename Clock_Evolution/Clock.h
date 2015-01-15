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
	//Since VS13 cannot compile the below line, I fudged it by adding it to Clock::Score()
	//static const int timeInterval[3] = { 60, 3600, 43200 }; //min,hr,day
	int PieceType;
	double PendulumLength; //less than 1
	double PieceInterval;  //pendulum and gear rotational period
	int numTeeth;
	bool isPowered;
	bool isAttachedtoHand; //if a gear is attached to a hand (powers hand)
public:
	ClockPiece();// :timeInterval({ 60, 3600, 43200 }) {};
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
	//ClockPiece();
};
class Clock
{
public:
	Clock(int);	//constructor
	Clock(Clock, Clock);
	double Score();
	double scorediff(double, double);
	void setMutationRate(double mRate) { mutationRate = mRate; };
	ClockPiece getClockPiece(int x, int y) { return clockGenome[x][y]; };
	ClockPiece getBestPendulum() { return bestPendulum; };
	ClockPiece getTimeGear(int index) { return timeGears[index]; };
	int getNotNullPieces() { return notNullPieces; };
	int getNumHands() { return numHands; };
	bool hasGearTrain() { timeGears[0].getPieceInterval() > 0 || timeGears[1].getPieceInterval() > 0 || timeGears[2].getPieceInterval() > 0; };
	//~Clock();	//destructor
	void show(int);
	int generation();
	void generation(int);
protected:
	int genesize;
	double mutationRate;
private:
	std::vector<std::vector<ClockPiece>> clockGenome;
	std::vector<ClockPiece> geartrain;
	ClockPiece bestPendulum;
	ClockPiece timeGears[3]; //stores the second, minute, and hour gears
	int numHands;
	int notNullPieces;  //num of genome spots that are filled with ClockPieces
	void checkPieceConn(int, int);
	double checkPendulum(int, int);
	bool isPendonTrain(int, int);
	bool checkRatchet(int, int);
	void calcGearInfo(int, int, double);
	bool checkMainspringorHand(int, int);
	double score;
};

#endif