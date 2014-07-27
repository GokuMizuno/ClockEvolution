#ifndef graph.h
#define graph.h
#include "stdafx.h"

/*This file contains all the struct and class decs for graph.cpp*/
struct AScore
{
public:
	AScore();
	double g, h, f;
};

struct ACell
{
	ACell();
	unsigned x, y;
	bool operator < const;
	bool enable;
};

struct Vector
{
	Vector();
	void Normalize();
	double Length();
	double AngleWith(Vector);
	double SignAngleWith(Vector);
	double x, y;
};

class AStar
{
public:
	class Heuristic
	{
	public:
		virtual void Start(ACell, ACell);
		virtual double Calculate(ACell, ACell, double);
		virtual bool IsGoal();
		virtual bool IsStop();
		virtual bool IsCancel();
		virtual void Step();
		virtual ~Heuristic();
	};
	AStar();
	void SetHeuristic();
	bool IsReady();
	void Initialize(unsigned, unsigned, double);
	bool Find(ACell, ACell, std::vector<std::vector<double> >, std::list<ACell>);
private:
	void Reconstruct(ACell, ACell, std::list<ACell>);
	Heuristic *h;
	std::vector<std::vector<bool> > Closed, Open;
	std::vector<std::vector<double> > Score;
	std::vector<std::vector<ACell> > From;
	double Factor;
	bool Ready;
};

#endif 