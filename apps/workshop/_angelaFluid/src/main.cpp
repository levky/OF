
#include "testApp.h"
#include "boids.h"

testApp *myApp;
int main( ){
	ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);			// <-------- setup the GL context
	myApp = new testApp;
	ofRunApp(myApp);
}
