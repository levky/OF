/*
 *  testApp.cpp
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *  Summary: This program will show the past 6hours temperature in the LEDA office at NewYork. 
 * 
 */
#include "testApp.h"
//--------------------------------------------------------------
// runs at the start of the program, to read the feed you need a pachube api key. 
// More info at www.pachube.com
// You need to have the csv url and the feedid to make this program works
//--------------------------------------------------------------
testApp::testApp()
{
    out = new ofxPachubeOutput(true);       /// threaded
 	out->setApiKey("6f438ce7b9318cad96259a5b6cff964150ce248706bfcddf9850f742922fed8f");
	//interval=0, every point, max-6hours
	//interval=60, one minutes, max-24 hours
	//interval=900, 15mins, max-14 days
	//interval=3600, 1hours, max-31days
	out->setCsvUrl("http://api.pachube.com/v2/feeds/19794/datastreams/0.csv?interval=60&duration=6hours");
	out->setFeedId(19794);
	out->setVerbose(false);
	out->setMinInterval(5);
	/// forcing update = ignoring min interval
	out->output(OFX_PACHUBE_CSV, true);
   }
//--------------------------------------------------------------
// destructor
//--------------------------------------------------------------
testApp::~testApp()
{

    delete out;
}

//--------------------------------------------------------------
// setup() runs at the start of the program.
//--------------------------------------------------------------
void testApp::setup(){
	ysteps =13;
	left =20;
	interval =900;
	higherbound=40;
	lowerbound=-10;
	
}

//--------------------------------------------------------------
// update() gets called repeatedly. It runs just before draw() so this place is for any update of variables
//--------------------------------------------------------------
void testApp::update(){

	xsteps= ofGetWidth()/100;
	bottom =ofGetHeight()*.75;
	out->output(OFX_PACHUBE_CSV, true);

}

//--------------------------------------------------------------
// draw() was used to draw all the things on the screen.
// It will show the temperature values in a certain interval
//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255,255,255);
    ofFill();

    char pcText[256];
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Temperature vs. Time", ofGetWidth()*.4, 20);
	//draw all points out
	for (int i = 1; i < out->getDatastreamCount(); i++)
	{
		ofSetColor(255, 255, 255);
		ofCircle(left+i*xsteps, bottom - (out->getValue(i))*ysteps, 2);
		
	}
	//print Y axis value from 0 to 40
	for(int i=lowerbound; i<higherbound; i++){
		ofSetColor(255,255,255);
		ofDrawBitmapString(ofToString(i),5,bottom- i*ysteps-ysteps/2);
	}
	//draw line between points
	for(int i=1; i<out->getDatastreamCount()-1;i++){
		ofLine(left+i*xsteps, bottom -(out->getValue(i))*ysteps,left+(i+1)*xsteps, bottom -(out->getValue(i+1))*ysteps);
	}
	//draw bottom line
	ofLine(0,bottom-ysteps/2,out->getDatastreamCount()*xsteps,bottom-ysteps/2);
	
	//draw bottom -
	for(int i=1; i<out->getDatastreamCount();i=i+5){
		ofLine(left+i*xsteps,bottom+ysteps/2,left+i*xsteps,bottom-ysteps);
	}
	//draw left line
	ofLine(left+xsteps,bottom-out->getDatastreamCount()*ysteps,left+xsteps,ofGetHeight());
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
