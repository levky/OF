#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(0, 0,200);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);		

	opticalFlow.allocate(320, 240);
	
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayLastImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	bLearnBakground = true;
	threshold = 80;
	finder.setup("aGest.xml");
}

//--------------------------------------------------------------
void testApp::update(){
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		colorImg.mirror(false, true);
		grayImage.setFromColorImage(colorImg);
		
		
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
	
		opticalFlow.calc(grayLastImage,grayImage,11);
		
		grayLastImage = grayImage;
	}
	finder.findHaarObjects(grayImage);

}

//--------------------------------------------------------------
void testApp::draw(){
	
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	
	colorImg.draw(20,20);	
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	// then draw the contours:
	ofFill();
	ofSetColor(0x333333);
	ofRect(360,540,320,240);
	ofSetColor(0xffffff);
	glPushMatrix();
	glTranslatef(360,540,0);
	opticalFlow.draw();
	glPopMatrix();

	
	ofSetColor(0xffffff);
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
	}
		
	ofDrawBitmapString("thresold: "+ofToString(threshold), 20, 600);
	ofDrawBitmapString("ofgetelasedtime: "+ofToString(ofGetElapsedTimef()), 20, 620);
//detecting hand
	int temp3=0;
	int temp4=0;
	if(finder.blobs.size()>0){
		temp3=finder.blobs[0].boundingRect.x+finder.blobs[0].boundingRect.width;
		temp4=finder.blobs[0].boundingRect.x;
	}
	ofDrawBitmapString(	ofToString(temp4)+"     "+ofToString(temp3), 20, 630);
	int temp=0;
	int temp2=0;
	if(finder.blobs.size()>0){
		temp=finder.blobs[0].boundingRect.y+finder.blobs[0].boundingRect.height;
		temp2=finder.blobs[0].boundingRect.y;
	}
	ofDrawBitmapString(	ofToString(temp2)+"     "+ofToString(temp), 20, 640);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case 's':
			vidGrabber.videoSettings();
			break;
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 'b':
			ofBackground(0,0,200);
			break;
		case 't':
			ofResetElapsedTimeCounter();
			break;

	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
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
void testApp::mouseReleased(){
	
}


/* original test app.c from takashi
 
 //
 // cvOpFlowLKExample by Takashi Maekawa.
 // An usage of example cvOpFlowBM class.
 //
 
 #include "testApp.h"
 
 
 //--------------------------------------------------------------
 void testApp::setup(){	 
 vidGrabber.setVerbose(true);
 vidGrabber.initGrabber(320,240);		// windows direct show users be careful
 // some devices (dvcams, for example) don't 
 // allow you to capture at this resolution. 
 // you will need to check, and if necessary, change 
 // some of these values from 320x240 to whatever your camera supports
 // most webcams, firewire cams and analog capture devices will support this resolution.
 
 opticalFlow.allocate(320, 240);
 
 colorImg.allocate(320,240);
 grayImage.allocate(320,240);
 grayLastImage.allocate(320,240);
 grayBg.allocate(320,240);
 grayDiff.allocate(320,240);
 bLearnBakground = true;
 threshold = 80;
 }
 
 //--------------------------------------------------------------
 void testApp::update(){
 ofBackground(100,100,100);
 vidGrabber.grabFrame();
 
 if (vidGrabber.isFrameNew()){
 
 colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
 grayImage.setFromColorImage(colorImg);
 
 
 if (bLearnBakground == true){
 grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
 bLearnBakground = false;
 }
 
 // take the abs value of the difference between background and incoming and then threshold:
 grayDiff.absDiff(grayBg, grayImage);
 grayDiff.threshold(threshold);
 
 // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
 // also, find holes is set to true so we will get interior contours as well....		
 
 opticalFlow.calc(grayLastImage,grayImage,11);
 
 grayLastImage = grayImage;
 }
 }
 
 //--------------------------------------------------------------
 void testApp::draw(){
 
 // draw the incoming, the grayscale, the bg and the thresholded difference
 ofSetColor(0xffffff);
 
 colorImg.draw(20,20);	
 grayImage.draw(360,20);
 grayBg.draw(20,280);
 grayDiff.draw(360,280);
 
 // then draw the contours:
 ofFill();
 ofSetColor(0x333333);
 ofRect(360,540,320,240);
 ofSetColor(0xffffff);
 glPushMatrix();
 glTranslatef(360,540,0);
 opticalFlow.draw();
 glPopMatrix();
 
 // finally, a report:
 
 ofSetColor(0xffffff);
 //char reportStr[1024];
 //sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i", threshold, contourFinder.nBlobs);
 //ofDrawBitmapString(reportStr, 20, 600);
 
 }
 
 
 //--------------------------------------------------------------
 void testApp::keyPressed  (int key){ 
 
 switch (key){
 case 's':
 vidGrabber.videoSettings();
 break;
 case ' ':
 bLearnBakground = true;
 break;
 case '+':
 threshold ++;
 if (threshold > 255) threshold = 255;
 break;
 case '-':
 threshold --;
 if (threshold < 0) threshold = 0;
 break;
 }
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
 void testApp::mouseReleased(){
 
 }
 
 */