#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(255,255,255);	
	
	zoom.setup(640, 480);
	hasCamera = grabber.initGrabber(640, 480);
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2.0));
	grabber.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	zoom.setZoomParams(mouseX, mouseY, 180, 0.0, 1.5);
	zoom.beginRender();
		
		if( hasCamera ){
			ofSetColor(255, 255, 255);
			grabber.draw(0, 0);
			
			ofSetColor(200, 10, 20);
			ofCircle(ofGetWidth() - 100, 200, 50);
		}else{
			ofSetColor(200, 10, 20);
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);		
		}
		
	zoom.endRender();
	zoom.draw(0, 0, 640, 480, true);
		
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//------------- -------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

