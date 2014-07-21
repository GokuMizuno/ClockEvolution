/*A Star
// Create by Ofer Rubinstein for Sumerian Blood.
// Code license: CC-BY
// Origin of blog post http://pompidev.net/2012/05/29/a-practical-overview-of-awith-code/
*/

struct AScore {
	public:
		AScore()
		{
			g = 0;
			h = 0;
			f = 0;
		}
		double g, h, f;
};

struct ACell {
	ACell()
	{
		x = 0;
		y = 0;
		Enable = false;
	}
	bool operator<(const ACell & d) const
	{
		return s.f>d.s.f;
	}

	AScore s;
	bool Enable;
	unsigned int x, y;
};

struct Vector {
	Vector()
	{
		x = 0;
		y = 0;
	}
	void Normalize()
	{
		double l = sqrt(x*x+y*y);
		if (l>0.000001)
		{
			x/=l;
			y/=l;
		}
		else
		{
			x = 0;
			y = 0;
		}
	}
	double Length()
	{
		return sqrt(x*x+y*y);
	}
	
	double AngleWith (Vector v)
	{
		double a = fabs(atan2(y, x)-atan2(v.y, v.x));
		if (a>Pi)
			a=2*Pi-a;
		return a;
	}

	double SignAngleWith (Vector v)
	{
		return atan2(y, x)-atan2(v.y, v.x);
	}
	double x;
	double y;
};

class AStar {
	public:
		// A heuristic interface that you can implement and provide to the AStar for different search priorities
		class Heuristic {
			public:
				// Called before the A* search begins
				virtual void Start(ACell First, ACell Goal) = 0;
				// Calculates the estimated distance to the goal
				virtual double Calculate (ACell w1, ACell w2, double Factor) = 0;
				// Return true if reaching the "goal" parameter provided to find means we can stop the search
				virtual bool IsGoal() {return true;};
				// Returns true if we should stop the search
				virtual bool IsStop (ACell w, double Factor) = 0;
				// Returns true if we have failed to achieve our goal(works in conjuction with IsStop)
				virtual bool IsCancel() = 0;
				// Called every iteration of the search
				virtual void Step() = 0;
				virtual ~Heuristic(){};
		};

		// ctr
		AStar()
		{
			Ready = false;
			Factor = 1;
			h = NULL;
		}

		// Setting the heuristic to use in the search
		void SetHeuristic (Heuristic & h)
		{
			this->h = &h;
		}

		// Was the AStar instance initialized?
		bool IsReady()
		{
			return Ready;
		}

		// Initialize the AStar with the field or "maze's" dimensions, and also a factor to scale doing the search map for performance.
		void Initialize (unsigned int w, unsigned int h, double Factor)
		{
			Ready = true;
			this->Factor = Factor;
			unsigned int fh = h/Factor;
			unsigned int fw = w/Factor;
			Score.resize(fh);
			From.resize(fh);
			Closed.resize(fh);
			Open.resize(fh);
			for (unsigned int y = 0; y<Score.size(); y++)
			{
				Score[y].resize(fw);
				From[y].resize(fw);
				Closed[y].resize(fw);
				Open[y].resize(fw);
				for (unsigned int x = 0; x<Score[0].size(); x++)
				{
					Closed[y][x] = false;
					Open[y][x] = false;
				}
			}
		}

		// The actual search function. Providing the start and goal of the search, the Weight maps of how passable or non passable is the terrain and the resulting search path
		// Returns true if reached goal, false if otherwise.
		bool Find(ACell start, ACell goal, std::vector<std::vector<double> > & Weight, std::list<ACell> & Path)
		{
			double Root = sqrt(2.0);
			for (unsigned int y = 0; y<Score.size(); y++)
				for (unsigned int x = 0; x<Score[0].size(); x++)
				{
					From[y][x].Enable = false;
					Closed[y][x] = false;
					Open[y][x] = false;
				}
			start.x = min(start.x/Factor, Score[0].size()-1);
			start.y = min(start.y/Factor, Score.size()-1);
			goal.x = min(goal.x/Factor, Score[0].size()-1);
			goal.y = min(goal.y/Factor, Score.size()-1);
			if (h!=NULL)
			{
				h->Start(start, goal);
				start.s.h = h->Calculate (start, goal, Factor);
				start.s.f = start.s.h;
			}
			std::priority_queue<ACell> openset;
			openset.push (start);

			while (!openset.empty())
			{

				std::list<ACell>::iterator q;
				ACell current;
				current = openset.top();
				if (h!=NULL)
					h->Step();
				if (h!=NULL && h->IsStop (current, Factor))
				{
					if (!h->IsCancel())
						Reconstruct (start, current, Path);
					openset = std::priority_queue<ACell>();
					return true;
				}
				if (h->IsGoal() && current.x==goal.x && current.y==goal.y)
				{
					Reconstruct (start, goal, Path);
					openset = std::priority_queue<ACell>();
					return true;
				}
				openset.pop();
				Open[current.y][current.x] = false;
				Closed[current.y][current.x] = true;
				unsigned int x1 = (current.x>1?current.x-1:0);
				unsigned int y1 = (current.y>1?current.y-1:0);
				unsigned int x2 = (current.x<Score[0].size()-1?current.x+1:Score[0].size()-1);
				unsigned int y2 = (current.y<Score.size()-1?current.y+1:Score.size()-1);
				for (unsigned int ny = y1; ny<=y2; ny++)
					for (unsigned int nx = x1; nx<=x2; nx++)
					{
						if (nx==current.x && ny==current.y)
							continue;
						std::list<ACell>::iterator q;
						if (Closed[ny][nx])
							continue;
						double dx = (double)nx-(double)current.x;
						double dy = (double)ny-(double)current.y;
						ACell neighbour;
						neighbour.x = nx;
						neighbour.y = ny;
//						double s = Score[current.y][current.x]+sqrt(dx*dx+dy*dy)+Weight[neighbour.y][neighbour.x];
						double s = Score[current.y][current.x]+(((nx==current.x) || (ny==current.y))?1:Root)+Weight[neighbour.y][neighbour.x];
						neighbour.s.g = s;
						bool IsFound = false;
						if (Open[ny][nx])
							IsFound = true;
						bool b = false;
						if (!IsFound)
						{
							if (h!=NULL)
								neighbour.s.h = h->Calculate (neighbour, goal, Factor);
							neighbour.s.f = neighbour.s.g+neighbour.s.h;
							openset.push(neighbour);
							Open[neighbour.y][neighbour.x] = true;
							b = true;
						}
						else 
							b = (s < Score[neighbour.y][neighbour.x]);
 
						if (b)
						{
							current.Enable = true;
							From[neighbour.y][neighbour.x] = current;
							neighbour.s.f = neighbour.s.g+neighbour.s.h;
							Score[neighbour.y][neighbour.x] = s;
						}
					}
 
			}
			return false;
		}
	private:
		// Once the search is done, this function is used to reconstruct the actual resulting optimal path.
		void Reconstruct (ACell start, ACell goal, std::list<ACell> & Path)
		{
//			Path.clear(); TODO: Need to provide a clear path
			ACell current = goal;
			while (current.x!=start.x || current.y!=start.y)
			{
				current.x*=Factor;
				current.y*=Factor;
				Path.push_front(current);
				current.x/=Factor;
				current.y/=Factor;
				current = From[current.y][current.x];
				if (!current.Enable)
					return;
			}
		}

		Heuristic * h;
		std::vector<std::vector<bool> > Closed, Open;
		std::vector<std::vector<double> > Score;
		std::vector<std::vector<ACell> > From;
		double Factor;
		bool Ready;
};
