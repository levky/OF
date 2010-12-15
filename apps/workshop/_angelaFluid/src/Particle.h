/*
 *  Particle.h
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once
#include "ofxVec3f.h"

class Particle {
public:	

    float x, y;
    float vx, vy;
    float radius;
    float alpha;
    float mass;
	
    void init(float x, float y);
    void update();
	void updateVertexArrays(int i, float* posBuffer, float* colBuffer);
	void drawOldSchool();
private:
	//ofImage img;
	float max_force;
	float max_vel;
	
	float arrive_dist;
	ofxVec3f force;
	ofxVec3f pos;
	ofxVec3f acc;
	ofxVec3f vel;
	int red;
	int green;
	int blue;
};

