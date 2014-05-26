#include "stdfax.h"
matrix::matrix()
{
	x=40;
	y=41;
	allocmat(x,y);
}

matrix::~matrix()
{
	delmatrix();
}

void matrix::allocmat(int x, int y)
{
	mat = new double*[x];
	for(int i=0;i<y;++i)
		mat[i] = new double[y];
}

void matrix::delmatrix()
{
	for(int i=0;i<y;++i)
		delete[] mat[i];
	delete[] mat;
}

double matrix::zeros(int width, int height)
{
	//matrix met = allocmat(width,height);
	//double met[width][height];
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

/*Throws expression must have a constant value error*/
double matrix::set_size(int x, int y)
{
	matrix rectangle[x][y];
	for(int i=0;i<x;++i)
		for(int j=0;j<y;++j)
			rectangle[i][j] = 0x7fffffff;
	return rectangle;
}

/*Below is placeholder text*/
void matrix::size_x(int x)
{
	this.rows = x;
}

void matrix::size_y(int y)
{
	this.columns = y;
}

/*Needs to be tested!*/
/*Should this be indices(int, int double*)?*/
double matrix::indices(int row, int column, double &target)
{
	int column_push = 0, x = row, y = column;
	matrix index_list[x][y];
	for(int i=0;i<row;++i)
		for(int j=0;j<column;++j)
			index_list[i][j] = 0x7fffffff;

	for(int i=0;i<row;++i)
	{
		for(int j=0;j<column;++j)
		{
			if(*target[i][j] != 0)
			{
				index_list[i][column_push] = j;
				column_push++;
			}
		}
		column_push = 0;
	}

	return index_list;
}

//used for matrix index = genome.indices().
/*Yeah, this doesn't work.
double matrix::indices()
{
	matrix index_list[][];
	for(int i=0;i<rows;++i)
		for(int j=0;j<columns;++j)
			if(this[i][j] != 0)
				;;

	return matrix_list;
}*/

/*What about using size(genome) to get dim, and making an index list that only matches a given number*/
double matrix::indices(double number, double &genome)
{
	int column_push = 0;
	matrix index_list[*genome.row()][*genome.column()];
	for(int i=0;i<row;++i)
		for(int j=0;j<column;++j)
			if(genome[i][j] == number)
			{
				index_list[i][column_push] = j;
				column_push++;
			}

	return index_list;
}

matrix& matrix::operator= (const matrix& other)
{
	if(this != &other)
	{
		delmatrix();
		x = other.x;
		y = other.y;
		allocmat(x,y);
		for(int i=0;i<x;++i)
			for(int j=0;j<y;++j)
				mat[i][j] = other.mat[i][j];
	}
	return *this;
}

