/*
 *  boid.h
 *  openFrameworks
 *
 *  Created by Levky on 25/03/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef BOID_H
#define BOID_H
#include "ofxVec3f.h"
#include "ofMain.h"

#include "ofxMSAFluid.h"
class boid {
	public:
		boid();
		void update();
		void draw();
		void bounce();
			//steering behaviors
		void addForce(ofxVec3f oForce);
		void subtractForce(ofxVec3f oForce);
		void seek(ofxVec3f oTarget);
		void flee(ofxVec3f oTarget);
		void arrive(ofxVec3f oTarget);
		void purse(boid* pBoid);
		void drift();
		
	
		ofxVec3f getPosition();
		ofxVec3f getVelocity();
	
		void setPosition(ofxVec3f oPos);
		void setMaxVelocity(float fMax);
		float getMaxVelocity();
		void setVelocity(ofxVec3f oVel);
		void setColor(int red, int green, int blue);
		void fadeColor(float rate);
		
		int red;
		int green;
		int blue;
		
	private:
		ofImage img;
		float max_force;
		float max_vel;
		float mass;
		float arrive_dist;
		ofxVec3f force;
		ofxVec3f pos;
		ofxVec3f acc;
		ofxVec3f vel;

		int radius;
		

			
};
#endif