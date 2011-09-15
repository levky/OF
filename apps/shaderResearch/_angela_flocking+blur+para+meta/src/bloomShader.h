/*
 *  bloomShader.h
 *  shaderTest
 *
 *  Created by astellato on 6/9/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxShader.h" 
#include "ofxFBOTexture.h"

class bloomShader{
public:
	void setup(int fboW, int fboH);
	void beginRender();
	void endRender();
	void setParams(float _bloomSize);
	void draw(float x, float y, float w, float h, bool useShader);
	
	ofxShader shader;
	ofxFBOTexture fbo;
	
	float bloomSize;
};