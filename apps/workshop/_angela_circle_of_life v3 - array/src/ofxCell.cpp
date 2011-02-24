/*
 *  ofxCell.cpp
 *  openFrameworks
 *  Circle of Life v2 - without pointer
 *
 *  Created by Angela Chim 
 *  Created: February 2011
 */

#include "ofMain.h"
#include "ofxCell.h"

ofxCell::ofxCell(){
	alive=false;
	mode=ofRandom(0,3);

}

void ofxCell::setCell (int r, int s){

	ring=r;
	steps=s;
	ringRadius=ring*ringSize;
	totalSteps = ceil(floor(2*PI*ringRadius)/(2 * circle_radius ));
	angleSteps=360./totalSteps;
	angle=steps*angleSteps;
	if(ring<=0){
		totalSteps=1;
		angleSteps=1;
		angle=0;
	}
}

int ofxCell::CalcTotSteps (int r){
	int tempringradius;
	int ans;
	tempringradius=r*ringSize;
	ans= ceil(floor(2*PI*tempringradius)/(2 * circle_radius ));
	
	if(r<0){
		ans=0;
	}
	return ans;
}

float ofxCell::CalcAngleStep(int r){
	int tempRR,tempC,totStep;
	tempRR=r*ringSize;
	totStep = ceil(floor(2*PI*tempRR)/(2 * circle_radius ));
	return(360./totStep);
	
}
float ofxCell::CalcAngle(int r, int s){
	int tempRR,tempC,totStep;
	float aStep;
	tempRR=r*ringSize;
	totStep = ceil(floor(2*PI*tempRR)/(2 * circle_radius ));
	aStep=(360./totStep);
	if(aStep==INFINITY || aStep<0){
		aStep=0;
	}
	return((float)s*aStep);
}

void ofxCell::setMaxRing(int maxRingNum){
	maxRing=maxRingNum;
}

void ofxCell::changedirection(int i){
	if(direction==0){
		direction=2;
	}
	else if(direction==1){
		direction=3;
	}
	else if(direction==2){
		direction=0;
	}
	else if(direction==3){
		direction=1;
	}
}


int ofxCell::getNextRing(){
	int temp;
	ofxCell xcell;
	if(direction==0){
		temp=ring-1;
	}
	else if(direction==1){
		temp=ring;
	}
	else if(direction==2){
		temp=ring+1;
	}
	else if(direction==3){
		temp=ring;
	}
	
	return temp;
}
//condition:
//if ring =1, nextring =0: nextangle and nextanglestep is infinity or negative
//if ring= 1, nextring =2: then calculate the next step
//if ring =0, nextring =1: next step is equal to ofRandom(0,7);
//if ring =0, nextring =-1: next angle and angle step is unknown
//any ring greater than 1: the calculation of the step is equal (current angle)/(angle step of next ring)+0.5
int ofxCell::getNextStep(){
	int temp;
	int ans;
	int nextring=getNextRing();
	float currangle=angle;
	//if ring is not equal to nextring 
	if(ring==1&&nextring==0){
		ans=0;
	}
	else if(ring==1 && nextring==2){
		ans=((float)currangle/(float)CalcAngleStep(nextring)+.5);
	}
	else if(ring==0 && nextring==1){
		ans=ofRandom(0,7);
	}
	else if(ring>1){
		ans=((float)currangle/(float)CalcAngleStep(nextring)+.5);
	} 
	else{
		ans=0;
	}
	//--------------
	if(direction==0){
		temp=ans;
	}
	else if(direction==1){
		temp=steps+1;
	}
	else if(direction==2){
		temp=ans;
	}
	else if(direction==3){
		temp=steps-1;
	}
	else{
		ofLog(OF_LOG_ERROR, "cannot find direction");
	}
	//-----------
	if(temp<0){
		temp=CalcTotSteps(nextring)-1;
	}
	else if(temp>=CalcTotSteps(nextring)){
		temp=0;
	}

	return temp;	
}

void ofxCell::setColor(ofColor a){
	color.r=a.r;
	color.g=a.g;
	color.b=a.b;
}

void ofxCell::setColor(int r, int g, int b){
	color.r=r;
	color.g=g;
	color.b=b;
}
//condition:
//if ring =1, nextring =0: nextangle and nextanglestep is infinity or negative
//if ring =0, nextring =-1: next angle and angle step is unknown
//any ring greater than 1: the calculation of the step is equal (current angle)/(angle step of next ring)+0.5
void  ofxCell::decreasering(){
	int ans;
	int changering;
	int nextring=ring-1;
	float currangle=angle;
	//if ring is not equal to nextring 
	if(ring==1&&nextring==0){
		ans=0;
	}
	else if(ring>1){
		ans=((float)currangle/(float)CalcAngleStep(nextring)+.5);
	} 
	
	else{
		ans=0;
	}
	setCell(nextring,ans);
	
}

//condition:
//if ring= 1, nextring =2: then calculate the next step
//if ring =0, nextring =1: next step is equal to ofRandom(0,7);
//any ring greater than 1: the calculation of the step is equal (current angle)/(angle step of next ring)+0.5

void  ofxCell::increasering()
{
	int ans;
	int changering;
	int nextring=ring+1;
	float currangle=angle;
	

	if(ring==0 && nextring==1){
		ans=ofRandom(0,7);
	}
	else if(ring<0){
		ans=0;
	}
	else if(ring>1){
		ans=((float)currangle/(float)CalcAngleStep(nextring)+.5);
	} 
	else{
		ans=0;
	}
	
	setCell(nextring,ans);
}	

void ofxCell::randomdirection(){
	
	int temp1;
	temp1=ofRandom(0,1000);
	if(temp1<500)  direction=1;
	else direction=3;
}

void ofxCell::draw(){
	if(alive){
	ofSetColor(color.r, color.g, color.b);
	ofFill();
	ofCircle(ringRadius*cos(CalcAngle(ring, steps )*PI/180.)+ofGetWidth()/2,-ringRadius*sin(CalcAngle(ring, steps)*PI/180.)+ofGetHeight()/2,circle_radius-2);
	//ofDrawBitmapString(ofToString(ring), ringRadius*cos(angle*PI/180.)+ofGetWidth()/2, -ringRadius*sin(angle*PI/180.)+ofGetHeight()/2+20);
	//ofDrawBitmapString(ofToString(steps), ringRadius*cos(angle*PI/180.)+ofGetWidth()/2, -ringRadius*sin(angle*PI/180.)+ofGetHeight()/2+40);
	//ofDrawBitmapString(ofToString(CalcTotSteps(ring) ), ringRadius*cos(angle*PI/180.)+ofGetWidth()/2, -ringRadius*sin(angle*PI/180.)+ofGetHeight()/2+60);
	//ofDrawBitmapString(ofToString(condition ), ringRadius*cos(angle*PI/180.)+ofGetWidth()/2, -ringRadius*sin(angle*PI/180.)+ofGetHeight()/2+80);
	}
}
