#pragma once


#include "ofMain.h"

#include "ofxOpenCv.h"




class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		void clearPixelArrays(unsigned char* pixelArray,int Width,int Height,unsigned char R ,unsigned char G,unsigned char B  ,unsigned char A );


        void Step();
        void renderMap();

        ofImage             im;
        ofTexture           testTex;
        int                 *buffer2;
        int                 *buffer1;
        int                 *temp;
        int                 width;
        int                 height;
        double              damping;

        unsigned char       * pixels;
        unsigned char       *pix;
        int                 i,xo,yo,yw;
        int                 shading;
        int                 waterSize;








};
extern testApp *myApp;
