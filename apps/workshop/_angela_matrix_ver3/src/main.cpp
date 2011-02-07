/* testApp.h
 * Created by Angela Chim
 * Created: December 2010 
 */

#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 800,600, OF_WINDOW);			// <-------- setup the GL context
	
	ofRunApp( new testApp());

}
