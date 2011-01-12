
#ifndef _TEST_APP
#define _TEST_APP

// 8/8/2008 Converted by Joel Gethin Lewis to OF 0.05 and OS X.
// http://www.joelgethinlewis.com
// Based completely on the original code by Takashi Maekawa.
// Downloaded from Google Code via CVS:
// http://code.google.com/p/of-computervision/
// cvOpFlowLKExample by Takashi Maekawa.
// An usage of example cvOpFlowBM class.

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxCvHaarFinder.h"

class testApp : public ofSimpleApp{
	
public:
	//runs at the start of the program. It initialize the variables such as the webcam, optical flow, color frame, gray frame, threshold and the haar finder
	void setup();
	//gets called repeatedly just before draw() so this place is for any updating of variables.
	void update();
	//gets called to draw everything into the window. 
	void draw();
	//used when any key is pressed
	void keyPressed  (int key);
	//used when the key is released
	void keyReleased (int key);
	//used when the mouse is moved
	void mouseMoved(int x, int y );
	//used when the mouse is dragged
	void mouseDragged(int x, int y, int button);
	//used when the mouse is pressed
	void mousePressed(int x, int y, int button);
	//used when the mouse is released
	void mouseReleased();
	
	//public variables
	ofVideoGrabber 			vidGrabber;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayLastImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvColorImage			colorImg;
	ofxCvOpticalFlowLK		opticalFlow;
	ofxCvHaarFinder			finder;
	int 					threshold;
	bool					bLearnBakground;
};

#endif

/* Original from Takashi
 
 //
 // cvOpFlowLKExample by Takashi Maekawa.
 // An usage of example cvOpFlowBM class.
 //
 
 
 #ifndef _TEST_APP
 #define _TEST_APP
 
 #include "ofMain.h"
 #include "ofCvMain.h"
 
 class testApp : public ofSimpleApp{
 
 public:
 
 void setup();
 void update();
 void draw();
 
 void keyPressed  (int key);
 void mouseMoved(int x, int y );
 void mouseDragged(int x, int y, int button);
 void mousePressed(int x, int y, int button);
 void mouseReleased();
 
 ofVideoGrabber 		vidGrabber;
 ofCvGrayscaleImage 	grayImage;
 ofCvGrayscaleImage 	grayLastImage;
 ofCvGrayscaleImage 	grayBg;
 ofCvGrayscaleImage 	grayDiff;
 ofCvColorImage		colorImg;
 
 ofCvOpticalFlowLK	opticalFlow;
 
 int 				threshold;
 bool				bLearnBakground;
 
 
 };
 
 #endif
 
 
 */