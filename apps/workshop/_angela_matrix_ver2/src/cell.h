/*
 *  cell.h
 *  openFrameworks
 *
 *  Created by LEDAProgrammer on 14/10/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CELL_H
#define CELL_H


#define windowrow 30  //the number of cells vertically
#define windowcol 40 //the number of cells horizontally
#define useOSC 1 //0- not using OSC, 1- using OSC
#define OSCInterface 1 //0 - for oscemote, 1 - for touch osc

class Cells{
	
public:
	Cells();
	
	//set cell 
	void setCells(int i,int j);
	//set counter to zero
	void resetcounter();
	//randomly pick a color for the cell(red,green or blue)
	void randomMode();
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
	
	//subtract the deadspeed of each cell(cellcolor/mode 1=red, 2=green, 3=blue)
	void addCrashes(int mode);
	
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
	int cellcolor; // Example: 1=red 2=green 3=blue
	int counter; // the number of hit
	int dspeed; //deadspeed
	
};
#endif