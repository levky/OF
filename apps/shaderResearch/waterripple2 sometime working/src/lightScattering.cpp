#include "lightScattering.h"

#define OFF_SCREEN_RENDER_RATIO 6

//--------------------------------------------------------------
void lightScattering::setup(int fboW, int fboH){	
	
	//ofBackground(255,255,255);	
	//ofSetVerticalSync(true);
	
	fbo.allocate(fboW, fboH, true);
	
	shader.loadShader("shaders/lightScattering");
	
	pos.set(100, 100);
	posZ = 100;
	
	GLdouble winX=0;
	GLdouble winY=0;
	uniformLightX = winX/((float)ofGetWidth()/OFF_SCREEN_RENDER_RATIO);
	uniformLightY = winY/((float)ofGetHeight()/OFF_SCREEN_RENDER_RATIO);

	uniformExposure = 0.0034f;
	uniformDecay = 1.0f;
	uniformDensity = 0.84f;
	uniformWeight = 5.65f;	
}

//--------------------------------------------------------------
void lightScattering::beginRender(){
	fbo.swapIn();
	
}

//--------------------------------------------------------------
void lightScattering::endRender(){
	fbo.swapOut();
}

//--------------------------------------------------------------
void lightScattering::setLightParams(float xPos, float yPos){
	pos.x			= xPos;
	pos.y			= yPos;
}

//--------------------------------------------------------------
void lightScattering::draw(float x, float y, float w, float h, bool useShader){
	
	
	if( useShader ){
		
		//first the horizontal shader 
		shader.setShaderActive(true);		
		shader.setUniformVariable2f("lightPositionOnScreen",pos.x/OFF_SCREEN_RENDER_RATIO,pos.y/OFF_SCREEN_RENDER_RATIO);
		shader.setUniformVariable1f("exposure",uniformExposure);
		shader.setUniformVariable1f("decay",uniformDecay);
		shader.setUniformVariable1f("density",uniformDensity);
		shader.setUniformVariable1f("weight",uniformWeight);
		
		ofSetColor(255, 255, 255);
		fbo.draw(0, 0, w, h);
		
		shader.setShaderActive(false);
		
	}else{
		fbo.draw(0, 0, w, h);
	}
	
}