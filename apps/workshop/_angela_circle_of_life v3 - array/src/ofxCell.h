/*
 *  ofxCell.h
 *  openFrameworks
 *  Circle of Life v2 - without pointer
 *
 *  Created by Angela Chim 
 *  Created: February 2011
 */

#ifndef ofxCell_H
#define ofxCell_H
#define circle_radius 15
#define ringSize 30


class ofxCell{

public:
	ofxCell();
	void setCell(int r,int s);
	void setMaxRing(int maxRingNum);
	void setColor(ofColor a);
	void setColor(int r, int g, int b);
	int CalcTotSteps (int r);
	float CalcAngleStep(int r);
	float CalcAngle(int r, int s);
	void changedirection(int d);
	void draw();
	void decreasering();
	void increasering();
	void randomdirection();
	int getNextRing();
	int getNextStep();
	
	bool alive;
	int steps;//0-max
	int ring;
	ofColor color;	
	int maxRing;
	int direction;
	int condition;
	int neighbor;
	int numOfHit;
	int mode;
	
	int totalSteps;//max steps 
	float angleSteps;//the angle between the cells in each ring
	int ringRadius;
	float angle;
	
};
#endif