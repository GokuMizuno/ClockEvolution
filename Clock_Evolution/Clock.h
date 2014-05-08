#ifndef CLOCK_H
#define CLOCK_H
/*This holds the declarations of the clock class, which is in Clock.cpp*/
/*Best practices:
  Include header guards
  Do not declare non constant vars in headers.
  Headers should only be used for declarations.
  Do not define functions.
  Headers should have a specific purpose.*/

class Clock
{
public:
	/*flag:  0 = free, 1 = being used (compared, mated, or mutated.)
	  Lock when starting to use, unlock when done.*/
	Clock();	//constructor
	~Clock();	//destructor
	void show();//debugging
	int Generation();
	bool isLocked();
	void Lock();
	void Unlock();
	double Score();
	friend Clock mate(Clock&, Clock&, Clock&);
	friend Clock mutate(Clock&);
	static const int rows = 40;
	static const int columns = 41;
private:
	bool flag;
	double mrand();
	double genome[rows][columns];
	int isBound;
	int generation;
	int pendula;
	int arms;
	double score;
	//pathfinding alg.
	//time accuracy.
};

#endif