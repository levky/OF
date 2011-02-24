/*
 *  main.cpp
 *  openFrameworks
 *  Circle of Life v2 - without pointer
 *
 *  Created by Angela Chim 
 *  Created: February 2011
 */

#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	ofRunApp( new testApp());

}
