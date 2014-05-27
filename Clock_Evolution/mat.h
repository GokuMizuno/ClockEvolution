/*Matrix class.
  Allows use of things that matlab does, like ones, index, et al.
  */
#ifndef MAT_H
#define MAT_H

class matrix
{
private:
	int x, y;
	double **mat;
public:
	matrix();
	~matrix();
	void allocmat(int, int);
	void delmatrix();
	matrix zeros(int,int);
	matrix ones(int, int);
	double rand(int, int);
	matrix set_size(int, int);
	matrix indices(int, int, matrix&); //gives list of all indices that match a given number
	double indices(double, double&);
	double slice(); //finish

	matrix& operator= (const matrix &other);
} mat;

#endif
