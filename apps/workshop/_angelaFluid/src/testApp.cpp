#include "testApp.h"
#include "msaColor.h"
#include "boids.h"


#pragma mark Custom methods

void testApp::addToFluid(float x, float y, float dx, float dy,  int ar, int ag, int ab,bool addColor) {
	
	float colorMult = 50;
	float velocityMult = 30;
	int index = fluidSolver.getIndexForNormalizedPosition(x, y);
	
	if(addColor) {
		fluidSolver.r[index]  +=ar;
		fluidSolver.g[index]  +=ag;
		fluidSolver.b[index]  +=ab;
	}

		fluidSolver.u[index] += dx * velocityMult;
		fluidSolver.v[index] += dy * velocityMult;

}


#pragma mark App callbacks



//--------------------------------------------------------------
void testApp::setup() {	 
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	pBoids =new boids(5);
	pBoids->setMaxVelocity(15);
	pBoids->setTooCloseDist(45.0);
	pBoids->setInSightDist(75.0);
	
	for (int i=0;i<pBoids->getNumBoids();i++){
		msaColor bCol;
		bCol.setHSV(i*60, 1, 1);
		pBoids->getBoids()[i]->setColor(bCol.r*255,bCol.g*255,bCol.b*255);
	}


	// setup fluid stuff
	fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
	
	fluidCellsX			= 150;
	drawFluid			= true;
	resizeFluid			= true;
	 
}


//--------------------------------------------------------------
void testApp::update(){
	
	pBoids->flock();
	pBoids->bounce();
	pBoids->update();
	
	float mx;
	float my;
	float mvx;
	float mvy;
	numCircle=pBoids->getNumBoids();
	
	for(int i=0;i<numCircle;i++){
		mx= (pBoids->getBoids()[i]->getPosition().x) * window.invWidth;
		my= (pBoids->getBoids()[i]->getPosition().y) * window.invHeight;
		mvx = (pBoids->getBoids()[i]->getVelocity().x) * window.invWidth;
		mvy = (pBoids->getBoids()[i]->getVelocity().y) * window.invHeight;
		
		//add circles positions and directions into the Fluid Solver
		addToFluid(mx,my,mvx,mvy,
		pBoids->getBoids()[i]->red,
		pBoids->getBoids()[i]->green,
		pBoids->getBoids()[i]->blue,
		true);
		
	if(resizeFluid) 	{
		fluidSolver.setSize(fluidCellsX, fluidCellsX / window.aspectRatio);
		fluidDrawer.setup(&fluidSolver);
		resizeFluid = false;
	}

	fluidSolver.update();
	
	// save old mouse position (openFrameworks doesn't do this automatically like processing does)
	pmouseX = mouseX;
	pmouseY = mouseY;
	}

}

//--------------------------------------------------------------
void testApp::draw(){
		ofSetBackgroundAuto(drawFluid);
		if(drawFluid) {
			for (int i=0;i<1;i++){
				glColor3f(1, 1, 1);
				fluidDrawer.draw(0, 0, window.width, window.height);
			}
		}

	pBoids->draw();

}


void testApp::windowResized(int w, int h) {
	window.width		= w;
	window.height		= h;
	
	window.invWidth		= 1.0f/window.width;
	window.invHeight	= 1.0f/window.height;
	window.aspectRatio	= window.width * window.invHeight;
	window.aspectRatio2 = window.aspectRatio * window.aspectRatio;
	
	resizeFluid = true;
}


#pragma mark Input callbacks

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

void testApp::mouseDragged(int x, int y, int button) {
	float mouseNormX = x * window.invWidth;
    float mouseNormY = y * window.invHeight;
    float mouseVelX = (x - pmouseX) * window.invWidth;
    float mouseVelY = (y - pmouseY) * window.invHeight;
	
	addToFluid(mouseNormX, mouseNormY, mouseVelX, mouseVelY,255,0,0, false);
}

