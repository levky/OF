/*
 *  boids.cpp
 *  openFrameworks
 *
 *  Created by Levky on 25/03/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 * 	Modified by Angela Chim on December 2010
 */

#include "boids.h"

boids::boids(int iNumBoids) {
	num_boids = iNumBoids;
	for (int i = 0; i < num_boids; i++) {
		pBoids.push_back(new boid());
		pBoids.back()->setPosition(ofxVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),300));
	}
}

void boids::update() {
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->update();
	}
}

void boids::bounce() {
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->bounce();
	}
	
}

void boids::draw() {
	for (int i = 0; i < pBoids.size(); i++) {
		ofEnableAlphaBlending();
		pBoids[i]->draw();
		ofDisableAlphaBlending();
	}	
}

void boids::seekParent(ofxVec3f oMainTarget) {
	pBoids[0]->seek(oMainTarget);
	for (int i = 1; i < pBoids.size(); i++) {
		pBoids[i]->seek(pBoids[i-1]->getPosition());
	}
}

void boids::flock() {
	int insight_count = 0;
	ofxVec3f average_vel, average_pos;
	for (int i = 0; i < pBoids.size(); i++) {
		average_vel.set(0,0,0);
		average_pos.set(0,0,0);
		insight_count = 0;
		
		for (int j =0; j < pBoids.size(); j++) {
			if (i == j) continue;
			float dist = (pBoids[i]->getPosition() - pBoids[j]->getPosition()).length();
			
			if (dist <= in_sight_dist) {
				average_vel += pBoids[j]->getVelocity();
				average_pos += pBoids[j]->getPosition();
				insight_count++;
				if (dist <= too_close_dist) {
					pBoids[i]->flee(pBoids[j]->getPosition());
				}
			}
		}
		if (insight_count > 0) {
			average_pos /= insight_count;
			average_vel /= insight_count;
			pBoids[i]->seek(average_pos);
			pBoids[i]->addForce(average_vel - pBoids[i]->getVelocity());
		}
	}
}

vector<boid*> boids::getBoids() {
	return pBoids;
}

void boids::setMaxVelocity(float fMax) {
	fMaxVel = fMax;
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->setMaxVelocity(fMax);
	}		
}

void boids::arrive(ofxVec3f oTarget) {
	float dist;
	for (int i = 0; i < pBoids.size(); i++) {
		dist = (pBoids[i]->getPosition() - oTarget).length();
		if (dist <= in_sight_dist*4) {
			//pBoids[i]->setColor(10,230,10);
			pBoids[i]->seek(oTarget);
		} else {
			//pBoids[i]->setColor(0,0,0);
		}
	}		
}

void boids::flee(ofxVec3f oTarget) {
	float dist;
	for (int i = 0; i < pBoids.size(); i++) {
		dist = (pBoids[i]->getPosition() - oTarget).length();
		if (dist <= in_sight_dist*4) {
			//pBoids[i]->setColor(230,10,10);
			pBoids[i]->flee(oTarget);
		} else {
			//pBoids[i]->setColor(0,0,0);
		}
	}		
}

void boids::explode() {
	float max_vel = pBoids[0]->getMaxVelocity();
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->setVelocity(ofxVec3f(ofRandom(-max_vel*5, max_vel*5), ofRandom(-max_vel*5, max_vel*5), ofRandom(0, -max_vel)));
		pBoids[i]->setColor(0,0,0);
	}			
}

void boids::drift() {
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->drift();
		pBoids[i]->fadeColor(0.99);
	}			
}

void boids::limitNum(int l) {
	while (num_boids > l) {
		num_boids--;
		pBoids.erase(pBoids.begin());
	}
}

void boids::addBoid() {
	num_boids++;
	pBoids.push_back(new boid());
	pBoids.back()->setPosition(ofxVec3f(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),300));
	pBoids.back()->setMaxVelocity(fMaxVel);
}

void boids::addBoid(ofxVec3f po, ofxVec3f ve, int r, int g, int b) {
	num_boids++;
	pBoids.push_back(new boid());
	pBoids.back()->setPosition(po);
	pBoids.back()->setVelocity(ve);
	pBoids.back()->setColor(r,g,b);
	pBoids.back()->setMaxVelocity(fMaxVel);
}

void boids::subtractBoid() {
	if (num_boids > 0) {
		num_boids--;
		pBoids.pop_back();
	}
}

int boids::getNumBoids() {
	return num_boids;
}

float boids::getMaxVel() {
	return fMaxVel;
}

void boids::setTooCloseDist(float dist) {
	too_close_dist = dist;
}

void boids::setInSightDist(float dist) {
	in_sight_dist = dist;
}

float boids::getTooCloseDist() {
	return too_close_dist;
}

float boids::getInSightDist() {
	return in_sight_dist;
}

void boids::randomColor() {
	for (int i = 0; i < pBoids.size(); i++) {
		pBoids[i]->setColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
	}			
}