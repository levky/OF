#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(20, 20, 20);
	ofSetVerticalSync(true);
	
	particleSystem.loadTexture("particleGrid.png", 2, 2);
	particleSystem.init();
	
}

//--------------------------------------------------------------
void testApp::update() {

	camera.setMouse(mouseX, mouseY);
	
	particleSystem.update();
	

}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	
	// Begin Camera
	camera.enableCamera();
	camera.center();
	camera.rotationUpdate();
	camera.zoomUpdate();
	
	// Draw the floor
	ofSetColor(40, 40, 40);
	glBegin(GL_QUADS);
	glVertex3f(-300, 200, -300);
	glVertex3f(300, 200, -300);
	glVertex3f(300, 200, 300);
	glVertex3f(-300, 200, 300);
	glEnd();
	
	// The Fast Particle System
	particleSystem.render();
	
	
	
	// End Camera
	camera.disableCamera();
	camera.setPreMouse(mouseX, mouseY);
	
	
	// draw the texture
	ofEnableAlphaBlending();
	ofSetColor(0xffffff);
	particleSystem.texture.draw(0, 50);
	ofDisableAlphaBlending();
	
	
	ofSetColor(255, 255, 255);
	string info = "FPS: "+ofToString(ofGetFrameRate());
	info += "\nTotal Particles: "+ofToString(MAX_PARTICLES);
	
	ofDrawBitmapString(info, 20, 20);
	
}





//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'f') ofToggleFullscreen();
	if(key == ' ') {
		ofImage img;
		img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string uid = ofToString(ofGetDay())+ofToString(ofGetYear())+ofToString(ofGetSeconds())+ofToString(ofGetHours	());
		img.saveImage("OMS_"+uid+".tiff");
	}
	
	if(key == OF_KEY_UP)	camera.setZoom(0.2);
	if(key == OF_KEY_DOWN)	camera.setZoom(-0.2);
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	camera.setRotation(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

void testApp::windowResized(int w, int h){
	
}
