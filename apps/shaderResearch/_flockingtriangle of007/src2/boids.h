/*
 *  boids.h
 *  openFrameworks
 *
 *  Created by Levky on 25/03/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BOIDS_H
#define	BOIDS_H

#include <vector>
#include "boid.h"
#include "ofxVec3f.h"

class boids {
	public:
		boids(int iNumBoids);
		void update();
		void draw();
	
		void bounce();
		void seekParent(ofxVec3f oMainTarget);
		void flock();
		vector<boid*> getBoids();
		void setMaxVelocity(float fMaxVel);
		void arrive(ofxVec3f oTarget);
		void flee(ofxVec3f oTarget);
		void explode();
		void drift();
		void limitNum(int l);
		
		void addBoid();
		void addBoid(ofxVec3f po, ofxVec3f ve, int r, int g, int b);
		void subtractBoid();
		int getNumBoids();
		float getMaxVel();
		void setTooCloseDist(float dist);
		void setInSightDist(float dist);
		float getTooCloseDist();
		float getInSightDist();
	
		void randomColor();
	
	private:
		int num_boids;
		vector<boid*> pBoids;
		float fMaxVel;
		float too_close_dist;
		float in_sight_dist;

};
#endif
