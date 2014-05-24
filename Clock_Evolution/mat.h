/*Matrix class.
  Allows use of things that matlab does, like ones, index, et al.
  */
#ifndef MAT_H
#define MAT_H

class matrix
{
	int rows, columns;
public:
	double zeros(int,int);
	double ones(int, int);
	double rand(int, int);
	int size_x(int);
	int size_y(int);
	double indices(int, int, double); //gives list of all indices that match a given number
	double indices(double, double);
	double slice(); //finish
} mat;

#endif
