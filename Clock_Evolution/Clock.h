#ifndef CLOCK_H
#define CLOCK_H
/*This holds the declarations of the clock class, which is in Clock.cpp*/

class Clock()
{
public:
	/*flag:  0 = free, 1 = being used (compared, mated, or mutated.)
	  Lock when starting to use, unlock when done.*/
	/*Best practices:
	  Include header guards
	  Do not declare non constant vars in headers.
	  Headers should only be used for declarations.
	  Do not define functions.
	  Headers should have a specific purpose.*/
	bool flag = 0;
	int pendula;
	int arms;
	int generation;
	double score;

	void Clock();
	void ~Clock();
	void show();
private:
	double mrand();
	double genome[40][100];
	int isBound;
	//pathfinding alg.
	//time accuracy.
};

Clock::Clock();  //constructor
Clock::~Clock(); //destructor
void Clock::show()    //debugging
#endif