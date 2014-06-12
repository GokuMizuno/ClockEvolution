#include "stdfax.h"

Clock::Clock() //default constructor
{
	/*The cells of the matrix are loaded with mrand(), and manipulated to read 1.0, 2.0, or 0.0 as needed.
	Using a standard mrand() Gaussian distro, all objects with > 3 sigma are given a value of 2.0,
	cells < 3 sigma, but > 2 sigma from norm are given 1.0, and all others are 0.0.  Thus, 95% of
	all cells, that is, gears, ratchets, et al, will do nothing, nor connect to anything.

	In the original paper, rand() is a value between [0,1], and 0.06 or less became 1, whilst
	0.06 to 0.10 became 2, and everything else mapped to 0.  Each gear gets between 4 and 100 teeth.

	Structure of the clock matrix
				row			column
	30 gears:	0:29		0:39	for connectivity
							40		number of teeth
	7 hands		30:36		0:39	connectivity
	1 ratchet	37			0:39	connectivity
	1 spring	38			0:39	connectivity
	1 base		39			0:39	connectivity
	*/

	/*Check gears to make sure number of teeth are greater than items connected to them.
	For k<row, genome[j][k] = genome[k][j]*/

	//This is merely the create function below
	generation = 1;
	flag = 0;
	int cless = columns-1;
	int rless = rows-1;
	for(int j=0;j<rows;j++) //rows
	{
		for(int k=0;k<columns;k++) //columns
		{
			if(k == cless)
			{
				genome[j][k] = (rand()%100); //# of teeth per gear <=100
				if(genome[j][k] < 4)
					genome[j][k] = 4;
				for(int l=0;l<columns;l++)
				{
					double sum=0;
					sum += genome[j][l];
					if(genome[j][cless] < sum)
						genome[j][cless] = sum;
				}
			}
			else
			{
				genome[j][k] = mrand();
				if(genome[j][k] > 0.997)
					genome[j][k] = 2.0;
				else if(genome[j][k] > 0.954)
					genome[j][k] = 1.0;
				else
					genome[j][k] = 0.0;
			}
		}
	}
}

Clock::~Clock()
{

}

void Clock::show(void)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			std::cout << genome[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

int Clock::Generation()  {  return generation;  }
bool Clock::isLocked()  {  return flag;  }
void Clock::Lock()  {  flag = 1;  }
void Clock::Unlock()  {  flag = 0;  }

double Clock::Score()
{
	double score, physics;
	int gears, pendula, arms;  //number of each

	score = 0;
	/*An arm is worth more than a pendula
	  A pendula is worth more than nothing
	  A perfectly accurate pendula is worth 1.0
	  All gears bound make score == 0
	  Each arm/pendula is worth some multiplier* how accurate it is*/
	/*First begin with a circuit algol.
	  Then do time accuracy*/

	/*This is the Matlab code.  Each line will be translated into C, and as it is done,
	  the matlab code will be commented out.*/
	
	//no idea what temp99 is, or what it does.  Keep commented out
	/*
	temp99 = ck;
	temp99(1:40,1:40) = conn;
	output{1} = temp99;*/
	
	//gconn2 = zeros(30);
	//gconn2(conn(1:30,1:30)==2) = 2;
	//keep = 30x1 matrix of zeroes
	//keep = zeros(30,1);
	double gconn2[30][30], keep[30];
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(2 == genome[i][j])
				gconn2[i][j] = 2;
			else
				gconn2[i][j] = 0;
		}
		keep[i] = 0;
	}
/*Commenting out to enable testing of mutate(Clock*)*/	
	//find = provides an array of indices for nonzero elements in conn
	//baseg = find(conn(40,1:30) ~= 0);
	//keep(baseg) = 1;		no idea what this line does
	for(int i=0;i<rows;i++)
		for(int j=0;j<30;j++)
			if((2 == genome[i][j])||(1 == genome[i][j]))
				baseg[i][j] = i;
	//double check to make sure i is the proper index to be saving
	
	//The circuit_distance.m function finds the shortest path between every
	// pair of gears.
	d2 = circuit(gconn2,baseg);
	//d2 = d2{1};		no idea what this line does
	
	//in an nxm array, length is n>m?n:m  equal to max(size(array))
	for g=1:length(baseg)
		keepg = ~isnan(d2(baseg(g),:)); //what. the. hell?
	keep(keepg==1) = 1;
	end

	for(int g=0;g<=40;++g) //c++
	{}

/*Matlab code below
conn(40,keep==1) = 1;

gconn = conn(1:30,1:30);

for r=1:30
    if keep(r) == 0
        gconn(r,:) = 0;
        gconn(:,r) = 0;
    end
end*/
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
p_count = 0;
pend = [];
for h = 31:37
    if conn(40,h) ~= 0
        g = find(conn(h,1:30) ~= 0);
        if length(g) ~= 1
            continue;
        end

        if length(find(conn(g,1:40) ~= 0)) <= 1
            l = (ck(h,41)/1e4);
            if l > 0
                p_count = p_count + 1;
                pend(p_count,1:3) = [h l (2.007 * (l^0.5))];
            end
        end
    end
end*/
	//c++ below
	int p_count = 0;  //number of pendula
	double s = 0;
	std::vector<double> pend[3]; //need to create a pend[3] for each pendula
	std::vector<double> g;
	std::vector<double> g2;
	std::vector<double> *ptr_pend;
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
			if(conn[g][a] != 0)  //does this work, since g is a vector?
				g2.push_back(conn[g][a]);
		}
		if(g2.size() <= 1) //double check the <= 1 parameter
		//if(length(find(conn(g,1:40) != 0)) <= 1)
		{
			s += genome[h][41]/1000;
			if(s > 0)
			{
				p_count++;
				ptr_pend.push_back() = new std::vector<double> pend[3];
				pend[3] = {h,s,(2.007*(s^(0.5)))};
			}
		}
	}
	if(p_count == 0)
		return score;
/*Matlab
if isempty(pend)
    output{2} = 0;
    output{3} = 0;
    return
end

output{3} = 1;
output{4} = pend;

% Test for the pendulum(s) ability to tell various intervals of time.
secpend = min(abs(1 - pend(:,3)))/1;
minpend = min(abs(60 - pend(:,3)))/60;
hrpend = min(abs(3600 - pend(:,3)))/3600;
daypend = min(abs(86400 - pend(:,3)))/86400;
weekpend = min(abs(604800 - pend(:,3)))/604800;
yearpend = min(abs(31536000 - pend(:,3)))/31536000;

score(1) = 1/secpend;
score(2) = 1/minpend;
score(3) = 1/hrpend;
score(4) = 1/daypend;
score(5) = 1/weekpend;
score(6) = 1/yearpend;

if min(pend(:,3)) > 31536000
    score(1:6) = 0;
elseif min(pend(:,3)) > 604800
    score(1:5) = 0;
elseif min(pend(:,3)) > 86400
    score(1:4) = 0;
elseif min(pend(:,3)) > 3600
    score(1:3) = 0;
elseif min(pend(:,3)) > 60
    score(1:2) = 0;
elseif min(pend(:,3)) > 1
    score(1) = 0;
end*/
	for(auto &ptr_pend)
	{
		//stuff
	}

% Prevent scores of infinity.
score(score > 1e6) = 1e6;
output{2} = sum(score);
  
/* Let's search foward from the pendulum. The only way a pendulum can
% transfer motion to gears is through a ratchet. We are not constraining
% who connects where but if things don't line up in a functional way the
% clock won't work and there is no need continuing the simulation. We
% onlt simulate as far as we need to go. This saves computer time and
% makes the code more compact.*//*
g = [];
gr = [];
gs = [];
for p = 1:size(pend,1)
    if conn(38,pend(p,1)) == 1
        %The ratchet connects to the pendulum.
        %This is the gear the pendulum ratchet connects to
        gr = find(conn(38,1:30) == 2);
        if length(gr) > 1
            gr = gr(1);
        end
        
        if conn(40,gr) == 0
            %The gear does not connect to the base.
            gr = [];
        end
        
        if ~isempty(gr)
            %This is the gear the spring connects to
            gs = find(conn(39,1:30) ~= 0);
            if length(gs) > 1
                gs = gs(1);
            end
            
            if conn(40,gs) == 0
                gs = [];
            end
            pendulum = p;
        end
    end
end
        
if ~isempty(gr) && ~isempty(gs)
    d2 = circuit_distance(gconn,[gr gs]);
    d2 = d2{1};
    
    if ~isnan(d2(gr,gs)) || gs == gr
        %The spring gear connects to the ratchet gear
    else
        output{3} = 2;
        return
    end
else
    return
end
output{3} = 3;
/* If you made it here you potentially have a powered clock
% must check if the gears turn or if they bind up.
% Start with the ratcheted gear and work foward to all gears it
% is connected to. Initial turn rate is 0, the values are updated
% as you work through the connections. If a value to be assigned to
% a gear conflicts with a value already there (except 0) that means
% the system will not turn.*//*
    
rotation = zeros(30,1);
period = pend(pendulum,3) * gearsize(gr);
period = (round(period * 1e3)) / 1e3;
rotation(gr) = period;
pathlength = 1;
s = gr;
        
while pathlength > 0
    nn = s(pathlength);
    post = find(gconn(nn,:) ~= 0);
    
    badgears = 0;
    foundtip = 0;
    for test = 1:length(post)
        if gconn(nn,post(test)) == 2
            temprot = rotation(nn);
        else
            temprot = -rotation(nn) * (gearsize(post(test))/gearsize(nn));
        end
        
        temprot = (round(temprot * 1e3)) / 1e3;
        
        if rotation(post(test)) == 0
            rotation(post(test)) = temprot;
            s = [s post(test)];
            pathlength = pathlength + 1;
            foundtip = 1;
            break;
        elseif abs(rotation(post(test)) - temprot) > 0.002
            badgears = 1;
            break
            
        end
    end
    
    if badgears == 1
        %disp('gears');
        break;
        
    end
        
    if isempty(test) && foundtip == 0
        s = s(1:length(s)-1);
        pathlength = pathlength - 1;
    elseif test == length(post) && foundtip == 0
        s = s(1:length(s)-1);
        pathlength = pathlength - 1;
    end
end

% There are other ways gears can bind. First check if a hand
% connects to two different gears. At least one must be spinning.

for r=31:37
    o = find(conn(r,1:40) ~= 0);
    if length(o) > 1
        g = find(conn(r,1:30) ~= 0);
        for temp = 1:length(g)
            if rotation(g(temp)) ~= 0
                badgears = 1;
                %disp('hands');
            end
        end
    end
end

% The spring was previously determined to connect to one gear and
% the housing, therefore the spring cannot bind up the gears.
% The ratchet was also previously tested.

if badgears == 1
    return
end

output{3} = 4;
% If you make it here then the gears do not bind. Find the hands
% are attached to the gears that move and calculate their period
% moving hands beat out pendulums. Multiply their scores by 1000.

spinrate = rotation(rotation ~= 0);

% Here we test the gears ability to measure various intervals of time.
% Gears usually beat pendulums since they can spin at much slower rates.
secgear = min(abs(1-abs(spinrate)))/1;
mingear = min(abs(60-abs(spinrate)))/60;
hrgear = min(abs(3600-abs(spinrate)))/3600;
daygear = min(abs(86400-abs(spinrate)))/86400;
weekgear = min(abs(604800-abs(spinrate)))/604800;
yeargear = min(abs(31536000-abs(spinrate)))/31536000;

if score(1) < abs(1/secgear)
    score(1) = abs(1/secgear);
end
if score(2) < abs(1/mingear)
    score(2) = abs(1/mingear);
end
if score(3) < abs(1/hrgear)
    score(3) = abs(1/hrgear);
end
if score(4) < abs(1/daygear)
    score(4) = abs(1/daygear);
end
if score(5) < abs(1/weekgear)
    score(5) = abs(1/weekgear);
end
if score(6) < abs(1/yeargear)
    score(6) = abs(1/yeargear);
end

% Gears cannot keep time below the period of the pendulum. This feature
% might have been added after I made the video.
if pend(pendulum,3) > 31536000
    score(1:6) = 0;
elseif pend(pendulum,3) > 604800
    score(1:5) = 0;
elseif pend(pendulum,3) > 86400
    score(1:4) = 0;
elseif pend(pendulum,3) > 3600
    score(1:3) = 0;
elseif pend(pendulum,3) > 60
    score(1:2) = 0;
elseif pend(pendulum,3) > 1
    score(1) = 0;
end
    
score(score > 1e6) = 1e6;
output{2} = sum(score);

spinners = find(rotation ~= 0);
hands = [];
handcount = 0;

% Look for hands connected to the gears.
for h=31:37
    temphand = find(conn(h,spinners) ~= 0);
    if ~isempty(temphand)
        if conn(40,h) == 0
            handcount = handcount + 1;
            hands(handcount,1:3) = [h spinners(temphand) rotation(spinners(temphand))];
    
        end
    end
end

if isempty(hands)
    return
end
output{3} = 5;
output{5} = hands;

% Test the hands ability to measure various periods of time.
hs = abs(1 - abs(hands(:,3)))/1;
hm = abs(60 - abs(hands(:,3)))/60;
hh = abs(3600 - abs(hands(:,3)))/3600;
hd = abs(86400 - abs(hands(:,3)))/86400;
hw = abs(604800 - abs(hands(:,3)))/604800;
hy = abs(31536000 - abs(hands(:,3)))/31536000;

sechand = min(hs);
minhand = min(hm);
hrhand = min(hh);
dayhand = min(hd);
weekhand = min(hw);
yearhand = min(hy);

temp = find(hs == sechand);
handuse(1) = temp(1);

temp = find(hm == minhand);
handuse(2) = temp(1);

temp = find(hh == hrhand);
handuse(3) = temp(1);

temp = find(hd == dayhand);
handuse(4) = temp(1);

temp = find(hw == weekhand);
handuse(5) = temp(1);

temp = find(hy == yearhand);
handuse(6) = temp(1);

uniquehand = length(unique(handuse));

score(1) = abs(1/sechand);
score(2) = abs(1/minhand);
score(3) = abs(1/hrhand);
score(4) = abs(1/dayhand);
score(5) = abs(1/weekhand);
score(6) = abs(1/yearhand);

if pend(pendulum,3) > 31536000
    score(1:6) = 0;
elseif pend(pendulum,3) > 604800
    score(1:5) = 0;
elseif pend(pendulum,3) > 86400
    score(1:4) = 0;
elseif pend(pendulum,3) > 3600
    score(1:3) = 0;
elseif pend(pendulum,3) > 60
    score(1:2) = 0;
elseif pend(pendulum,3) > 1
    score(1) = 0;
end

/* As mentioned in the video, hands on gears are much better than gears
% alone since they allow you to keep track of the exact position of the
% gear. This way you can look away from the clock and not loose the
% time. Hands therefore make the clock much better at telling time.
% QUestion is how much better. Here I multiply the score by 1 million
% since I think hands improve them that much (clocks that you have to
% stare at all the time are pretty crappy), but this value is subjective.
% Play with it and see what happens.*//*
score(score > 1e6) = 1e6;
output{2} = sum(score) * 1e6;

output{3} = 4 + uniquehand;
*/
	/*This is the end of the Matlab code.*/
	return score;
}

double Clock::mrand()
{
	double u,v,r;
	do
	{
		u = ((double)rand()/(RAND_MAX))*2-1;
		v = ((double)rand()/(RAND_MAX))*2-1;
		r = u*u + v*v;
	}while(r>1);
	return r;
}

void Clock::doPhysics()
{
	/*Now that the genome has been made, time to make it conform to physics
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
	std::vector<double> v;

	/*Spring*/
	int i=38;
	v.reserve(5);
	for(int j=cless;j<=0;j--) //double check to make sure this is cless or columns
	{
		double sum;
		sum = genome[i][cless];
		if((1.0 == genome[i][j])&&(2.0 == genome[i][j]))
		{
			v.push_back(j);
		}
		int qq = v.size();
		while(qq > 4)
		{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent genome[i][0] from mucking things up
			v.at(rand()%v.size()) = -1;
			qq--;
		}

		//the last thing we do is clear the vector
		for(std::vector<double>::iterator it=v.end();it!=v.begin();it--)
		{
			if(*it != -1)
			{
				/*For some reason, VS2010 throws an error at genome[i][*it]*/
				int q = *it;
				genome[i][q] = 0;
				genome[q][i] = 0;
			}
			v.pop_back();
		}
	}
	/*Ratchets*/
	i=37;
	v.reserve(5);
	for(int j=cless;j<=0;j--)
	{
		double sum;
		sum = genome[i][cless];
		if((1.0 == genome[i][j])&&(2.0 == genome[i][j]))
		{
			v.push_back(j);
		}
		int qq = v.size();
		while(qq > 3)
		{
			//get 3 random elements and pull them from v, then drop the rest
			//-1 is to prevent genome[i][0] from mucking things up
			//one element via the teeth, two via center
			v.at(rand()%v.size()) = -1;
			qq--;
		}

		//the last thing we do is clear the vector
		for(std::vector<double>::iterator it=v.end();it!=v.begin();it--)
		{
			if(*it != -1)
			{
				/*For some reason, VS2010 throws an error at genome[i][*it]*/
				int q = *it;
				genome[i][q] = 0;
				genome[q][i] = 0;
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
			double sum;
			sum = genome[i][cless];
			if((1.0 == genome[i][j])&&(2.0 == genome[i][j]))
			{
				v.push_back(j);
			}
			int qq = v.size();
			while(qq > 4)
			{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent genome[i][0] from mucking things up
				v.at(rand()%v.size()) = -1;
				qq--;
			}

		//the last thing we do is clear the vector
			for(std::vector<double>::iterator it=v.end();it!=v.begin();it--)
			{
				if(*it != -1)
				{
				/*For some reason, VS2010 throws an error at genome[i][*it]*/
					int q = *it;
					genome[i][q] = 0;
					genome[q][i] = 0;
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
			double sum;
			sum = genome[i][cless];
			if((1.0 == genome[i][j])&&(2.0 == genome[i][j]))
			{
				v.push_back(j);
			}
			int qq = v.size();
			while(qq > 4)
			{
			//get 4 random elements and pull them from v, then drop the rest
			//-1 is to prevent genome[i][0] from mucking things up
				v.at(rand()%v.size()) = -1;
				qq--;
			}

		//the last thing we do is clear the vector
			for(std::vector<double>::iterator it=v.end();it!=v.begin();it--)
			{
				if(*it != -1)
				{
				/*For some reason, VS2010 throws an error at genome[i][*it]*/
					int q = *it;
					genome[i][q] = 0;
					genome[q][i] = 0;
				}
				v.pop_back();
			}
		}
	}
	/*Bidirectionality
	  Start from bottom due to having already fixed the lower part of the matrix*/
	for(int i =rless;i>0;i--)
		for(int j = cless;j>0;j--)
			genome[j][i] = genome[i][j];
}

/*Is this going to be public or private?*//*
double Clock::circuit(double c[30][30], double primarynodes[30]) //doublecheck primarynodes
{
	//since c,primarynodes are arrays, they are passed by address
	/*Matlab code.  It will be translated line by line into C code.*/

	//d = ones(size(c));
	//dtemp = ones(length(c),1) * 1e6;
	//pathmat{size(c,1),size(c,2)} = [];
	//%xxx = waitbar(0,'Searching for Paths');
/*	double d[30][30], pathmat[30][30];
	double dtemp[30];
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
			d[i][j] = 1;
		dtemp[i] = 1000000;
	}


/*%postmat{1:length(c)} = [];
for i = 1:length(c)
    postmat{i} = find(c(i,:) ~= 0);
end*/
	/*As far as I can tell, c(i,:) is the i'th row of c.
	  ~= 0 is not equal to zero
	  find gives the indices of its arguements.
	  So, we are finding the indices of c not equal to zero.*//*
	double postmat[30];
	for(int i=0;i<30;i++)  //does this work?
	{
		//scan over the rows and columns of c
		for(int j=0;j<30;j++)
			for(int k=0;k<30;k++)
				if(c[j][k] != 0)
				{
					postmat[i] = j;
					break;
				}
				else
					postmat[i] = -1;  //double check this
	}
	//replace above with below
/*	{
	int column_push = 0;
	matrix *ptarget;
	ptarget = &target;
	matrix index_list;
	index_list.allocmat(row, column);
	for(int i=0;i<row;++i)
		for(int j=0;j<column;++j)
			index_list[i][j] = 0x7fffffff;

	for(int i=0;i<row;++i)
	{
		for(int j=0;j<column;++j)
		{
			if(*ptarget[i][j] != 0)
			{
				index_list[i][column_push] = j;
				column_push++;
			}
		}
		column_push = 0;
	}

	return index_list;
}*/

/*
//for N = 1:length(c)
	for(int N = 0; N<30;N++)
	{
    
    if isempty(primarynodes(primarynodes == N));
        continue;
    end
    
    s = N;
    pathlength = 1;
    
    while pathlength > 0
        nn = s(pathlength);
        post = postmat{nn};
        
        foundtip = 0;
        for test = 1:length(post)
            if dtemp(post(test)) > pathlength
                dtemp(post(test)) = pathlength;
                pathmat{N,post(test)} = [s post(test)];
                s = [s post(test)];
                pathlength = pathlength + 1;
                foundtip = 1;
                break;
            end
        end
        
        if isempty(test) && foundtip == 0
            s = s(1:length(s)-1);
            pathlength = pathlength - 1;
        elseif test == length(post) && foundtip == 0
            s = s(1:length(s)-1);
            pathlength = pathlength - 1;
        end
    end

    d(N,:) = dtemp;
    dtemp = ones(length(c),1) * 1e6;
	} //end for(N)
end

d(d == 1e6) = NaN;

x{1} = d;
x{2} = pathmat;
*/

	/*end Matlab code*//*
	return 0;//somthing;
}*/
