/* 
 * cell.h
 * Created by Angela Chim
 * Created: December 2010 
 */
#ifndef CELL_H
#define CELL_H

#define windowrow 30  //the number of cells vertically
#define windowcol 40 //the number of cells horizontally


class Cells{
	
public:
	Cells();
	
	//set cell 
	void setCells(int i,int j);
	//set counter to zero
	void resetcounter();
	//randomly set a direction for the cell
	void randomdirection();
	//set column
	void setcol(int pCol);
	//set row
	void setrow(int pRow);
	//get the next position x
	int getnextx();
	//get the next position y
	int getnexty();
	//set the next position x
	void setnextx(int pX);
	//set the next position y
	void setnexty(int pY);
	//get direction x
	int getXDirection();
	//get direction y
	int getYDirection();
	//set direction x
	void setXDirection(int pdx);
	//set direcion y
	void setYDirection(int pdy);
	//draw all cell that is alive
	void draw(int width,int height);
	
	//public variables
	bool alive;
	int numItems; // stores the numbers of neighbour 
	float red;
	float blue;
	float green;
	int row;
	int col;
	int dx;
	int dy;
	int nextx;
	int nexty;
	int counter; // the number of hit
};
#endif