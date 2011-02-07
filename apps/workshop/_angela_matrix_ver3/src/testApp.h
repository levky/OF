/* testApp.h
 * Created by Angela Chim
 * Created: December 2010 
 */
#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "cell.h"
#include "ofxXmlSettings.h"
#include "ofxSimpleGuiToo.h"
#include "ofxOsc.h"

#define PORT 8000
#define SPORT 9000
#define HOST "172.20.10.124"
#define left 0
#define right 1
#define opp 2
#define debug 1

#define useOSC 1 //0- not using OSC, 1- using OSC
#define OSCInterface 1 //0 - for oscemote, 1 - for touch osc

class testApp : public ofBaseApp{

	public:

	//--------------------------------------------------------------
	//sColorIsEqualSliderColor() was used for updating the cell's color. It will use the slider color
	// parameter: is the index number of the array
	//--------------------------------------------------------------
	void sColorIsEqualSliderColor(int i);
	//--------------------------------------------------------------
	//sliderColorIsEqualsColor() was used for updating all the slider color
	// parameter: is the index number of the array
	//--------------------------------------------------------------
	void sliderColorIsEqualsColor(int i);
	//--------------------------------------------------------------
	// setStage() was used for setting the stage parameters, such as the direction of each stage, 
	// the size of the stage, and the color range between the stage.
	//--------------------------------------------------------------
	void setStage();
	//--------------------------------------------------------------
	//turnleft() was used for mapping the current position to the left position.
	//	example: when the current position was pointing to the North, the next position will be NorthWest.
	//--------------------------------------------------------------
	void turnleft(int x,int y);
	//--------------------------------------------------------------
	//turnright() was used for mapping the current position to the right position.
	//	example: when the current position was pointing to the North, the next position will be NorthEast.
	//--------------------------------------------------------------
	void turnright(int x,int y);
	//--------------------------------------------------------------
	//turnopposite() was used for mapping the current position to the opposite position.
	//	example: when the current position was pointing to the North, the next position will be South.
	//--------------------------------------------------------------
	void turnopposite(int x,int y);
	//--------------------------------------------------------------
	// changedirection() was used for the cell to change direction and it will subtract that cell deadspeed.
	// The parameter: contain the x and y position of the 2d matrix. x is in the range between 0 to 39.  
	//					y is in the range between 0 to 29.
	//--------------------------------------------------------------
	void changedirection(int x, int y);
	//--------------------------------------------------------------
	// The checkneighbor() function will return true if there is any neighbor. 
	//
	// The parameter: x is the column position; y is the row position of the neighbor;
	//					curx is the column position; cury is the row position of the current cell;
	//					column(0-39), row(0-29);
	// return: a boolean(true or false)
	//--------------------------------------------------------------
	bool checkneighbor(int x,int y,int curx,int cury);
	//--------------------------------------------------------------
	//addNewCell() was used for adding a new cell into the board.
	// It will ramdomly pick empty cell in the board and add a new cell into it.
	//--------------------------------------------------------------
	void addNewCell();
	//--------------------------------------------------------------
	//deleteCell() was used for deleting a cell from the board.
	// It will ramdomly pick a cell that is alive and delete the cell.
	//--------------------------------------------------------------
	void deleteCell();
	//--------------------------------------------------------------
	//updateMap() was used for updating all the elements from the Life array to the Map array.
	//--------------------------------------------------------------
	void updateMap();
	//--------------------------------------------------------------
	//updatePosition() was used for updating the cells position. When the cell has any neighbors, it will change direction.
	// When there is no cell that is alive on the next position then it will update the cell position.
	// When the cell hit the border, then it will change direction.
	//--------------------------------------------------------------
	void updatePosition();
	//--------------------------------------------------------------
	//updateLife() was used when current cell has neighbors it will set the number of neighors in numItems
	//--------------------------------------------------------------
	void updateLife();
	//--------------------------------------------------------------
	//updateColor() was used to update the color of each cell.  
	// The equation for the first range is:  first color - (diff between first and second color)/steps*(counter)
	//				second range is: second color - (diff between second and third color)/steps*(counter-steps)
	//--------------------------------------------------------------
	void updateColor();
	//--------------------------------------------------------------
	//updateNumOfCircle() was used for calculating the number of cells in the board. 
	// It stores the number in the variable called NumOfALiveCircle.
	//--------------------------------------------------------------
	void updateNumOfCircle();
	//--------------------------------------------------------------
	//CalcNumOfCircle() was used for calculating the number of cells in the board. 
	// Return: an integer of the number of cell in the board
	//--------------------------------------------------------------
	int CalcNumOfCircle();
	//--------------------------------------------------------------
	// parseOSCMsg() was used for decoding the different OSC messages and determine what is the appropriate actions.
	// There is two type of osc interface they are:
	//     0 - oscemote 
	//     1 - touchOSC
	//--------------------------------------------------------------
	void parseOSCMsg();
	//--------------------------------------------------------------
	// setupGui() was used for setting the gui interface. 
	//--------------------------------------------------------------
	void setupGui();
	//--------------------------------------------------------------
	//getCircularColor() was used for calculating the color from the color point you get from the color wheel
	// parameter: float angle (from 0 to 360); float radius(0-1) ; scale (0-1)
	// return: ofColor
	//--------------------------------------------------------------
	ofColor getCircularColor( float angle, float radius, float scale );
	//--------------------------------------------------------------
	// setup() runs at the start of the program. It initialize the variables such as the background color, framerate, osc receiver, 
	// osc sender, the cells column and row, and then it will add 100 cell into the board.
	// Also for touchosc, it will send the initial settings to your iphone/ipod/ipod
	// ShowMsg and fullscreen are set to false. Framerate and deadspeed is set to 5. The hit rate is set to 50.
	//--------------------------------------------------------------
	void setup();	
	//--------------------------------------------------------------
	//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
	//--------------------------------------------------------------
	void update();
	//--------------------------------------------------------------
	// draw() was used to draw all the things on the screen.
	// It will show the 40 circles horizotally and 30 circles vertically, and the string messages.
	// Each circle will change its color depends on which stage they are on.
	//--------------------------------------------------------------
	void draw();
	
	//for keyboard and mouse
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	//public variables
	Cells Life[windowcol+1][windowrow+1];
	Cells map[windowcol+1][windowrow+1];
	int frames; //frame rate
	int br,bg,bb; //background
	float myColors[4]; //background color
	float sColor1[4];
	float sColor2[4];
	float sColor3[4];
	float sColor4[4];
	float sColor5[4];
	
	float sliderColor1[4];
	float sliderColor2[4];
	float sliderColor3[4];
	float sliderColor4[4];
	float sliderColor5[4];
	float psliderColor1[4];
	float psliderColor2[4];
	float psliderColor3[4];
	float psliderColor4[4];
	float psliderColor5[4];
	
	float pwColor[4];
	float wColor[4];
	
	int aliveSlider;
	int NumOfALiveCircle;//number of circle
	int numberOfCell;
	int stage1;
	int stage2;
	int stage3;
	int stage4;
	bool flag;//show the ShowMsg
	bool showGui;
	bool enable1;
	bool enable2;
	bool enable3;
	bool enable4;
	bool enable5;
	int steps;
	
private:
	ofxOscReceiver receiver;
	ofxOscSender sender;
	};

#endif
