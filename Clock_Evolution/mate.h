#ifndef MATE_H
#define MATE_H
/*Mate is the function that takes two CLocks and
merges them together to produce a new Clock.

To do so, it must access their genomes, and hence,
mate is a friend of Clock.

A friend is a class that can see your privates.*/

#include "clock.h"

/*class mate(Clock, Clock)
{
public:
	stuff;
private:
	stuff;
protected:
	stuff;
};*/

/*NOT TESTED, DOES NOT WORK*/
Clock mate(Clock, Clock)
{
	/*Rand alg to determine how clocks are mated
	  Mutates the resultant clock.
	  Sets generation of new clock to parent Clock++
	  Makes sure new clock is valid*/
	//stuff;
	return Clock;
}

#endif