/*
 *  boid.cpp
 *  openFrameworks
 *
 *  Created by Levky on 25/03/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "boid.h"

boid::boid() {
	
	pos.set(300.0f, 200.0f, 0.0f);
	acc.set(0.4, 0.4, 0.0f);
	vel.set(ofRandom(0.1f, 0.4f), ofRandom(0.1f, 0.4f), 0.3f);
	vel =20.0f;
	
	max_vel =20.0f;
	mass = 1.0f;
	
	max_force = 2.0f;
	force.set(0.0f, 0.0f, 0.0f);

	arrive_dist = 200.0f;
	
	red = 0;
	green = 0;
	blue = 0;
	radius=10;
	
}
void boid::update() {
	force.limit(max_force);
	vel += force;
	vel.limit(max_vel);
	pos += vel;
}

void boid::draw() {
	ofEnableSmoothing();
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	
	glPopMatrix();
	ofSetLineWidth(2);

	
	ofSetColor(red,green,blue,100);
	//
	
	ofCircle(pos.x,pos.y, radius);
	ofFill();
	
	ofEnableSmoothing();
	
	ofSetColor(red,green,blue,100);
	ofSetLineWidth(3);
	
	//ofCircle(pos.x, pos.y, 6*pos.z*0.015);
	ofCircle(pos.x, pos.y,radius);
	ofDisableSmoothing();
	
}

void boid::bounce() {
	if (pos.x > ofGetWidth()) {
		pos.x = ofGetWidth();
		vel.x *= -1;
	}
	else if (pos.x < 0) {
		pos.x = 0;
		vel.x *= -1;
	}
	
	if (pos.y > ofGetHeight()) {
		pos.y = ofGetHeight();
		vel.y *= -1;
	}
	else if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1;
	}
	
	if (pos.z < 0) {
		pos.z = 0;
		vel.z *= -1;
	}
	else if (pos.z > 150) {
		pos.z = 150;
		vel.z *= -1;
	}
}

void boid::seek(ofxVec3f oTarget) {
	ofxVec3f desired_vel = oTarget - pos;
	desired_vel.scale(max_vel);
	desired_vel -= vel;
	addForce(desired_vel);
}

void boid::flee(ofxVec3f oTarget) {
	ofxVec3f desired_vel = oTarget - pos;
	desired_vel.scale(max_vel);
	desired_vel-= vel;
	subtractForce(desired_vel/2);
}

void boid::arrive(ofxVec3f oTarget) {
	ofxVec3f desired_vel = oTarget - pos;
	float dist = desired_vel.length();
	desired_vel.normalize();
	
	if (dist <= arrive_dist) {
		desired_vel *= ((max_vel * dist / arrive_dist));
		ofSetColor(0x00);
	}
	else {
		desired_vel *= max_vel;
	}
	
	if (dist > 10) {
		desired_vel -= vel;
		addForce(desired_vel);
	}
	else {
		force = 0;
		vel = 0;
	}
}

void boid::purse(boid* pBoid) {
	float dist = (pBoid->getPosition() - getPosition()).length();
	float ahead_time = dist / max_vel;
	ofxVec3f predicted_target = pBoid->getPosition() + pBoid->getVelocity()*ahead_time;
	seek(predicted_target);
}

void boid::drift() {
	vel *= 0.99;
	force = 0;
}

void boid::addForce(ofxVec3f oForce) {
	force += oForce;
}

void boid::subtractForce(ofxVec3f oForce) {
	force -= oForce;
}

ofxVec3f boid::getPosition() {
	return pos;
}

ofxVec3f boid::getVelocity() {
	return vel;
}

void boid::setPosition(ofxVec3f oPos) {
	pos = oPos;
}
void boid::setPosition(float x,float y){
	pos.set(x,y,0);
}
void boid::setMaxVelocity(float fMax) {
	max_vel = fMax;
}

float boid::getMaxVelocity() {
	return max_vel;
}

void boid::setVelocity(ofxVec3f	oVel) {
	vel = oVel;
}

void boid::setVelocity(float x,float y) {
	vel.set(x,y,0);
}

void boid::setColor(int iRed, int iGreen, int iBlue) {
	red = iRed;
	green = iGreen;
	blue = iBlue;
}

void boid::fadeColor(float rate) {
	red *= rate;
	green *= rate;
	blue *= rate;
}