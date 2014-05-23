#include "stdfax.h"

double matrix::zeros(int width, int height)
{
	double met[width][height];
	for(int i=0;i<width;++i)
		for(int j=0;j<height;++j)
			met[i][j] = 0.;
	return met;  //this is wrong
}

double matrix::ones(int width, int height)
{
	double met[width][height];
	for(int i=0;i<width;++i)
		for(int j=0;j<height;++j)
			met[i][j] = 1.;
	return met;  //this is wrong
}
/*Below is placeholder text*/
int matrix::size_x()
{
	return this.x;
}

int matrix::size_y()
{
	return this.y;
}
