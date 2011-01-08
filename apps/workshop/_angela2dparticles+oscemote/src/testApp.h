/*
* Title: testApp.h
*  Created by Angela Chim
* Summary: This program is the header of testApp, it has all the variables and function needed for this program
* Created: December 2010
*/
#pragma once
#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxBox2d.h"
#include "Boids.h"
#include "ofxSimpleGuiToo.h"
#include "ofxOsc.h"
#define maxgravity 15
#define MAXBOIDS  500
#define PORT 8050    //receive 
#define SPORT 9001    //send 
#define HOST "127.0.0.1"//ipod or iphone ip Address

// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	CustomParticle() {
	}
	ofColor color;
	void draw() {
		
		if(dead=true && body == NULL) return;
		
		float radius = getRadius();
		
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		
		ofSetColor(color.r, color.g, color.b);
		ofFill();
		ofCircle(0, 0, radius);	
		
		glPopMatrix();

	}
};

// -------------------------------------------------

class testApp : public ofBaseApp {
	
public:
	
	testApp();
	void setup();
	void update();
	void draw();
	void checkFlag();
	void addBoids(float mouseX, float mouseY);
	void deleteBoids();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
	float px, py,vx,vy;
	bool bMouseForce;
	bool bGrabbing;
	bool bFlockings;
	bool bAddBoids;
	bool bAGravity;
	bool bShowMsg;
	bool pbGrabbing;
	bool pbMouseForce;
	bool pbFlockings;
	bool pbAGravity;
	bool toggle1;
	
	boids* pBoids;
	vector<boid*> pBoids2;

	ofxBox2d						box2d;			  //	the box2d world
	//vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	//vector		<ofxBox2dPolygon>	polygons;		  //	defalut box2d polgons
	//vector		<ofxBox2dRect>		boxes;			  //	defalut box2d rects
	//vector      <ofxBox2dLine>		lines;			  //	default box2d lines (hacked)
	vector		<CustomParticle>	customParticles;  //	this is a custom particle the extends a cirlce

	//ofxBox2dCircle					ballJoints[5];	  //	ball joints
	//ofxBox2dJoint					joints[5];		  //	box2d joints
	//ofxBox2dLine					lineStrip;		  //	a linestrip for drawing

	float br,bg,bb;//background color
	float myColors[4];//background color for gui
	float timer;//timer for mouse force
	float mtimer;//timer for pboids2
	bool bmouse;
	float pwidth;
	float pheight;
		
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	
};
