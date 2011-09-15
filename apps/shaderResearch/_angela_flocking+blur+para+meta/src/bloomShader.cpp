/*
 *  bloomShader.cpp
 *  shaderTest
 *
 *  Created by astellato on 6/9/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "bloomShader.h"

void bloomShader::setup(int fboW, int fboH){
	
	ofBackground(255,255,255);	
	ofSetVerticalSync(true);
	
	fbo.allocate(fboW, fboH, true);
	
	shader.loadShader("shaders/bloom");
	
	bloomSize = 0.0f;
}

void bloomShader::beginRender(){
	fbo.swapIn();
}

void bloomShader::endRender(){
	fbo.swapOut();
}

void bloomShader::setParams(float _bloomSize){
	
	bloomSize = _bloomSize;
	
}

void bloomShader::draw(float x, float y, float w, float h, bool useShader){
	
	if(useShader){
		shader.setShaderActive(true);
		//shader.setUniformVariable2f("sampleDivisor", divisor.x, divisor.y);
		ofSetColor(255, 255, 255);
		fbo.draw(0, 0);
		shader.setShaderActive(false);
	}
	else{
		fbo.draw(0, 0);
	}
}