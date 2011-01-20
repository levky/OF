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
#define UseOSC 0	//0- no, 1- yes
#define OSCInterface 1 //0 - OSCemote, 1- custom TouchOSC

// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	CustomParticle(){
	}
	ofColor color;
	int masterRed,masterBlue,masterGreen;
	ofImage loader;
	
	void draw() {
		
		if(dead=true && body == NULL) return;
		
		float radius = getRadius();
		
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		ofSetColor(color.r+masterRed, color.g+masterGreen, color.b+masterBlue);
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
	void sendOscFlag();
	void checkGravity();
	void parseOSCMsg();
	void changeMasterColor();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	
	float px, py,vx,vy,xg,yg;
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
	bool bGravity;
	bool pbGravity;
	
	boids* pBoids;
	vector<boid*> pBoids2;

	ofxBox2d						box2d;			  //	the box2d world
	vector		<CustomParticle>	customParticles;  //	this is a custom particle the extends a cirlce

	float br,bg,bb;//background color
	float myColors[4];//background color for gui
	float timer;//timer for mouse force
	float mtimer;//timer for pboids2
	float gtimer;//timer for gravity
	bool bmouse;
	float pwidth;
	float pheight;
	
	int masterRed,masterBlue,masterGreen;
		
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	
};
