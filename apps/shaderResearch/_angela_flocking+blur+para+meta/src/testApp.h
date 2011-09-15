/*
* Title: testApp.h
*  Created by Angela Chim
* Summary: This program is the header of testApp, it has all the variables and function needed for this program
* Created: December 2010
*/
#pragma once
#include "ofxVec3f.h"
#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxBox2d.h"
#include "Boids.h"
#include "ofxSimpleGuiToo.h"
#include "ofxOsc.h"
#include "ofxFBOTexture.h"
#include "ofxShader.h"
#include "ofxXmlSettings.h"
#include "shaderBlur.h"

#define maxgravity 15
#define MAXBOIDS  500
#define PORT 8000   //receive
#define SPORT 9000    //send 
//#define HOST "127.0.0.82"//ipod or iphone ip Address
#define UseOSC 1	//0- no, 1- yes
#define OSCInterface 1 //0 - OSCemote, 1- custom TouchOSC
#define BLOBS_WIDTH		100
#define BLOBS_HEIGHT	100

 struct blob{
	int px;
	int py;
	int dx;
	int dy;
};
// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	CustomParticle(){
	}
	ofColor color;
	int masterRed,masterBlue,masterGreen;
	
	//random radius
	void draw1(bool randomcolor,float colorRange) {
		
		if(dead=true && body == NULL) return;
		
		float radius = getRadius();	
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		if(randomcolor){
			ofSetColor(color.r*colorRange+masterRed, color.g*colorRange+masterGreen, color.b*colorRange+masterBlue);
		}
		else
			ofSetColor(masterRed,masterGreen, masterBlue);
		
		ofFill();
		ofCircle(0, 0, radius);	
		
		
		glPopMatrix();
	}
	//not random radius,  set radius
	void draw2(float radius, bool randomcolor) {
		
		if(dead=true && body == NULL) return;
		
		radius = getRadius();
		
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		
		if(randomcolor){
		ofSetColor(color.r+masterRed, color.g+masterGreen, color.b+masterBlue);
		}
		else
		ofSetColor(masterRed,masterGreen, masterBlue);
		
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
	void checkMode();
	void updatePhysic();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
	void addblob();
	void metaupdate();
	//meta------------------------------
	ofTexture		tex;
	unsigned char	*texPixels;
	vector<blob> pblobs;
	int *m_vy;
	int *m_vx; 
	
	bool bmetaball;
	
	//----------------------------------
	char mode;
	ofxVec3f target;
	
	float px, py,vx,vy,xg,yg;
	bool bMouseForce;
	bool bGrabbing;
	bool bFlockings;
	bool bAddBoids;

	bool bShowMsg;
	bool pbGrabbing;
	bool pbMouseForce;
	bool pbFlockings;
	bool pbAGravity;
	bool toggle1;
	
	bool bAGravity;
	bool bGravity;
	bool pbGravity;
	
	boids* pBoids;
	vector<boid*> pBoids2;

	ofxBox2d						box2d;			  //	the box2d world
	vector		<CustomParticle>	customParticles;  //	this is a custom particle the extends a cirlce

	float br,bg,bb;//background color
	
	float timer;//timer for mouse force
	float mtimer;//timer for pboids2
	float gtimer;//timer for gravity
	bool bmouse;
	float pwidth;
	float pheight;
	
	int masterRed,masterBlue,masterGreen;
	float myColors[4];//background color for gui
	float colorRange;
	float number;
	ofVideoGrabber grabber;
	bool hasCamera;
	
	//blur effect
	int stoptime;
	shaderBlur blur;
	float blurSlider;
	float blurSpeed;
	
	//boids
    float boidsMaxVelocity;
    float boidsTooCloseDist;
    float boidsInSightDist;
	bool boids_delete;
	bool boids_adding;
	int boids_limNum;
	int FAFED;

	
	//box2d
	//set mass=3, bounce=0.53, friction=0.3
	float gui_mass;
	float gui_bounce;
	float gui_friction;
	float box2dFPS;
	bool bUpdatePhysic;
	bool bCheckBound;
	
	//custom particle
	float strength;
	float damping;
	float minDis ;
	float particle_radius;
	bool particle_random_radius;
	bool particle_random_color;
		
	ofxXmlSettings XML;
	string HOST;
	float p_particle_radius;
	bool pbrandom_radius;
	
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	
};
