#pragma once

#include "ofMain.h"
#include "ofxMSAFluid.h"
#include "boid.h"
#include "boids.h"
#include "ofxVec3f.h"

// comment this line out if you don't wanna use TUIO
// you will need ofxTUIO & ofxOsc
//#define USE_TUIO		

// comment this line out if you don't wanna use the GUI
// you will need ofxSimpleGuiToo, ofxMSAInteractiveObject & ofxXmlSettings
// if you don't use the GUI, you won't be able to see the fluid parameters
//#define USE_GUI		



//#ifdef USE_TUIO
//#include "ofxTuio.h"
//#define tuioCursorSpeedMult				0.5	// the iphone screen is so small, easy to rack up huge velocities! need to scale down 
//#define tuioStationaryForce				0.001f	// force exerted when cursor is stationary
//#endif


//#ifdef USE_GUI 
//#include "ofxSimpleGuiToo.h"
//#endif


class testApp : public ofSimpleApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);

	void windowResized(int w, int h);
	void addToFluid(float x, float y, float dx, float dy, bool addColor = true, bool addForce = true);

	void addToFluid(float x, float y, float dx, float dy, int ar, int ag, int ab,bool addColor=true);
    
	int					fluidCellsX;
	bool				resizeFluid;
	bool				drawFluid;

	
	ofxMSAFluidSolver	fluidSolver;
	ofxMSAFluidDrawer	fluidDrawer;	

	
	int					pmouseX, pmouseY;
    boids *pBoids;
	ofxVec3f target;
	
	int numCircle;
	// cache these for slightly better performance
	struct {
		int				width;
		int				height;
		float			invWidth;
		float			invHeight;
		float			aspectRatio;
		float			aspectRatio2;
		
	} window;
	

	
//#ifdef USE_TUIO
//	myTuioClient tuioClient;
//#endif	
	
//#ifdef USE_GUI 
//	ofxSimpleGuiToo	gui;
//#endif
	
	
};
extern testApp *myApp;




