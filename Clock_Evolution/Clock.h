#ifndef CLOCK_H
#define CLOCK_H
/*This holds the declarations of the clock class, which is in Clock.cpp*/

class Clock
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
	Clock();	//constructor
	~Clock();	//destructor
	void show();//debugging
	int Generation();
	bool isLocked();
	void Lock();
	void Unlock();
	double Score();
	friend Clock mate(Clock, Clock);
	friend Clock mutate(Clock&);
private:
	bool flag;
	double mrand();
	double genome[40][100];
	int isBound;
	int generation;
	int pendula;
	int arms;
	double score;
	//pathfinding alg.
	//time accuracy.
};

#endif