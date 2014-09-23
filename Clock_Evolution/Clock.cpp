#include "stdfax.h"

Clock::Clock() //default constructor
{
	{
		/*The cells of the matrix are loaded with mrand(), and manipulated to read 1.0, 2.0, or 0.0 as needed.
		Using a standard mrand() Gaussian distro, all objects with > 3 sigma are given a value of 2.0,
		cells < 3 sigma, but > 2 sigma from norm are given 1.0, and all others are 0.0.  Thus, 95% of
		all cells, that is, gears, ratchets, et al, will do nothing, nor connect to anything.

		In the original paper, rand() is a value between [0,1], and 0.06 or less became 1, whilst
		0.06 to 0.10 became 2, and everything else mapped to 0.  Each gear gets between 4 and 100 teeth.

		Structure of the clock matrix
		row			column
		30 gears	0:29		0:39	for connectivity
		0:29		40		number of teeth
		7 hands		30:36		0:39	connectivity
		1 ratchet	37			0:39	connectivity
		1 spring	38			0:39	connectivity
		1 base		39			0:39	connectivity
		*/

		/*Check gears to make sure number of teeth are greater than items connected to them.
		For k<row, gene[j][k] = gene[k][j]*/

		//This is merely the create function below
		generation = 1;
		flag = 0;
		for (int j = 0; j<rows; j++) //rows
		{
			for (int k = j; k<columns; k++) //columns
			{
				if (k == (columns - 1))
				{
					gene[j][k] = (rand() % 100); //# of teeth per gear <=100
					if (gene[j][k] < 4)
						gene[j][k] = 4;
					for (int l = 0; l<columns; l++)
					{
						int sum = 0;
						sum += gene[j][l];
						if (gene[j][cless] < sum)
							gene[j][cless] = sum;
					}
				}
				else
				{
					if (mrand() > 0.997)
						gene[j][k] = 2;
					else if ((mrand() > 0.954) && (mrand() < 0.997))
						gene[j][k] = 1;
					else
						gene[j][k] = 0;
				}
			}
		}
	}

}
Clock::~Clock()
{

}

class Clock
{
	void generate()
	{
		/*The cells of the matrix are loaded with mrand(), and manipulated to read 1.0, 2.0, or 0.0 as needed.
		Using a standard mrand() Gaussian distro, all objects with > 3 sigma are given a value of 2.0,
		cells < 3 sigma, but > 2 sigma from norm are given 1.0, and all others are 0.0.  Thus, 95% of
		all cells, that is, gears, ratchets, et al, will do nothing, nor connect to anything.

		In the original paper, rand() is a value between [0,1], and 0.06 or less became 1, whilst
		0.06 to 0.10 became 2, and everything else mapped to 0.  Each gear gets between 4 and 100 teeth.

		Structure of the clock matrix
		object		row			column
		30 gears	0:29		0:39	for connectivity
		""			0:29		40		number of teeth
		7 hands		30:36		0:39	connectivity
		1 ratchet	37			0:39	connectivity
		1 spring	38			0:39	connectivity
		1 base		39			0:39	connectivity
		*/

		/*Check gears to make sure number of teeth are greater than items connected to them.
		For k<row, gene[j][k] = gene[k][j]*/

		//This is merely the create function below
		generation = 1;
		flag = 0;
		for (int j = 0; j<rows; j++) //rows
		{
			for (int k = j; k<columns; k++) //columns
			{
				if (k == j)  //no object can touch itself, so we zero the identity matrix
				{
					gene[j][k] = 0;
				}
				if (k == (columns-1))
				{
					gene[j][k] = ((rand() % 96 + 4)); //# of teeth per gear in range [4,100]
					for (int l = 0; l<columns; l++)
					{
						int sum = 0;
						sum += gene[j][l];
						if (gene[j][(column -1)] < sum)
							gene[j][(column -1)] = sum;
					}
				}
				else
				{
					if (mrand() > 0.997)
					{
						gene[j][k] = 2;
						gene[k][j] = 2;
					}
					else if ((mrand() > 0.954) && (mrand() < 0.997))
					{
						gene[j][k] = 1;
						gene[k][j] = 1;
					}
					else
					{
						gene[j][k] = 0;
						gene[k][j] = 0;
					}
				}
			}
		}
	}
	void setDimensions(int x, int y)
	{
		rows = x;
		columns = y;
	}
	void Clock::show(void)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				std::cout << gene[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}
	int generation()  { return generation; }
	void generation(int newGen)  { generation = newGen; }
	bool isLocked()  { return flag; }
	void lock() { flag = 1; }
	void unlock() { flag = 0; }
	double mrand()
	{
		double u, v, r;
		do
		{
			u = ((double)rand() / (RAND_MAX)) * 2 - 1;
			v = ((double)rand() / (RAND_MAX)) * 2 - 1;
			r = u*u + v*v;
		} while (r>1);
		return r;
	}

};


double Clock::Score()
{
	double score, physics;
	int gears, pendula, arms;  //number of each

	score = 0;
	/*An arm > pendula > nothing
	  All gears bound make score == 0
	  Each arm/pendula is worth some multiplier times how accurate it is*/
	/*First begin with a circuit algol.
	  Then do time accuracy*/
	
	//The circuit_distance.m function finds the shortest path between every
	// pair of gears.
	/*for(int i=;;)
	{
		for(int j=;;)
			something[i][j] = circuit(gconn2,baseg);
	}*/
	
	//in an nxm array, length is n>m?n:m  equal to max(size(array))
	for g=1:length(baseg)
		keepg = ~isnan(d2(baseg(g),:)); //what. the. hell?
	keep(keepg==1) = 1;
	end

	for(int g=0;g<=40;++g) //c++
	{}

	double conn[40][41], gconn[30][30];
	for(int a=0;a<40;++a)
		for(int b=0;b<30;++b)
			conn[a][b] = 0.0;
	for(int a=0;a<30;++a)
		for(int b=0;b<30;++b)
			gconn[a][b] = 0.0;
	
	for(int a=0;a<40;++a)
	{
		for(int b=0;b<30;++b)
		{
			if(keep[a][b] == 1)
				conn[a][b] = 1;
			if((a<30)&&(b<30))
				gconn[a][b] = conn[a][b];
		}
	}

	for(int r=0;r<30;++r)
	{
		if(keep[r] == 0)
		{
			for(int a=0;a<30;++a)
			{
				gconn[r][a] = 0;
				gconn[a][r] = 0;
			}
		}
	}


/* Check for a pendulum: a hand that is attached to the base
% that hand may be attached to a gear, but that gear cannot
% be attached to anything else. In this simple simulation a pendulum is
% the only form that can create regular motion, this is a simple fact.
% If we don't find one there is no need to go on as the clock will not
% work no matter how the remaining components are connected.
*/
	int p_count = 0;  //number of pendula
	double s = 0;
	double pend[6][3];
	std::vector<double> g;
	std::vector<double> g2;

	for(int h=0;h<7;++h)
		for(int a=0;a<3;++a)
			pend[h][a] = 0;

	for(int h=30;h<37;++h)
	{
		if(conn[40][h] != 0)
		{
			for(int a=0;a<30;++a)
			{
				if(conn[h][a] != 0)
					g.push_back(conn[h][a]);
			}
			//g=find(conn(h,1:30) != 0);  //see if the base/hand combo is attached to a gear
			if(g.size() == 0) // no pendula
				continue;
		}

		for(int a=0;a<40;++a)
		{
			if(conn[g][a] != 0)  //this does not work, need an iterator to loop over g
				g2.push_back(conn[g][a]);
		}
		if(g2.size() <= 1) //double check the <= 1 parameter
		//if(length(find(conn(g,1:40) != 0)) <= 1)
		{
			s = gene[h][41]/1000;
			if(s > 0)
			{
				p_count++;
				pend[h][0] = h;
				pend[h][1] = s;
				pend[h][2] = 2.007*(s^(1/2));
			}
		}
	}
	if(p_count == 0)
		return score;

	double min = pend[0][2];
	for(int h=0;h<7;++h)
	{
		if(min < 0)
			min *= -1;
		if(min > pend[h][2])
			min = pend[h][2];
	}

//Test for the pendulum(s) ability to tell various intervals of time.
	double secpend,minpend,hrpend,daypend,weekpend,yearpend;
	secpend = (1-min)/1;
	minpend = (60-min)/60;
	hrpend = (3600-min)/3600;
	daypend = (86400-min)/86400;
	weekpend = (604800-min)/604800;
	yearpend = (31536000-min)/31536000;

	if(min > 31536000)
		score += 0;
	else if(min > 604800)
		score += 1/yearpend;
	else if(min > 86400)
		score += 1/weekpend + 1/yearpend;
	else if(min > 3600)
		score += 1/daypend + 1/weekpend + 1/yearpend;
	else if(min > 60)
		score += 1/hrpend + 1/daypend + 1/weekpend + 1/yearpend;
	else if(min > 1)
		score += 1/minpend + 1/hrpend + 1/daypend + 1/weekpend + 1/yearpend;
	else //min has sub-second accuracy
		score += 1/secpend + 1/minpend + 1/hrpend + 1/daypend + 1/weekpend + 1/yearpend;

/* Let's search foward from the pendulum. The only way a pendulum can
% transfer motion to gears is through a ratchet. We are not constraining
% who connects where but if things don't line up in a functional way the
% clock won't work and there is no need continuing the simulation. We
% onlt simulate as far as we need to go. This saves computer time and
% makes the code more compact.*/
	return score;
}

void Clock::doPhysics()
{
	/*Now that the gene has been made, time to make it conform to physics
	  Starting from the bottom, we make sure that:
	  Springs can only be attached to 4 items
	  Ratchets can only be attached to 3 items
	  Hands can only be attached to 4 items
	  Gears can only be attached to as may items as they have teeth
	  
	  We get a list of connections for each object, then chose randomly from that list.
	  After making sure that the bottom object is in conformance with the laws of physics,
	  we use bidirectional connectivity to make sure that since A touches B, B touches A*/
	int cless = columns-2;  //last column is used for #teeth/ger
	int rless = rows-1;
	std::vector<int> v;

	/*Spring*/
	int i=38;
	v.reserve(5);
	for(int j=cless;j<=0;j--) //double check to make sure this is cless or columns
	{
		if((1 == gene[i][j])&&(2 == gene[i][j]))
		{
			v.push_back(j);
		}
		int qq = v.size();
		while(qq > 4)
		{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent gene[i][0] from mucking things up
			v.at(rand()%v.size()) = -1;
			qq--;
		}
		//the last thing we do is clear the vector
		for(std::vector<int>::iterator it=v.end();it!=v.begin();it--)
		{
			if(*it == -1)
			{
				/*For some reason, VS2010 throws an error at gene[i][*it]*/
				int q = *it;
				gene[i][q] = 0;
				gene[q][i] = 0;
			}
			v.pop_back();
		}
	}

	/*Ratchets*/
	i=37;
	v.reserve(5);
	for(int j=cless;j<=0;j--)
	{
		if((1 == gene[i][j])&&(2 == gene[i][j]))
		{
			v.push_back(j);
		}
		int qq = v.size();
		while(qq > 3)
		{
			//get 3 random elements and pull them from v, then drop the rest
			//-1 is to prevent gene[i][0] from mucking things up
			//one element via the teeth, two via center
			v.at(rand()%v.size()) = -1;
			qq--;
		}

		//the last thing we do is clear the vector
		for(std::vector<int>::iterator it=v.end();it!=v.begin();it--)
		{
			if(*it == -1)
			{
				/*For some reason, VS2010 throws an error at gene[i][*it]*/
				int q = *it;
				gene[i][q] = 0;
				gene[q][i] = 0;
			}
			v.pop_back();
		}
	}

	/*7 Hands*/
	v.reserve(5);
	for(i=36;i>29;i--)
	{
		for(int j=cless;j<=0;j--)
		{
			if((1 == gene[i][j])&&(2 == gene[i][j]))
			{
				v.push_back(j);
			}
			int qq = v.size();
			while(qq > 4)
			{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent gene[i][0] from mucking things up
				v.at(rand()%v.size()) = -1;
				qq--;
			}

		//the last thing we do is clear the vector
			for(std::vector<int>::iterator it=v.end();it!=v.begin();it--)
			{
				if(*it == -1)
				{
				/*For some reason, VS2010 throws an error at gene[i][*it]*/
					int q = *it;
					gene[i][q] = 0;
					gene[q][i] = 0;
				}
				v.pop_back();
			}
		}
	}

	/*Gears*/
	v.reserve(5);
	for(i=29;i>=0;i--)
	{
		for(int j=cless;j<=0;j--)
		{
			if((1.0 == gene[i][j])&&(2.0 == gene[i][j]))
			{
				v.push_back(j);
			}
			int qq = v.size();
			while(qq > 4)
			{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent gene[i][0] from mucking things up
				v.at(rand()%v.size()) = -1;
				qq--;
			}

		//the last thing we do is clear the vector
			for(std::vector<int>::iterator it=v.end();it!=v.begin();it--)
			{
				if(*it != -1)
				{
				/*For some reason, VS2010 throws an error at gene[i][*it]*/
					int q = *it;
					gene[i][q] = 0;
					gene[q][i] = 0;
				}
				v.pop_back();
			}
		}
	}
	/*Bidirectionality
	  Start from bottom due to having already fixed the lower part of the matrix
	  We note that an object cannot touch itself, so the identity matrix is blanked*/
	for(int i =(rows-1);i>0;i--)
		for (int j = (columns-1); j > 0; j--)
		{
			gene[j][i] = gene[i][j];
			if (i == j)
				gene[i][j] = 0;
		}
}

/*Private function, only called by Score()*/
int Clock::circuit()
{
	/*for A*, we need a list of all the elements of c[][] that are nonzero.
	We pass that list to A*, and iterate over it, looking for a path between
	two nodes.
	We then return that matrix, and let Score do it's thing to the returned matrix.

	Either that, or rearrange circuit, and pass to it the wanted nodes, and see if
	a path exists between them.  If that is the case, circuit() may not be needed,
	A* can just be directly invoked from Score.*/

	for (int x = 0; x < rows;x++)
	{ }
	return 0;//somthing;
}
