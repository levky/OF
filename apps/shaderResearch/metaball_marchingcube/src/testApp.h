#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxMarchingCubes.h"
#include "ofx3DUtils.h"
#include "MetaBall.h"
#include "ofxSTL.h"

#define NUM_META_BALLS 10



class testApp : public ofBaseApp{
	
public:
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
	
	ofxMarchingCubes marchingCubes;
	ofxLight light, reflections;
	vector<MetaBall> metaBalls;
	bool bSaveModel;
};

#endif
