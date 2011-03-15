/*
 *  testApp.h
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */


#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxPachube.h"

//--------------------------------------------------------
class testApp : public ofSimpleApp
{
	public:
        testApp();
        ~testApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	int ysteps;
	int xsteps;
	int bottom ;
	int left ;
	int interval;
	int lowerbound;
	int higherbound;
	
	
	private:
		ofxPachubeOutput*               out;
		ofxPachubeInput*                in;
        int                             iCounter;
};

#endif
