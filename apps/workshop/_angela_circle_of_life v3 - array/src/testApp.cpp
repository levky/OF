/*
 *  testApp.cpp
 *  openFrameworks
 *  Circle of Life v3 - array 
 *
 *  Created by Angela Chim 
 *  Created: February 2011
 */

#include "testApp.h"
//--------------------------------------------------------------
// deleteCell() was used for delete a cell in the board
//--------------------------------------------------------------
void testApp::deleteCell(){
	int a,b;
	a=ofRandom(0,maxRingNum);
	b=ofRandom(0,checkstep[a]);
	bool emptyCell=true;
	while(emptyCell && !numOfCell==0 ){
		if (myCircle[a][b].alive==false){
			a=ofRandom(0,maxRingNum);
			b=ofRandom(0,checkstep[a]);
		}
		else{
			myCircle[a][b].alive=false;
			myCircle[a][b].setCell(a,b);
			emptyCell=false;
			numOfCell--;
		}
	}
}

//--------------------------------------------------------------
// resetneighbor() was used for reset all neighbor to zero
//--------------------------------------------------------------
void testApp::resetneighbor(){
	for(int i=0;i<maxRingNum;i++){
		for(int j=0;j<checkstep[i];j++){
			myCircle[i][j].neighbor=0;
		}
	}
}
//--------------------------------------------------------------
// addcounter() was used for keep track the number of hit to make one alive cell
// The parameter: i, and j is the index of myCircle
//--------------------------------------------------------------
void testApp::addcounter(int i,int j){
	//if the current cell is less than numOfHit then add one 
	if(myCircle[i][j].numOfHit<numOfHit){
		myCircle[i][j].numOfHit++;
	}
	//else add a new cell
	else
	{	
		if (NumOfALiveCircle<maxCircles){
			addNewCell();	
		}
	}
}
	
//--------------------------------------------------------------
// The checkneighbor() function will return true if there is any neighbor. 
// The parameter: ring is the first index of myCircle
//				  ny is the next step of myCircle, cury is the current step of myCircle. 
// return: a boolean(true or false)
//--------------------------------------------------------------
bool testApp::checkneighbor(int ring,int ny,int cury){ 
	//if the neighbor position is out of range then return false
	if(ny<0){
		ny= checkstep[ring];
	}
	else if (ny> checkstep[ring]){
		ny=0;
	}
	if (myCircle[ring][ny].alive && myCircle[ring][cury].alive)
	{ 	
		//if the neighbor goes to the same spot with the current cell
		if( myCircle[ring][cury].getNextStep()==myCircle[ring][ny].getNextStep()){
			
			return true;
		}
		//if there is a neighbor wants to go to the current cell position
		if( myCircle[ring][cury].getNextStep()==myCircle[ring][ny].steps){
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
//updateLife() was used when current cell has neighbors it will set the number of neighors for each cell
//--------------------------------------------------------------
void testApp::updateLife(){
	updatecount = 0;
	int count;
	for(int i=0;i<maxRingNum;i++){
		for(int j=0;j<checkstep[i];j++){
			count=0;
			updatecount++;
			if(checkneighbor(i,j+1,j)){
				count++;
			}
			if(checkneighbor(i,j-1,j)){
				count++;
			}
			myCircle[i][j].neighbor=count;
			if(myCircle[i][j].neighbor>0){
			   addCrashes(myCircle[i][j].mode,i,j);
			   addcounter(i,j);
			}
		}
	}
}

//--------------------------------------------------------------
// changedirection() was used for the cell to change direction. direction is 1 or 3
// The parameter: the index number of myCircle
//--------------------------------------------------------------	
void testApp::changedirection(int x,int y){

	if(myCircle[x][y].direction==1){
		myCircle[x][y].direction=3;
	}

	else if(myCircle[x][y].direction==3){
		myCircle[x][y].direction=1;
	}
}

//--------------------------------------------------------------
// changecondition() was used for change the condition. condition is 0 or 1
//--------------------------------------------------------------
void testApp::changecondition(int i,int j){
	if(myCircle[i][j].condition==0){
		myCircle[i][j].condition=1;
	}
	else{
		myCircle[i][j].condition=0;
	}
}
//--------------------------------------------------------------
// updateNumOfCircle() was used to update the number of cell is in the board and
//  the value stored in the variable called NumOfALiveCircle
//--------------------------------------------------------------
void testApp::updateNumOfCircle(){
	NumOfALiveCircle=0;
	for (int x=0; x<maxRingNum;x++){
		for(int y=0; y<checkstep[x];y++){
			if(myCircle[x][y].alive==true){
				NumOfALiveCircle++;
			}
		}
	}
}

 //--------------------------------------------------------------
 //updatePosition() was used for updating the cells position. When the cell has any neighbors, it will change direction.
 // example:	hit number is multiple of 5 and condition =0, then moved out one step of the ring
 //				hit number is multiple of 7 and condition =0, then move in one step of the ring
 //				When there is no cell that is alive on the next position then it will update the cell position.
 //--------------------------------------------------------------
void testApp::updatePosition(){
	
	//if the cell has any neighbors then change direction 
	for(int i=0;i<maxRingNum;i++){
		for(int j=0;j<checkstep[i];j++){
			if(myCircle[i][j].neighbor>0 && myCircle[i][j].alive){
				
				if(myCircle[i][j].condition==0){
					if(myCircle[i][j].numOfHit%5==0 && myCircle[i][j].numOfHit%7==0){
						changedirection(i,j);
					}
					else if(myCircle[i][j].numOfHit%5==0){
						myCircle[i][j].increasering();
					}
					else if(myCircle[i][j].numOfHit%7==0){
						myCircle[i][j].decreasering();
					}
					else{
						changedirection(i,j);
					}
				}
				
				else if(myCircle[i][j].condition==1){
					if(myCircle[i][j].numOfHit%5==0 && myCircle[i][j].numOfHit%7==0){
						changedirection(i,j);
					}
					else if(myCircle[i][j].numOfHit%5==0){
						myCircle[i][j].increasering();
					}
					else if(myCircle[i][j].numOfHit%7==0){
						myCircle[i][j].decreasering();
					}
					else{
						changedirection(i,j);
					}
				}
			}
		}
	}
	for(int i=0;i<maxRingNum;i++){
		for(int j=0;j<checkstep[i];j++){
			//if the next position is in range
			if(myCircle[i][j].alive && myCircle[i][j].ring>0 && myCircle[i][j].ring < maxRingNum ){
				//change the position if the next position is empty	
				if(tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].alive==false){
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].alive=true;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].setMaxRing(maxRingNum);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].setCell(myCircle[i][j].ring, myCircle[i][j].getNextStep());
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].direction=myCircle[i][j].direction;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].setColor(myCircle[i][j].color.r,myCircle[i][j].color.g,myCircle[i][j].color.b);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].condition=myCircle[i][j].condition;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].numOfHit=myCircle[i][j].numOfHit;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].getNextStep()].mode=myCircle[i][j].mode;

				}
				
				//position unchange cuz the next position is occupied
				else if (tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].alive==false){
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].alive=true;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setMaxRing(maxRingNum);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setCell(myCircle[i][j].ring, myCircle[i][j].steps);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].direction=myCircle[i][j].direction;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setColor(myCircle[i][j].color.r,myCircle[i][j].color.g,myCircle[i][j].color.b);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].condition=myCircle[i][j].condition;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].numOfHit=myCircle[i][j].numOfHit;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].mode=myCircle[i][j].mode;
					
				}
				else{
					cout<<"nowhere to go\n";
					numOfCell--;
				}
			}
			//out of the ring & alive
			else if (myCircle[i][j].alive){
				
				if(myCircle[i][j].ring<0){
					myCircle[i][j].increasering();
					myCircle[i][j].condition=0;
				}
				else if(myCircle[i][j].ring>maxRingNum){
					myCircle[i][j].decreasering();
					myCircle[i][j].condition=1;
				}
				
				if (tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].alive==false){
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].alive=true;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setMaxRing(maxRingNum);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setCell(myCircle[i][j].ring, myCircle[i][j].steps);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].direction=myCircle[i][j].direction;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].setColor(myCircle[i][j].color.r,myCircle[i][j].color.g,myCircle[i][j].color.b);
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].condition=myCircle[i][j].condition;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].numOfHit=myCircle[i][j].numOfHit;
					tempCircle[myCircle[i][j].ring][myCircle[i][j].steps].mode=myCircle[i][j].mode;
				}
				else{
					cout<<"out of the ring and nowhere to go\n";
					numOfCell--;
				}
			}
			
		}
	}
	for (int x=0; x<maxRingNum;x++){
		for(int y=0; y<checkstep[x];y++){
			myCircle[x][y].ring=tempCircle[x][y].ring;
			myCircle[x][y].steps=tempCircle[x][y].steps;
			myCircle[x][y].alive=tempCircle[x][y].alive;
			myCircle[x][y].maxRing=tempCircle[x][y].maxRing;
			myCircle[x][y].direction=tempCircle[x][y].direction;
			myCircle[x][y].condition=tempCircle[x][y].condition;
			myCircle[x][y].neighbor=tempCircle[x][y].neighbor;
			myCircle[x][y].numOfHit=tempCircle[x][y].numOfHit;
			myCircle[x][y].mode=tempCircle[x][y].mode;
			myCircle[x][y].color=tempCircle[x][y].color;
		}
	}
}

//--------------------------------------------------------------
// addCrashes() was used to update the color of the cell. Everytime it hit the color of the cell will 
// become darker. Until its color is full the cell will die.
// parameter: mode=0 for red, mode=1 for green, mode=2 for blue
//			x and y are the index number of myCircle 
//--------------------------------------------------------------
void testApp::addCrashes(int mode,int x,int y){
	//for red
	if (myCircle[x][y].mode==0){
		if(myCircle[x][y].color.b<10||myCircle[x][y].color.g<10){
			myCircle[x][y].alive=false;
			numOfCell--;
		}
		else{
			myCircle[x][y].color.b-=deadspeed;
			myCircle[x][y].color.g-=deadspeed;
		}
			
	}
	//for green
	if(myCircle[x][y].mode==1){
		if(myCircle[x][y].color.b<10||myCircle[x][y].color.r<10)
		{
			myCircle[x][y].alive=false;
			numOfCell--;
		}
		else{
			myCircle[x][y].color.b-=deadspeed;
			myCircle[x][y].color.r-=deadspeed;
		
		}
	}
	//for blue
	if(myCircle[x][y].mode==2){
		if(myCircle[x][y].color.r<10||myCircle[x][y].color.g<10)
		{
			myCircle[x][y].alive=false;
			numOfCell--;
		}
		else{
			myCircle[x][y].color.r-=deadspeed;
			myCircle[x][y].color.g-=deadspeed;
		}
	}
}
	
//--------------------------------------------------------------
//addNewCell() was used for adding a new cell into the board.
// It will ramdomly pick empty cell in the board and add a new cell into it.
//--------------------------------------------------------------
void testApp::addNewCell(){
	
	int a,b;
	a=ofRandom(0,maxRingNum);
	b=ofRandom(0,checkstep[a]);
	bool checkalive=true;
	while(checkalive && NumOfALiveCircle<maxCircles){
		if (myCircle[a][b].alive){
			a=ofRandom(0,maxRingNum);
			b=ofRandom(0,checkstep[a]);
		}
		else{
			myCircle[a][b].alive=true;
			myCircle[a][b].setCell(a, b);
			myCircle[a][b].setMaxRing(maxRingNum);
			myCircle[a][b].randomdirection();
			myCircle[a][b].condition=0;
			myCircle[a][b].numOfHit=0;
			myCircle[a][b].setColor(255,255,255);
			myCircle[a][b].mode=ofRandom(0,3);
			numOfCell++;
			checkalive=false;
		}
	}
}

//--------------------------------------------------------------
// parseOSCMsg() was used for decoding the different OSC messages and determine what is the appropriate actions.
// There is two type of osc interface they are:
//     0 - oscemote 
//     1 - touchOSC
//--------------------------------------------------------------
void testApp:: parseOSCMsg(){

	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		switch(OSCInterface){
			case 1:
				//if there is changes make for the framerate, change value (max is 100)
				if(m.getAddress()=="/2/slider/FrameRate"){
					frame=m.getArgAsFloat(0)*100;
					if (frame==0){
						frame=1;
					}
				}
				//if there is changes for the # of hits, change value (max is 200)
				else if(m.getAddress()=="/2/slider/NumOfHits"){
					numOfHit=m.getArgAsFloat(0)*200;
					if (numOfHit<5) {
						numOfHit=1;
					}
				}
				//if there is changes for the deadspeed, change value (max is 80) 
				else if(m.getAddress()=="/2/slider/DeadSpeed"){
					deadspeed=m.getArgAsFloat(0)*80;
					if (deadspeed<5) {
						deadspeed=1;
					}
				}
				//this toggle is for the fullscreen,  1 is to show and 0 is not show
				else if (m.getAddress()=="/2/FullScreen"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						keyPressed('t');
						//if(m.getArgAsInt32(0)==1)
						//	ofHideCursor();
						//else
						//	ofShowCursor();
					}
				}
				//this toggle is for the ShowMsg, 1 is to show and 0 is not show
				else if(m.getAddress()=="/2/ShowMsg"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						showMsg=!showMsg;
					}
				}
				//this button is for the AddCell
				else if(m.getAddress()=="/2/AddCell"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						keyPressed('a');
					}
				}

				break;
		}
	}
}

//--------------------------------------------------------------
void testApp::setup(){
	
	//initalize variable
	showMsg=true;
	showFrame=true;
	frame=12;
	deadspeed=10;
	numOfHit=10;
	numOfCell=0;
	grid=5;
	ofSetFrameRate(frame);
	
	//setting up the receive and send ports
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);
	
	//maxRingNum = sqrt((ofGetWidth()/2)*(ofGetWidth()/2)+(ofGetHeight()/2)*(ofGetHeight()/2))/ringSize;
	maxRingNum=numOfRings;
	NumOfALiveCircle=0;
	
	//create checkstep
	for(int i=0;i<maxRingNum;i++){
			   int tempringradius;
			   tempringradius=i*ringSize;
			   checkstep[i]= ceil(floor(2*PI*tempringradius)/(2 * circle_radius ));
	}
	checkstep[0]=1;
	
	//setup the cell for every index in the array
	for (int x=0; x<maxRingNum;x++){
		for(int y=0; y<maxSteps;y++){
			myCircle[x][y].setCell(x,y);
			tempCircle[x][y].setCell(x,y);
		}
	}

	//add 100 cell
	for(int i=0;i<100;i++){
		addNewCell();
	}
}

//--------------------------------------------------------------
// updateTemp() was used to update the temp circle that all circle is no alive
//--------------------------------------------------------------

void testApp::updateTemp(){
	for (int x=0; x<maxRingNum;x++){
		for(int y=0; y<checkstep[x];y++){
			tempCircle[x][y].alive=false;
		}
	}
}

//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
//--------------------------------------------------------------
void testApp::update(){

	updateTemp();
	if (useOSC){
		parseOSCMsg();
	}
	if(showFrame)
	ofSetFrameRate(frame);
	
	updateLife();
	updatePosition();
	resetneighbor();
	updateNumOfCircle();
	
}
//--------------------------------------------------------------
// draw() was used to draw all the things on the screen.
// It will show a circle grid and the string messages.
// Each cell will change its color when it get hit
//--------------------------------------------------------------
void testApp::draw() {
	ofBackground(0, 0, 0);

	float ang;
	for (int i=0; i<maxRingNum*ringSize;i=i+ringSize){
		ang=360./checkstep[i/ringSize];
		for(int j=0; j<checkstep[i/ringSize];j++){
		
			if(myCircle[i/ringSize][j].alive && i!=0)
				ofSetColor(myCircle[i/ringSize][j].color.r,myCircle[i/ringSize][j].color.g,myCircle[i/ringSize][j].color.b);
			
			else
				ofSetColor(grid, grid, grid);
			
			ofCircle(i*cos(j*ang*PI/180.)+ofGetWidth()/2,-i*sin(j*ang*PI/180.)+ofGetHeight()/2,circle_radius-2);
		}
	}
	
	if(showMsg){
		string temp="";
		ofSetColor(255, 255, 255);
		temp+="Number of Frame: "+ofToString(frame)+"\n";
		temp+="FrameRate: "+ofToString(ofGetFrameRate())+"\n";
		temp+="Deadspeed: "+ofToString(deadspeed)+"\n";
		temp+="Number of hit to make one alive: "+ofToString(numOfHit)+"\n";
		temp+="RingSize: "+ofToString(ringSize)+"\n";
		temp+="UpdateLife counter: "+ofToString(updatecount)+"\n";
		temp+="Number of circles: "+ofToString(NumOfALiveCircle)+"\n";
		ofDrawBitmapString(temp, 20, 20);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	switch (key) {
		case 't':
			ofToggleFullscreen();
			break;
		case '-':
			if(frame<1)
			{
				frame=1;
			}
			else{
				frame--;
			}
			break;
		case '=':
			frame++;
			break;
		case ']':
			if(grid>255){
				grid=255;
			}
			else{
				grid++;
			}
			break;
		case '[':
			if(grid<0)
			{
				grid=0;
			}
			else{
				grid--;
			}
			
			break;
		case 'a':
			addNewCell();
			break;
		case 'd':
			deleteCell();
			break;
		case '9':
			deadspeed--;
			break;
		case '0':
			deadspeed++;
			break;
		case 'o':
			numOfHit--;
			break;
		case 'p':
			numOfHit++;
			break;
		case 'f':
			showFrame=!showFrame;
			break;
		case 'g':
			showMsg=!showMsg;
			break;
		default:
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

