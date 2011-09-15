#ifndef _TEST_APP
#define _TEST_APP

#define WIDTH			800
#define HEIGHT			450
#define BLOBS_WIDTH		250
#define BLOBS_HEIGHT	250
#define BLOBS_TOTAL		2

#include "ofMain.h"
#include "ofxShader.h"
typedef struct blob{
	int px;
	int py;
	int dx;
	int dy;
};

class testApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();
		void saveOutputImage();
	void addblob();
	
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	void metaEffect();
		ofTexture		tex;
		unsigned char	*texPixels;
	
		int numBlobs;
		int *blogPx;
		int *blogPy;
	
		int *blogDx;
		int *blogDy;
	
		int *vy;
		int *vx; 
	vector<blob> pblobs;
	
	/*vector<int> px;
	vector<int>  py;
	
	vector<int>  dx;
	vector<int>  dy;
	 */
	
			int					screenGrabCount;
		ofImage 			screenGrab;
	ofxShader myShader;

};

#endif
