#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxShader.h"
#include "ofxVectorMath.h"
#include "ofxFBOTexture.h"

#define NUM_PARTICLES 1000


// ----------------------- Classes for particles
class Pvert {
public:
	float x,y,z;
	Pvert() {
		x=0.0;y=0.0;z=0.0;
	}
};
class Pcolor {
public:
	float r,g,b,a;
	Pcolor() {
		r=0.0;g=0.0;b=0.0;a=0.0;
	}
};


// ----------------------- 
class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void renderFBO();
	
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	// Camera
	ofxVec3f tran, tranv;
	ofxVec3f rot, rotv;
	
	// reset the particle
	void resetParticle(int i);
	
	
	// Color and Vertex VBO
	GLuint	 vbo[2];
	
	float   boxSize;
	
	Pvert	vel[NUM_PARTICLES];
	Pvert	pnts[NUM_PARTICLES];
	Pcolor	color[NUM_PARTICLES];

	float pointSizes[NUM_PARTICLES];
	
	ofxFBOTexture	fbo;
	ofTexture		texture;
	ofxShader		shader;
	
};

#endif
