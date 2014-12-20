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
	void generate();  //should this be generate(int row,int column);?
	void show();//debugging
	int generation();
	void generation(int);
	bool isLocked();
	void lock();
	void unlock();
	double score();
	void setDimensions(int, int);
	friend void mate(Clock&, Clock&, Clock&);
	friend void mate(Clock*);
	friend void mutate(Clock&);
	class Heutristic
	{
		virtual void Start(int, int) = 0;
		virtual int Calculate(int, int) = 0;
		virtual bool IsGoal() { return true; };
		virtual bool IsCancel(int) = 0;  //is this needed?
		virtual bool Step() = 0;
		virtual ~Heutristic(){};
	};
protected:
	bool flag;
	static int rows = 40;
	static int columns = 41;
	double mrand();
	void doPhysics();
	int gene[rows][columns];
	int isBound;
	int gen;
	int pendula;
	int arms;
	double score; = 0
private:
	//pathfinding alg.
	int circuit(int, int);
	std::vector<int> returnVector(int, int, std::vector<int>&);
	//time accuracy.
};

#endif