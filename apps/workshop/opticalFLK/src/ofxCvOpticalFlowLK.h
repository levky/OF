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

#pragma once

#include "ofMain.h"
#include "ofxCvConstants.h"
#include "ofxCvGrayscaleImage.h"

//the width of the captured video
#define DEFAULT_CAPTURE_WIDTH 320

//the height of the captured video
#define DEFAULT_CAPTURE_HEIGHT 240

//the size of the columns
#define DEFAULT_CAPTURE_COLS_STEP 4

//the size of the rows
#define DEFAULT_CAPTURE_ROWS_STEP 4

class ofxCvOpticalFlowLK
	{
	public:
		ofxCvOpticalFlowLK(void);
		~ofxCvOpticalFlowLK(void);
		//get the horizontal velocity at a given position. r1 is the x position of the frame and r2 is the y position of the frame.It returns a float number
		float getx(int r1,int r2);
		//get the vertical velocity at a given position. y1 is the x position of the frame and y2 is the y position of the frame.It returns a float number
		float gety(int y1,int y2);
		//create a space to store the frame. _w is the frame width and _h is the frame height.
		void allocate(int _w, int _h);
		//Calculates optical flow for 2 images using classical Lucas & Kanade algorithm
		void calc( ofxCvGrayscaleImage & pastImage, ofxCvGrayscaleImage & currentImage, int size);
		//set the size of the columns and rows.
		void setCalcStep(int _cols, int _rows);	
		//draw the optical flow into the window.It will show a red bar on the left screen and green bar on the right screen. when motion detected motion moving to the left the background will change to green and any motion moving to the right the background will change to red.
		void draw();
		
		
		//the width of the frame
		int captureWidth;
		//the height of the frame
		int captureHeight;
		//the horizontal velocity 
		IplImage* vel_x;
		//the vertical velocity
		IplImage* vel_y;
		//to keep track of the number of times the horizontal velocity go through the same direction
		int counter;	
		
	private:
		//the size of the columns
		int captureColsStep;
		//the size of the rows
		int captureRowsStep;
	};

