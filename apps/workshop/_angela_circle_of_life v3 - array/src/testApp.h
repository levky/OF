/*
 *  testApp.h
 *  openFrameworks
 *  Circle of Life v2 - without pointer
 *
 *  Created by Angela Chim 
 *  Created: February 2011
 */

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxCell.h"
#include <vector>
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#define PORT 8000
#define SPORT 9000
#define HOST "172.20.10.91"

#define OSCInterface		1
#define useOSC				1
#define maxSteps			146
#define maxCircles			300
#define numOfRings			21
class testApp : public ofBaseApp{

	public:
	void parseOSCMsg();
	void resetneighbor();
	void addNewCell();
	void updatePosition();
	void updateTemp();
	void deleteCell();
	void changedirection(int i,int j);
	void changecondition(int i,int j);
	bool checkneighbor(int r,int ny,int cury);
	void addcounter(int i,int j);
	void updateLife();
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void addCrashes(int m, int x,int y);
	void updateNumOfCircle();

	ofxCell myCircle[numOfRings+1][maxSteps];
	ofxCell tempCircle[numOfRings+1][maxSteps];
	int checkstep[numOfRings+1];
	int maxRingNum;
	int frame;
	int grid;
	int numOfHit;
	int deadspeed;
	bool showMsg;
	bool showFrame;
	int numOfCell;
	int NumOfALiveCircle;
	
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	int updatecount;
};
#endif

