#ifndef CLOCK_H
#define CLOCK_H
/*This holds the declarations of the clock class, which is in Clock.cpp*/

class Clock()
{
public:
	/*flag:  0 = free, 1 = being used (compared, mated, or mutated.)
	  Lock when starting to use, unlock when done.*/
	bool flag = 0;
	int pendula;
	int arms;
	int generation;
	double score;
private:
	double mrand();
	double genome[40][41];
	int isBound;
	//pathfinding alg.
	//time accuracy.
};
#endif