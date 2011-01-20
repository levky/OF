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
#define windowrow 30 
#define windowcol 40

class Cells{
	
public:
	Cells();
	void setCells(int i,int j);
	bool alive;
	int numItems;
	float red;
	float blue;
	float green;
	int row;
	int col;
	int dx;
	int dy;
	int nextx;
	int nexty;
	int cellcolor;
	int counter;
	int dspeed;
	void draw(int width,int height);
	void setcol(int pCol);
	void setrow(int pRow);
	int getnextx();
	int getnexty();
	void setnextx(int pX);
	void setnexty(int pY);
	int getXDirection();
	int getYDirection();
	void setXDirection(int pdx);
	void setYDirection(int pdy);
	void addCrashes(int mode);
	void randomdirection();
	void randomMode();
	void resetcounter();
	
};
#endif