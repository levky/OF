#include "testApp.h"

void testApp::setup(){
	// this number describes how many bins are used
	// on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
	// if this number is too high, binning is not effective
	// because the screen is not subdivided enough. if
	// it's too low, the bins take up so much memory as to
	// become inefficient.
	int binPower = 4;

	particleSystem.setup(ofGetWidth(), ofGetHeight(), binPower);

	kParticles = 3;
	float padding = 0;
	float maxVelocity = .5;
	for(int i = 0; i < kParticles * 1024; i++) {
		float x = ofRandom(padding, ofGetWidth() - padding);
		float y = ofRandom(padding, ofGetHeight() - padding);
		float xv = ofRandom(-maxVelocity, maxVelocity);
		float yv = ofRandom(-maxVelocity, maxVelocity);
		Particle particle(x, y, xv, yv);
		particleSystem.add(particle);
	}

	ofBackground(0, 0, 0);

	timeStep = 1;
	lineOpacity = 8;
	pointOpacity = 128;
	isMousePressed = false;
	slowMotion = false;
	particleNeighborhood = 30; //too close dist
	particleRepulsion = 50; //force to push others away when get too close
	centerAttraction = .1;
	insightDist = 50;
}

void testApp::update(){
}

void testApp::draw(){
	particleSystem.setTimeStep(timeStep);

	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, lineOpacity);
	particleSystem.setupForces();
	// apply per-particle forces
	glBegin(GL_LINES);
	for(int i = 0; i < particleSystem.size(); i++) {
		Particle& cur = particleSystem[i];
		//add a cohersion force so each particle move around the same direction
		//use the same idea but look for particles within an insight radius and add the sum of force
		particleSystem.flock(cur, insightDist, 5);
		//particle not get too close, ie no over crowding, radius of effect should be too close dist
		particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
		// forces on this particle
		cur.bounceOffWalls(0, 0, ofGetWidth(), ofGetHeight());
		//cur.addDampingForce();
	}
	glEnd();
	// single global forces
	//particleSystem.addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth(), centerAttraction);
	if(isMousePressed)
		particleSystem.addAttractionForce(mouseX, mouseY, 200, 4);
	particleSystem.update();
	ofSetColor(255, 255, 255, pointOpacity);
	particleSystem.draw();
	ofDisableAlphaBlending();

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(kParticles) + "k particles", 32, 32);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 32, 52);
}

void testApp::keyPressed(int key){
	if(key == 'p')
		ofSaveScreen(ofToString(ofGetMinutes()) + "_" + ofToString(ofGetFrameNum()) + ".png");
	if(key == 's') {
		slowMotion = !slowMotion;
		if(slowMotion)
			timeStep = .05;
		else
			timeStep = 1;
	}
}

void testApp::mousePressed(int x, int y, int button){
	isMousePressed = true;
}

void testApp::mouseReleased(int x, int y, int button){
	isMousePressed = false;
}
