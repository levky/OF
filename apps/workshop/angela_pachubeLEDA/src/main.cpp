/*
 *  main.cpp
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */
#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(700,600, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	ofRunApp(new testApp());

}
