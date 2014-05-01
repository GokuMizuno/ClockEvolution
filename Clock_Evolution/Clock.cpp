#include "Clock.h";

class Clock {
private:
	/*Structure of the clock matrix
	30 gears:	rows 1:30	columns 1:40
	if the cell is 1, it is connected by teeth, 2 by axle, 0 = all else
	columns 41:100 hold number of teeth
	7 hands:	rows 31:37	columns 1:40 = connectivity
	1 ratchet:	row 38		columns 1:40 = connectivity
	1 spring:	row 39		columns 1:40 = connectivity
	1 base:		row 40		columns 1:40 = connectivity
	*/
	double genome[40][41];
	double mrand();
public:
	int gen, num; //gen is the clock creation generation, num is the number 1-1000 of the clock.
	float time, score[7];
	Clock(bool, int); //Default constructor: 0 is create new, 1 is load from a file
//	~Clock();
	void show(void);
	float eval(void);
};

Clock::Clock(bool create, int i)
{
	/*The cells of the matrix are loaded with mrand(), and manipulated to read 1.0, 2.0, or 0.0 as needed.
	Using a standard mrand() Gaussian distro, all objects with > 3 sigma are given a value of 2.0,
	cells < 3 sigma, but > 2 sigma from norm are given 1.0, and all others are 0.0.  Thus, 95% of
	all cells, that is, gears, ratchets, et al, will do nothing, nor connect to anything.

	In the original paper, rand() is a value between [0,1], and 0.06 or less became 1, whilst
	0.06 to 0.10 became 2, and everything else mapped to 0.
	*/

	/*Ways to cheat:  Just use three clocks and constantly compare.
	The use of k>=j makes the matrices bidirectional. by setting ck[j][k] = ck[k][j].
	Check gears to make sure number of teeth are greater than items connected to them.*/
/*	new int num, gen;
	new float ck[40][41];
	new float time, score[7];*/
	//This is merely the create function below
	if(create == 0)
	{
		num = i;
		gen = 1;
		for(int j=0;j<40;j++)
		{
			for(int k=j;k<41;k++)
			{
				if(k == 40)
				{
					ck[j][k] = (int)(mrand()*100); //# of teeth/gear <=100
					//checks numbers of gears vs. teeth in gears
					for(int l=0;l<40;l++)
					{
						float sum=0;
						sum += ck[j][l];
						if(ck[j][40] < sum)
							ck[j][40] = sum;
					}
				}
				else
				{
					ck[j][k] = mrand();
					if(ck[j][k] > 0.997)
					{
						ck[j][k] = 2.0;
						ck[k][j] = 2.0;
					}
					else if(ck[j][k] > 0.954)
					{
						ck[j][k] = 1.0;
						ck[k][j] = 1.0;
					}
					else
					{
						ck[j][k] = 0.0;
						ck[k][j] = 0.0;
					}
				}
			}
		}
	}
	else //create == 1
	{
		//other stuff
	};
}

/*Clock::~Clock()
{
	delete float ck[40][41];
	delete int gen, num;
	delete float time, score[6];
}*/

void Clock::show(void)
{
	for(int i=0;i<40;i++)
	{
		for(int j=0;j<41;j++)
		{
			cout << ck[i][j] << '\t';
		}
		cout << endl;
	}
}

float Clock::eval(void)
{
	/*score[0] stores the total number of intersections between components.  More intersections mean more complexity
	and more complexity means more energy goes into building the device.  All else being equal. the clock with the
	less complexity wins
	Scores 1-6 are used to hold the object d'art's scores for seconds, minutes, hours, days, weeks, and years.
	The more accurate, the higher the score.  Pendula are base ranked, and hands provide a score modifier.  The
	pendulum provides the base motion, without one, there is no clock.  Circuits are evaluated to modify gear
	ratios as evolutionary advantagious to provide a better clock.*/
	bool pendula = false;

	//aaa;
}
