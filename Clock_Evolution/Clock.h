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
	int pendula;
	int arms;
	double score;

	void Clock();
	void ~Clock();
	void show()
	int Generation();
	bool isLocked();
	bool Lock();
	bool Unlock();
private:
	bool flag;
	double mrand();
	double genome[40][100];
	int isBound;
	int generation;
	//pathfinding alg.
	//time accuracy.
};

Clock::Clock();  //constructor
Clock::~Clock(); //destructor
Clock::show();   //debugging
int Generation()  {  return generation;  }
bool isLocked()  {  return flag;  }
bool Lock()  {  flag = 1;  }
bool Unlock()  {  flag = 0;  }

#endif