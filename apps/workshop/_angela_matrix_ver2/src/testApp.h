/* testApp.h
 * Created by Angela Chim
 * Created: December 2010 
 */
#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "cell.h"
#include "ofxSimpleGuiToo.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"

#define PORT 8000
#define SPORT 9000
#define HOST "169.254.40.78" 

class testApp : public ofBaseApp{

	public:
		void changedirection(int x,int y);
		bool checkneighbor(int ncol,int nrow, int curcol, int curnow);
		void addNewCell();
		void updatePosition();
		void updateLife();
		void updateNumOfCircle();
		void setup();
		void update();
		void draw();
		void maintainCircle(float pslider);
		void maintainCircle2(float pslider);
		void parseOSCMsg();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		Cells Life[windowcol+1][windowrow+1];
		Cells map[windowcol+1][windowrow+1];
		int frames;//frame rate
		int mode;
		int br,bg,bb;//background
		float myColors[4];//background color
		float slider;
		int pcounter; //hit 
		int NumOfALiveCircle;//number of circle
		int deadspeed;//decrease the color by this number of increment
		
		bool flag;//show the ShowMsg
		bool toggle1;// for gui
		bool toggle2;// for gui
	
	
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	
	};

#endif
