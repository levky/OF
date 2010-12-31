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
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp());
	
}
