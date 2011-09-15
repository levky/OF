/*
 * Title: testApp.cpp
 * Created by Angela Chim on August 2011
 * Summary: This program is in a openCV program with Delaunay triangulation. I also implemented the code to read the
 * OSC message.  So you can use the touch OSC app in the ipod /iphone.
 *
 */

#include "testApp.h"



void testApp::setup(){

	ofBackground(230, 230, 230);
    ofSetFrameRate(30);
	
	//setting for the boids
	pBoids=new boids(totboids);
	pBoids->setMaxVelocity(10);
	pBoids->setTooCloseDist(45.0);
	pBoids->setInSightDist(75.0);
	z=100;
	mode = 'a'; 
	pBoids->randomColor();

	
	//Camera
	colorImage.allocate(CAM_WIDTH, CAM_HEIGHT);
    threImg.allocate(CAM_WIDTH, CAM_HEIGHT);
    bgImg.allocate(CAM_WIDTH, CAM_HEIGHT);
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);
#else
	vidPlayer.loadMovie("fingers.mov");
	vidPlayer.play();
#endif
	
	
	//default setting for tlength= show triagle less than 100;threshold, triangle colors(rgba) and port number
	ShowShort=true;
	tlength=100;
	threshold =38;
	bLearnBackground = true;
	myColors[0]=255;
	myColors[1]=0;
	myColors[2]=255;
	myColors[3]=100;
	//osc
	receiver.setup(PORT);
	//sender.setup(HOST,SPORT);
	
	showMsg=true;
	int i=pBoids->getBoids().size();
	resolution=max(3,i );
	bFindHoles=true;
	CamMaxArea=(CAM_WIDTH*CAM_HEIGHT)/3;
	CamMinArea=20;
	bResolution=true;
	
}
//change the color of the triangles
void testApp::changeMasterColor(){
	
		triangle.Red=myColors[0];
		triangle.Green=myColors[1];
		triangle.Blue=myColors[2];
		triangle.Alpha=myColors[3];
		
}
//--------------------------------------------------------------
//parseOSCMsg() was used for decoding the different OSC messages and determine what is the appropriate actions.
// There is two type of osc interface they are:
//     0 - oscemote 
//     1 - touchOSC
//--------------------------------------------------------------
void testApp::parseOSCMsg(){
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		switch(UseOSC){
			
				
			case 1:
				//TouchOSC
				if(m.getAddress()=="/1/fader1"){
					int br=m.getArgAsFloat(0)*30;
					//ofBackground(br,bg,bb);
					//myColors[0]=br;
					CamMinArea=br;
				}
				//background color for green
				else if(m.getAddress()=="/1/fader2"){
					int br=m.getArgAsFloat(0)*CAM_WIDTH*CAM_HEIGHT/3;
					//ofBackground(br,bg,bb);
					//myColors[1]=br;
					CamMaxArea=br;
				}
				//background color for blue
				else if(m.getAddress()=="/1/fader3"){
					int br=m.getArgAsFloat(0)*1000;
					//ofBackground(br,bg,bb);
					//myColors[2]=br;
					resolution=max(3,br);
				}
				else if(m.getAddress()=="/1/fader4"){
					int br=m.getArgAsFloat(0)*500;
					//ofBackground(br,bg,bb);
					tlength=br;
				}
				else if(m.getAddress()=="/1/fader5"){
					int br=m.getArgAsFloat(0)*100;
					//ofBackground(br,bg,bb);
					threshold=br;
				}
				else if(m.getAddress()=="/1/toggle1"){
					int br=m.getArgAsInt32(0);
					if(br){
						showMsg=true;
					}
					else {
						showMsg=false;
					}

				}
				else if(m.getAddress()=="/1/toggle2"){
					int br=m.getArgAsInt32(0);
					if(br){
						bFindHoles=true;
					}
					else {
						bFindHoles=false;
					}
					
				}
				else if(m.getAddress()=="/1/toggle3"){
					int br=m.getArgAsInt32(0);
					if(br){
						bResolution=true;
					}
					else {
						bResolution=false;
					}
					
				}
				break;
		}
	}
}


void testApp::update(){
	parseOSCMsg();
	bool bNewFrame =false;
	
	
	changeMasterColor();
#ifdef _USE_LIVE_VIDEO
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
#else
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
#endif
	
	if (bNewFrame)
	{
#ifdef _USE_LIVE_VIDEO
		colorImage.setFromPixels(vidGrabber.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        colorImage.mirror(false, true);
#else
		colorImage.setFromPixels(vidPlayer.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        colorImage.mirror(false, true);
		
#endif
		
	
		
        if(bLearnBackground)
        {
            bgImg = colorImage;
            bLearnBackground = false;
        }
		
        threImg = colorImage;
        threImg.absDiff(bgImg);
        threImg.blur(5);
        threImg.threshold(threshold);
		
		//find holes is false at default
		contourFinder.findContours(threImg,CamMinArea,CamMaxArea, 5, bFindHoles);

		// contourFinder.findContours(threImg, 20, (CAM_WIDTH*CAM_HEIGHT)/3, 5, bFindHoles);
	
		//show short or long triangle	
		triangle.ShowShort=ShowShort;
		
		//boids
		switch (mode) {
			case 'a':
				pBoids->flock();
				pBoids->arrive(target);
				break;
			case 'f':
				pBoids->flock();
				pBoids->flee(target);
				break;
			case 'x':
				pBoids->flock();
				pBoids->explode();
				mode = 0;
				break;
			case 's':
				pBoids->drift();
				break;
			case 'e':
				pBoids->drift();
				break;
			default:
				break;
		}
		pBoids->update();
		pBoids->bounce();
		
		
		int i;
		
		// update triangulation
		triangle.clear();
		blobs.pts.clear();
		for (i=0; i<contourFinder.nBlobs; i++)
        {
			if(bResolution){
				resolution=max( 3.0f, (float)contourFinder.blobs[i].pts.size()/2);
				printf("blobs resolution = %f \n",(float)contourFinder.blobs[i].pts.size());
			}
            triangle.triangulate(contourFinder.blobs[i],resolution ,0,tlength);
        }
 		for (i=0; i<pBoids->getBoids().size(); i++)
		{
			blobs.pts.push_back(ofPoint(pBoids->getBoids()[i]->getPosition().x,pBoids->getBoids()[i]->getPosition().y));
		}
		
		
		if(pBoids->getBoids().size()>2)
			triangle.triangulate(blobs,max(3,(int)blobs.pts.size()),0, tlength);
	}		
}

void testApp::draw(){
	
	//ofDisableAlphaBlending();
	ofSetColor(255, 255, 255);
	//show camera video
	//colorImage.draw(0, 0);
	
    // Thresholded image + contour finder
	
	     threImg.draw(0, 0);
    //contourFinder.draw(0, 0);
	

    // Triangulation
   triangle.draw(0, 0);

	
	
    // Infos
	pBoids->draw();
	
	if(showMsg){
		
		ofSetColor(255,0,0);
		ofDrawBitmapString("Max Velocity: " + ofToString((int)pBoids->getMaxVel()), 10, 10);
		ofDrawBitmapString("Number of Boids: " + ofToString(pBoids->getNumBoids()), 10, 30);
		ofDrawBitmapString("TooCloseDist: " + ofToString(pBoids->getTooCloseDist()), 10, 50);
		ofDrawBitmapString("InSightDist: " + ofToString(pBoids->getInSightDist()), 10, 70);
		ofDrawBitmapString("Mouse Z: " + ofToString(z), 10, 90);
		ofDrawBitmapString("Press 'a'/'z' to increase/decrease max velocity", 200, 10);
		ofDrawBitmapString("Press '+'/'-' to increase/decrease number of boids", 200, 30);
		ofDrawBitmapString("Press 's'/'x' to increase/decrease too close dist", 200, 50);
		ofDrawBitmapString("Press 'd'/'c' to increase/decrease in sight dist", 200, 70);
		ofDrawBitmapString("Press 'f'/'v' to increase/decrease in mouse z", 200, 90);
		ofDrawBitmapString("Move/Drag mouse for seek/flee or press ' ' to explode", 10, 110);
		switch (mode) {
			case 'a':
				ofDrawBitmapString("Attracting Mode", 10, ofGetHeight()-10);
				break;
			case 'f':
				ofDrawBitmapString("Fleeing Mode", 10, ofGetHeight()-10);
				break;
			case 'x':
				ofDrawBitmapString("Explode Mode", 10, ofGetHeight()-10);
				break;
			case 's':
				ofDrawBitmapString("Slinging Mode", 10, ofGetHeight()-10);
				break;
			case 'e':
				ofDrawBitmapString("Emitting Mode", 10, ofGetHeight()-10);
				break;
			default:
				ofDrawBitmapString("Default Mode", 10, ofGetHeight()-10);
				break;
		}
		ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate()), 10, 110 + 20);
		ofDrawBitmapString("nb Triangles : " + ofToString(triangle.nTriangles), 10, 110 + 40);
		ofDrawBitmapString("length: "+ ofToString(tlength), 10,110+60);
		ofDrawBitmapString("threshold: "+ofToString(threshold), 10,110+80);
		ofDrawBitmapString("resolution: "+ ofToString(resolution)+"  bresolution: "+ofToString(bResolution), 10,110+100);
		
	}
	
}

void testApp::keyPressed(int key){
	
	switch (key){
		case '+':
			pBoids->addBoid();
			break;
		case '-':
			pBoids->subtractBoid();
			break;
		case 'a':
			pBoids->setMaxVelocity(pBoids->getMaxVel() + 0.5);
			break;
		case 'z':
			pBoids->setMaxVelocity(pBoids->getMaxVel() - 0.5);
			break;
		case 's':
			pBoids->setTooCloseDist(pBoids->getTooCloseDist() + 0.5f);
			break;
		case 'x':
			pBoids->setTooCloseDist(pBoids->getTooCloseDist() - 0.5f);
			break;
		case 'd':
			pBoids->setInSightDist(pBoids->getInSightDist() + 0.5f);
			break;
		case 'c':
			pBoids->setInSightDist(pBoids->getInSightDist() - 0.5f);
			break;
		case 'f':
			z+=100;
			break;
		case 'v':
			z-=100;
			break;
		case '1':
			mode = 'a';
			break;
		case '2':
			mode = 'f';
			break;
		case '3':
			mode = 'x';
			break;
		case '4':
			mode = 's';
			pBoids->randomColor();
			break;
		case '5':
			mode = 'e';
			pBoids->randomColor();
			break;
		case '6':
			pBoids->setMaxVelocity(pBoids->getMaxVel());
			break;
		case '[':
			tlength--;
			break;
		case ']':
			tlength++;
			break;
		case '0':
			ShowShort=!ShowShort;
			break;
		case ' ':
			bLearnBackground = true;
			break;
		case 'b':
			threshold--;
			break;
		case 'g':
			threshold++;
			break;
		default:
			break;
	}	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if (mode == 'a' || mode == 'f') {
		target.set(x,y,0);
	}
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if (mode =='e') {
		pBoids->limitNum(95);
		for (int i = 0; i < 5; i++) {
			ofxVec3f tp;
			ofxVec3f tv;
			tp.x = x;
			tp.y = y;
			tp.z = 10;
			tv.x = ofRandom(-10, 10);
			tv.y = ofRandom(-10, 10);
			tv.z = ofRandom(-10, 10);
			pBoids->addBoid(tp,tv,(int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
		}
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if (mode == 's') {
		lastpos.x = x;
		lastpos.y = y;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if (mode == 's') {
		ofxVec3f tp;
		ofxVec3f tv;
		tp.x = x;
		tp.y = y;
		tp.z = 50;
		tv.x = (x - lastpos.x)/10;
		tv.y = (y - lastpos.y)/10;
		tv.z = ofRandom(-0.25,0.25);
		pBoids->addBoid(tp,tv,(int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

