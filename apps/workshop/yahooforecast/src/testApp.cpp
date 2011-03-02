/*
 *
 *  testApp.cpp
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */

#include "testApp.h"

//--------------------------------------------------------------
// setup() runs at the start of the program. It initialize the variables such as the unit(true= Celsius or false=Fahrenheit),and myurl/setID

//--------------------------------------------------------------

void testApp::setup(){
	weather.setunit(true);
	weather.setID("2502265");
	weather.updateweather();
}

//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
// draw() was used to draw on the screen
//--------------------------------------------------------------

void testApp::draw(){
	
	ofBackground(100, 100, 200);
	weather.draw();
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){	
	
	switch (key) {
		case '1':
			weather.setID("2165352");
			weather.updateweather();
			break;
		case '2': 
			weather.setID("9807");
			weather.updateweather(); 
			break;
		case '3': 
			weather.setID("44418");
			weather.updateweather(); 
			break;
		case '4': 
			weather.setID("4118");
			weather.updateweather(); 
			break;
		case 'r':
			weather.updateweather();
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
