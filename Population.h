#include "stdfax.h"

class Population
{
private:
	Clocks[] individuals;
public:
	Population(int, bool);
	Clock getIndividual(int);
	Clock getWorst(Clock, Clock, Clock);
	Clock saveIndividual(int, Clock);
};
