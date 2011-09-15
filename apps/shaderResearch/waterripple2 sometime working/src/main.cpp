//#include "ofMain.h"
#include "testApp.h"
//#include "ofAppGlutWindow.h"

//========================================================================
testApp *myApp;
int main( ){

    //ofAppGlutWindow window;
	ofSetupOpenGL(/*&window,*/ 520,520, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	myApp = new testApp;

	ofRunApp( /*new testApp()*/myApp);

}
