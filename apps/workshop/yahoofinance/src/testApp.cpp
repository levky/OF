/*
 *  testApp.cpp
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	finance.setID("0005.hk");
	finance.updatefinance();
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(100, 100, 200);
	finance.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
	switch (key) {
		case '1':
			finance.setID("0001.hk");
			finance.updatefinance();
			break;
		case '2': 
			finance.setID("0005.hk");
			finance.updatefinance();
			break;
		default:
			break;
	}
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
