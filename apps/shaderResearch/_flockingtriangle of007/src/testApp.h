/*
 * Title: testApp.h
 * Created by Angela Chim on August2011
 * Summary: This program is the header of testApp, it has all the variables and function needed for this program
 * 
 */

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxTriangle.h"
#include "ofxOpenCv.h"
#include "boids.h"
#include "ofxOsc.h"
#define CAM_WIDTH      1024
#define CAM_HEIGHT     768
#define PORT 8000   //receive
//#define SPORT 9000    //send 
#define UseOSC 1	//0- no, 1- yes
#define _USE_LIVE_VIDEO
#define totboids 0

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void parseOSCMsg();
	void changeMasterColor();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);private:


	//boids
	boids *		pBoids;
	char		mode;
	int			z;
	ofxVec3f	target;
	ofPoint		lastpos;
	
	//Triangle
	ofxTriangle		triangle;
	ofxCvBlob		blobs;
	bool			ShowShort;
	float			myColors[4];
	int				tlength;
private:
	#ifdef _USE_LIVE_VIDEO
	ofVideoGrabber 		vidGrabber;
	#else
	ofVideoPlayer 		vidPlayer;
	#endif
	
	ofxCvColorImage         colorImage;
	ofxCvGrayscaleImage     threImg;
	ofxCvGrayscaleImage     bgImg;
	ofxCvContourFinder      contourFinder;
	
	int                      threshold;
	bool                     bLearnBackground;
	ofxOscReceiver receiver;
//	ofxOscSender sender;
	
	//show msg
	bool showMsg;
	
	//blob paramethers
	int resolution;
	bool bResolution;
	bool bFindHoles;
	int CamMaxArea;
	int CamMinArea;
	
	
};

#endif
