#include "testApp.h"
int w;
int h;

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	w=ofGetWidth();
	h=ofGetHeight();
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(w,h);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    colorImg.allocate(w,h);
	grayImage.allocate(w,h);
	grayBg.allocate(w,h);
	grayDiff.allocate(w,h);

	bLearnBakground = true;
	threshold = 80;
	
	//setting for the boids
	pBoids=new boids(100);
	pBoids->setMaxVelocity(10);
	pBoids->setTooCloseDist(100);
	pBoids->setInSightDist(75.0);
	
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

	pBoids->flock();
	pBoids->bounce();
	pBoids->update();
	
	
/*
    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), w,h);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), w,h);
        #endif

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (w*h)/3, 10, true);	// find holes
	}
	
	//overline the shape in the blobs
	
	*/
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	pBoids->draw();
	// draw the incoming, the grayscale, the bg and the thresholded difference
	//ofSetHexColor(0xffffff);
//	colorImg.draw(20,20);
//	grayImage.draw(360,20);
//	grayBg.draw(20,280);
	//grayDiff.draw(360,280);

	// then draw the contours:

	//ofFill();
//	ofSetHexColor(0x333333);
	//ofRect(360,540,320,240);
//	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually,
	// this is how to get access to them:
	/*
	for( int i=0; i<contourFinder.blobs.size(); i++ ) {
	
		//draw backwards so that the outter layer of the line will bounce out the balls
		for (int j = 0; j <contourFinder.blobs[i].nPts ; j=j+20){
			ofCircle(contourFinder.blobs[i].pts[j].x,contourFinder.blobs[i].pts[j].y,3);
			printf("%i, %i \n",i,contourFinder.blobs[i].nPts);
			
			//lineStrip2.addPoint(contourFinder.blobs[i].pts[(contourFinder.blobs[i].nPts)-j-1].x, contourFinder.blobs[i].pts[(contourFinder.blobs[i].nPts)-j-1].y);
		}
		//lineStrip2.createShape();
		//customLines.push_back(lineStrip2);	
	}
	 
    for (int i = 0; i < contourFinder.nBlobs; i++){
    //    contourFinder.blobs[i].draw(360,540);
    }

	// finally, a report:
*/
	ofSetHexColor(0xffffff);
	char reportStr[1024];
	//sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f", threshold, contourFinder.nBlobs, ofGetFrameRate());
	sprintf(reportStr,"framerate :%f",ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);
	 

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
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
void testApp::keyReleased(int key){

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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
