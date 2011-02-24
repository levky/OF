/*
 *  cells.h
 *  openFrameworks
 *
 *  Created by LEDAProgrammer on 15/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef CELLS_H
#define	CELLS_H

#include <vector>
#include "ofxCell.h"

class Cells{
public:
	Cells();
	void update();
	void updateLife();
	void updatePostion();
	void draw();
	void isExisted();
	vector<ofxCell*> getCells();
	void setMaxRingNum(int fMaxRing);
	void addCell();
	void addCell(int a, int b);
	void resetneighbor();
	void changedirection(int x);
	void changecondition(int i);
	vector <ofxCell*> getCells();
	
private:
	int numOfCell;
	vector <ofxCell*> pCells;
	int maxRingNum;
	
};