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
int matrix::size_x(int x)
{
	this.rows = x;
}

int matrix::size_y(int y)
{
	this.columns = y;
}

/*Needs to be tested!*/
/*Should this be indices(int, int double*)?*/
double matrix::indices(int row, int column, double genome)
{
	int column_push = 0;
	matrix index_list[row][column];
	for(int i=0;i<row;++i)
		for(int j=0;j<column;++j)
			if(genome[i][j] != 0)
			{
				index_list[i][column_push] = j;
				column_push++;
			}

	return index_list;
}

//used for matrix index = genome.indices().
/*Yeah, this doesn't work.*/
double matrix::indices()
{
	matrix index_list[][];
	for(int i=0;i<rows;++i)
		for(int j=0;j<columns;++j)
			if(this[i][j] != 0)
				;;

	return matrix_list;
}

/*What about using size(genome) to get dim, and making an index list that only matches a given number*/
double matrix::indices(double number, double genome)
{
	int column_push = 0;
	matrix index_list[genome.row()][genome.column()];
	for(int i=0;i<row;++i)
		for(int j=0;j<column;++j)
			if(genome[i][j] == number)
			{
				index_list[i][column_push] = j;
				column_push++;
			}

	return index_list;
}
