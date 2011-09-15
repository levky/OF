#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	ofPoint iniPos(0,0,0); //the position is refering to the center of the grid
	ofPoint gridSize(1000, 1000, 1000);
	int gridResX = 30;
	int gridResY = 30;
	int gridResZ = 30;
	marchingCubes.init(iniPos, gridSize, gridResX, gridResY, gridResZ);
	glEnable(GL_DEPTH_TEST);
	metaBalls.resize(NUM_META_BALLS);
	for(int i=0; i<metaBalls.size(); i++){
		metaBalls[i].init(iniPos);
	}
	light.pointLight(0, 0, 255, iniPos.x, iniPos.y, 500);
	reflections.directionalLight(100, 100, 100, 0, -1, 0);
	reflections.specular(200, 200, 200);
	ofxMaterialSpecular(250, 250, 250);
	ofxMaterialShininess(30);
	ofxSetSmoothLight(true);
	
	ofSetLogLevel(OF_LOG_VERBOSE);
	bSaveModel = false;
}

//--------------------------------------------------------------
void testApp::update(){
	float counter = ((float)ofGetFrameNum()) * 0.01f;
	float threshold = ((float)mouseX / ofGetWidth());
	marchingCubes.resetIsoValues();
	ofPoint force;
	ofPoint gridCenter = marchingCubes.getGridPos();
	float randomStep = 10;
	for(int i=0; i<metaBalls.size(); i++){
		force.x = ofRandom(-randomStep, randomStep);
		force.y = ofRandom(-randomStep, randomStep);
		force.z = ofRandom(-randomStep, randomStep);
		force += (gridCenter - metaBalls[i]) * 0.003f;
		metaBalls[i].update(force, 0.9);
		marchingCubes.addMetaBall(metaBalls[i], metaBalls[i].size);
	}
	
	marchingCubes.update(threshold, true);
	
	if(bSaveModel){
		bSaveModel = false;
		marchingCubes.saveModel("testBin.stl");
		marchingCubes.saveModel("testASCII.stl", true);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
//	marchingCubes.draw();
	ofxLightsOn();
	ofPoint center(ofGetWidth()*0.5f, ofGetHeight()*0.5f, -1000);
	ofPoint gridSize = marchingCubes.getGridSize();
	float counter = (float)ofGetFrameNum();
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glRotatef(counter*0.05f, 1.0f, 0.0f, 0.0f);
	glRotatef(counter*0.1f, 0.0f, 1.0f, 0.0f);
	vector<ofPoint>& vertices = marchingCubes.getVertices();
	vector<ofPoint>& normals = marchingCubes.getNormals();
	int numVertices = vertices.size();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<numVertices; i++){
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
	ofxLightsOff();
	glColor3f(0.0f, 0.0f, 0.0f);
	marchingCubes.drawCube();
	//marchingCubes.debugDraw();
	glPopMatrix();
	
	string info = "fps:" + ofToString(ofGetFrameRate()) + 
	+ "\nnum triangles:" + ofToString(marchingCubes.getNumTriangles(), 0)
	+ "\nthreshold:" + ofToString(marchingCubes.getThreshold());
	ofDrawBitmapString(info, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == ' ')bSaveModel = true;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

