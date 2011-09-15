/*
 * Title: testApp.h
 * Created by Angela Chim
 * Created: December 2010
 */
#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	
    ofAppGlutWindow window;
	//1024, 768
	ofSetupOpenGL(&window,800,650, OF_WINDOW);
	ofRunApp(new testApp());
	
}
