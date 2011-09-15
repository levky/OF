#include "testApp.h"

ofVideoGrabber vidGrabber;
ofxCvColorImage colorImg;
ofxCvColorImage diffs;
ofxCvColorImage old;
bool bLearnBakground;
int threshold;

//--------------------------------------------------------------
void testApp::setup(){  
	
    width = 640;  
    height = 480;  
	
    vidGrabber.setVerbose(true);  
    vidGrabber.setDeviceID(1);  
    vidGrabber.setUseTexture(true);  
    vidGrabber.initGrabber(width, height);  
	
    buffer1 = new int[width * height];  
    buffer2 = new int[width * height];  
    temp = new int[width * height];  
	
    testTex.allocate(width, height, GL_RGB);  
    colorImg.allocate(width,height);  
    diffs.allocate(width, height);  
    old.allocate(width, height);  
	
    bLearnBakground = true;  
    threshold = 30;  
    damping = 0.94;  
}  


void testApp::Step()  
{  
    int i = 0;  
    int yw = 0;  
    for(int y = 1; y < height - 1; y++)  
    {  
        yw = y * width;  
        for(int x = 1; x < width -1; x++)  
        {  
            i = x + yw;  
            buffer2[i] =  ((buffer1[i-1] + buffer1[i+1] + buffer1[i - width] + buffer1[i + width]) >>1 ) - buffer2[i];  
            buffer2[i] =  (int)(buffer2[i]*damping);   
			
        }  
    }  
	
}  

/* this method should render the ripples */  
void testApp::renderMap()  
{  
    int i,xo,yo;  
    double shading;  
    xo = 0;  
    yo = 0;  
    shading = 0.0;  
    int yw = 0;  
    unsigned char *pix = colorImg.getPixels();  
	
    unsigned char* pixels = new unsigned char[width * height * 3];  
    i=0;  
	
    for(int y = 1; y < height - 1; y++)  
    {  
        yw = y * width;  
		
        for(int x = 1; x < width - 1; x++)  
        {  
            i = x + yw;  
            xo = buffer2[i-1] - buffer2[i+1];  
			
			
            yo = buffer2[i-width] - buffer2[i+width];  
            shading = (xo - yo)/2;  
			
			
            int xnew = x + xo;  
            if (xnew < 0) xnew = 0;  
            if (xnew >= width) xnew = width - 1;  
			
            int ynew = y + yo;  
            if (ynew < 0) ynew = 0;  
            if (ynew >= height) ynew = height - 1;  
			
			
            unsigned char tred = pix[((ynew-1)*width+(xnew-1)) + 1];  
            unsigned char tgreen = pix[((ynew-1)*width+(xnew-1)) + 1];  
            unsigned char tblue = pix[((ynew-1)*width+(xnew-1)) + 2];  
            if (shading < 0) shading = 0;  
            if (shading > 255) shading = 255;  
            tred = tred + shading;  
            tgreen = tgreen + shading;  
            tblue = tblue + shading;  
			
            pixels[((y-1)*width+(x-1))*3 + 0] = tred;  
            pixels[((y-1)*width+(x-1))*3 + 1] = tgreen;  
            pixels[((y-1)*width+(x-1))*3 + 2] = tblue;  
			
        }  
    }  
	
    temp = buffer1;  
    buffer1 = buffer2;  
    buffer2 = temp;  
    testTex.loadData(pixels, width, height, GL_RGB);  
	
}  


//--------------------------------------------------------------  
void testApp::update(){  
	
    bool bNewFrame = false;  
    vidGrabber.grabFrame();  
    bNewFrame = vidGrabber.isFrameNew();  
	
    if (bNewFrame){  
		
        //colorImg.setFromPixels(vidGrabber.getPixels(), width, height);  
        //testApp::frameDiff(colorImg, old, diffs, threshold);  
		old = colorImg;  
		testApp::Step();  
		testApp::renderMap();  
    }  
}  

void testApp::draw(){  
	
    // draw the incoming, the grayscale, the bg and the thresholded difference  
    ofSetColor(0xffffff);  
    //colorImg.draw(0,0, width, height);  
    ofEnableAlphaBlending();  
    testTex.draw(0,0,width, height);  
    ofDisableAlphaBlending();  
  
  
  
}  
//--------------------------------------------------------------
void testApp::keyPressed  (int key){


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   buffer1[(y*width+x)] += (int)ofRandom(-waterSize, waterSize);
}

void testApp::windowResized(int w, int h) {

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

void testApp::clearPixelArrays(unsigned char* pixelArray,int Width,int Height,unsigned char R ,unsigned char G,unsigned char B,unsigned char A){
	int bpp = 4;
	for (int y = 0 ;y< Height;y++){
		for (int x = 0 ;x< Width;x++){
			int Pixel = bpp*(y*Width+x);
			pixelArray[Pixel]= R;
			pixelArray[Pixel+1]= G;
			pixelArray[Pixel+2]= B;
			pixelArray[Pixel+3]= A;
		}
	}
}

