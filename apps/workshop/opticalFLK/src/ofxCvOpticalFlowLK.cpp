//
// ofxCvOpticalFlowLK.h - a OpenCV cvOpticalFlowLK warpper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of 
// the GNU Lesser General Public License.
//
#define mcounter 7
#define mfast 100
#include "ofxCvOpticalFlowLK.h"

ofxCvOpticalFlowLK::ofxCvOpticalFlowLK(void){
	captureWidth = DEFAULT_CAPTURE_WIDTH;
	captureHeight = DEFAULT_CAPTURE_HEIGHT;

	captureColsStep = DEFAULT_CAPTURE_COLS_STEP;
	captureRowsStep = DEFAULT_CAPTURE_ROWS_STEP;
	
	vel_x = vel_y = NULL;
	counter=0;

	
}

ofxCvOpticalFlowLK::~ofxCvOpticalFlowLK(void){
	if(vel_x != NULL)
		cvReleaseImage(&vel_x);
	if(vel_y != NULL)
		cvReleaseImage(&vel_y);

}
float ofxCvOpticalFlowLK::getx(int px,int py){
	return (int)cvGetReal2D( vel_x, py, px );
	
}
float ofxCvOpticalFlowLK::gety(int px,int py){
	return (int)cvGetReal2D( vel_x, py, px );
}
void ofxCvOpticalFlowLK::allocate(int _w, int _h){
	captureWidth = _w;
	captureHeight = _h;
	
	if(vel_x != NULL)
		cvReleaseImage(&vel_x);
	if(vel_y != NULL)
		cvReleaseImage(&vel_y);

	vel_x = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	vel_y = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	
    cvSetZero(vel_x);
    cvSetZero(vel_y);
}

void ofxCvOpticalFlowLK::setCalcStep(int _cols, int _rows){
	captureColsStep = _cols;
	captureRowsStep = _rows;
}

void ofxCvOpticalFlowLK::calc( ofxCvGrayscaleImage & pastImage, ofxCvGrayscaleImage & currentImage, int size) {
	cvCalcOpticalFlowLK( pastImage.getCvImage(), currentImage.getCvImage(),	cvSize( size, size), vel_x, vel_y );
}

void ofxCvOpticalFlowLK::draw(void){
	if(vel_x == NULL || vel_y == NULL)
		return;
//	ofSetColor(0xffffff);
	ofNoFill();
	float speed;
	float a=0;
	float b=0;
	float lefthigh=captureHeight-1;
	float righthigh=captureHeight-1;
	float lefthighvel=0;
	float righthighvel=0;
	float rightpos=-1;
	float leftpos=-1;
	
	int x, y, dx, dy;
	for ( y = 0; y < captureHeight; y += captureRowsStep ){
		for ( x = 0; x < captureWidth; x += captureColsStep ){

			dx = (int)cvGetReal2D( vel_x, y, x );
			dy = (int)cvGetReal2D( vel_y, y, x );
			speed = dx * dx + dy * dy;
			ofLine(x, y, x+dx, y+dy);
			
			//calculate the total velocity x in the middle of the screen 
			if(y>captureHeight/2&&y<captureHeight/2+20){
			a+=dx;
			b+=dy;
			}
			if(x>0 && x<( captureWidth-1)/3)//left side
			{
				//if the velocity of dx is greater the lefthighvel store the y position and lefthighvel
				if(lefthighvel<dx&& dx>9){
					leftpos=y;
					lefthighvel=dx;
				}
			}
			if(x>(captureWidth-1)*2/3&& x<captureWidth)
			{
				if(righthighvel<dx&& dx>9){
					rightpos=y;
					righthighvel=dx;
				}
			}
		}
	}
	if(leftpos<0)
		leftpos=239;
	if(rightpos<0)
		rightpos=239;
	//right-green
	ofSetColor(0, 255, 0);
	ofFill();
	ofRect((captureWidth-1)*2/3,rightpos,captureWidth/3,20);
	//left-red
	ofSetColor(255, 0, 0);
	ofRect(0,leftpos,captureWidth/3,20);
	
	ofSetColor(255, 255,255);
	ofNoFill();
	ofRect(captureWidth/(mcounter-1)*counter,100 , captureWidth/(mcounter-1)*(counter+1)-captureWidth/(mcounter-1)*counter, 10);
	

	int total=captureWidth*captureHeight;

	string str;
	str+="The velocity x: \n";
	str+= ofToString(a)+"\n";
	str+="The velocity y: \n";
	str+= ofToString(b)+"\n";
	str+="The left bar: \n";
	str+=ofToString(leftpos)+"/n";
	
	ofDrawBitmapString(str,400, 0);
	ofLog(OF_LOG_ERROR, ofToString(a));
	
	if(a>mfast){
		counter+=1;
	}
	else if(a< -mfast){
		counter-=1;
	}
	else
		counter=0;
	
	if( counter>mcounter){
		ofLog(OF_LOG_ERROR,"right");
		ofBackground(100, 0, 0);//red
	}
	if(counter<-mcounter){
	   ofLog(OF_LOG_ERROR, "left");
		ofBackground(0, 100, 0);//green
	}
	
}
