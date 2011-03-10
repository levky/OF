/*
 *  testApp.h
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
*/
#ifndef _TEST_APP
#define _TEST_APP
#include "yahoofinance.h"
#include "ofMain.h"

class testApp : public ofSimpleApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		yahoofinance finance;
		
};
#endif
