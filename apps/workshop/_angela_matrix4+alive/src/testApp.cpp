/* testApp.cpp
 * Created by Angela Chim
 * Summary: This program is similar to the Game of Life. When the cell collides with any neighbors around it, it will
 * change direction. Everytime it hit with another cell it will change its color. it will becomes darker and when it 
 * becomes full the cell will die. If the two cells has the same color and hit together it will keep track of how 
 * many times it hit. When the cell hits at a certain number, a new cell will came alive. There is 3 different colors for 
 * the cell. This program will randomly generate the color for the cells.
 * Created: December 2010 
 */

#include "testApp.h"

//--------------------------------------------------------------
// changedirection() was used for the cell to change direction and it will subtract that cell deadspeed.
// The parameter: contain the x and y position of the 2d matrix. x is in the range between 0 to 39.  
//					y is in the range between 0 to 29.
//--------------------------------------------------------------
void testApp::changedirection(int x,int y){
    Life[x][y].dx*=-1;
	Life[x][y].dy*=-1;
	Life[x][y].addCrashes(Life[x][y].cellcolor);
}
//--------------------------------------------------------------
// The checkneighbor function will return true if there is any neighbor. If the neighbor goes to the same spot with 
// the current cell and if they had the same color and the counter is less then pcounter then increment the counter by one 
// or else it will add a new cell into the board. 
// Also, it will check if there is a neighbor wants to go to the current cell position and if they had the 
// same color and the counter is less then pcounter then increment the counter by one or else it will
// add a new cell into the board.
//
// The parameter: x is the column position; y is the row position of the neighbor;
//					curx is the column position; cury is the row position of the current cell;
//					column(0-39), row(0-29);
// return: a boolean(true or false)
//--------------------------------------------------------------
bool testApp::checkneighbor(int x,int y,int curx,int cury){ 
	//if the neighbor position is out of range then return false
	if(x<0 ||x >windowcol-1 ||y<0 ||y>windowrow-1) return false;
	//if both cell is alive 
	if (Life[x][y].alive && Life[curx][cury].alive)
	{ 
		//if the neighbor goes to the same spot with the current cell
		if( map[x][y].getnextx()==map[curx][cury].getnextx() && map[x][y].getnexty()==map[curx][cury].getnexty()){
			//if both cell are the same color
			if(map[x][y].cellcolor==map[curx][cury].cellcolor){
				//if the current cell is less than pcounter then add one 
				if(map[x][y].counter<pcounter)
					Life[x][y].counter+=1;
				//else add a new cell
				else
				{	
					int a,b;
					a=ofRandom(0,windowcol);
					b=ofRandom(0,windowrow);
					Life[a][b].alive=true;
					Life[a][b].setCells(a,b);
					Life[x][y].counter=0;
					map[x][y].counter=0;
				}
			}
			return true;
		}
		//if there is a neighbor wants to go to the current cell position
		if(map[x][y].getnextx()==map[curx][cury].col&&map[x][y].getnexty()==map[curx][cury].row){
			//if both cell has the same color
			if(map[x][y].cellcolor==map[curx][cury].cellcolor){
				//if counter is less the pcounter, then counter add itelf by one
				if(map[x][y].counter<pcounter)
					Life[x][y].counter+=1;
				//or else add a new cell
				else
				{	
					int a,b;
					a=ofRandom(0,windowcol);
					b=ofRandom(0,windowrow);
					Life[a][b].alive=true;
					Life[a][b].setCells(a,b);
					Life[x][y].counter=0;
					map[x][y].counter=0;
				}
			}
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
//updatePosition() was used for updating the cells position. When the cell has any neighbors, it will change direction.
// When there is no cell that is alive on the next position then it will update the cell position. When the cell hit the border
// then it will change direction.
//--------------------------------------------------------------
void testApp::updatePosition(){
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			map[i][j].col=Life[i][j].col;
			map[i][j].row=Life[i][j].row;
			map[i][j].alive=Life[i][j].alive;
			map[i][j].dx=Life[i][j].dx;
			map[i][j].dy=Life[i][j].dy;
			map[i][j].nextx=Life[i][j].nextx;
			map[i][j].nexty=Life[i][j].nexty;
			map[i][j].numItems=Life[i][j].numItems;
			map[i][j].counter=Life[i][j].counter;
			Life[i][j].dspeed=deadspeed;
			map[i][j].dspeed=Life[i][j].dspeed;
		}
	}
	
	int tempx,tempy;
	int tr,tg,tb;
	int NumOfALiveCircle=0;
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			//if the cell has any neighbors then change direction 
			if(map[x][y].numItems>0){
				changedirection(x,y);
			}
			//the temp position is next position of the current cell
			tempx=map[x][y].col+map[x][y].dx;
			tempy=map[x][y].row+map[x][y].dy;
			//if the current cell is alive
			if(	map[x][y].alive){
				NumOfALiveCircle++;
				//if the next position is in range
				if(tempx<windowcol && tempy<windowrow&&tempx>=0 &&tempy>=0){
					//change the position if the current cell is alive and if the next position dont have neighbour
					if(Life[tempx][tempy].alive==false){
					Life[tempx][tempy].alive= true;
					Life[x][y].alive=false;
					tr=Life[tempx][tempy].red;
					tg=Life[tempx][tempy].green;
					tb=Life[tempx][tempy].blue;
					Life[tempx][tempy].dx=map[x][y].dx;
					Life[tempx][tempy].dy=map[x][y].dy;
					Life[tempx][tempy].red=Life[x][y].red;
					Life[tempx][tempy].green=Life[x][y].green;
					Life[tempx][tempy].blue=Life[x][y].blue;
					Life[tempx][tempy].cellcolor=map[x][y].cellcolor;
					Life[tempx][tempy].counter=map[x][y].counter;
					Life[x][y].red=tr;
					Life[x][y].green=tg;
					Life[x][y].blue=tb;
					
					}
				}
				//when they hit the borders, change direction
				else{
					if(tempx<0 || tempx> windowcol-1){
						Life[x][y].dx*=-1;
						//Life[x][y].addCrashes(Life[x][y].cellcolor);
					}
					if( tempy<0 || tempy>windowrow-1){
						Life[x][y].dy*=-1;
						//Life[x][y].addCrashes(Life[x][y].cellcolor);
					}
				}
			}
		}
	}
}
//--------------------------------------------------------------
//updateLife() was used when current cell has neighbors it will set the number of neighors in numItems
//--------------------------------------------------------------
void testApp::updateLife(){
	int count;
	int tempx,tempy;
	int tr,tg,tb;
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			count=0;

			//check if the neighbor 
			if(checkneighbor(i-2,j-2,i,j)) {
				count++;
			}
			if(checkneighbor(i-1,j-2,i,j)) {
				count++;
			}
			if(checkneighbor(i,j-2,i,j)) {
				count++;
			}
			if(checkneighbor(i+1,j-2,i,j)) {
				count++;
			}
			if(checkneighbor(i+2,j-2,i,j)) {
				count++;
			}
			if(checkneighbor(i-2,j-1,i,j)) {
				count++;
			}		
			if(checkneighbor(i+2,j-1,i,j)) {
				count++;
			}	
			if(checkneighbor(i-2,j,i,j)) {
				count++;
			}	
			if(checkneighbor(i+2,j,i,j)) {
				count++;
			}
			if(checkneighbor(i-2,j+1,i,j)) {
				count++;
			}	
			if(checkneighbor(i+2,j+1,i,j)) {
				count++;
			}
			if(checkneighbor(i-2,j+2,i,j)) {
				count++;
			}
			if(checkneighbor(i-1,j+2,i,j)) {
				count++;
			}
			if(checkneighbor(i,j+2,i,j)) {
				count++;
			}
			if(checkneighbor(i+1,j+2,i,j)) {
				count++;
			}
			if(checkneighbor(i+2,j+2,i,j)) {
				count++;
			}
			
			//check if the neighbor is alive
			if(checkneighbor(i-1,j-1,i,j)) count++;
			if(checkneighbor(i,j-1,i,j)) count++;
			if(checkneighbor(i+1,j-1,i,j)) count++;
			
			if(checkneighbor(i-1,j,i,j)) count++;
			if(checkneighbor(i+1,j,i,j)) count++;
			
			if(checkneighbor(i-1,j+1,i,j)) count++;
			if(checkneighbor(i,j+1,i,j)) count++;
			if(checkneighbor(i+1,j+1,i,j)) count++;
			
			int x=i;
			int y=j;
			if (count>0)
				Life[i][j].numItems=count;
		}
	}
}
//--------------------------------------------------------------
//updateNumOfCircle() was used for calculating the number of cells in the board. It stores the number in the variable 
//  called NumOfALiveCircle.
//--------------------------------------------------------------
void testApp::updateNumOfCircle(){
	NumOfALiveCircle=0;
	for(int i=0;i<windowcol;i++){
		for(int j=0;j<windowrow;j++){
			if( Life[i][j].alive==true){
				NumOfALiveCircle++;
			}
		}
	}
}


//--------------------------------------------------------------
// setup() runs at the start of the program. It initialize the variables such as the background color, framerate, osc receiver, 
// osc sender, the cells column and row, and then it will add 100 cell into the board.
// Also for touchosc, it will send the initial settings to your iphone/ipod/ipod
// ShowMsg and fullscreen are set to false. Framerate and deadspeed is set to 5. The hit rate is set to 50.
//--------------------------------------------------------------

void testApp::setup(){
	//ofBackground(100,100,100);
	ofBackground(0,0,0);
	frames=5;
	mode=1;
	pcounter=50;
	deadspeed=5;
	br=0;
	bg=0;
	bb=0;
	myColors[0]=br/255;
	myColors[1]=bg/255;
	myColors[2]=bb/255;
	flag=false;
	
	//setting up the receive and send ports
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);
	
	//set the cell col and row
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			Life[i][j].setCells(i,j);
		}
	}
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			map[i][j].setCells(i,j);
		}
	}
	
	//add 100 new cells
	int numberofcell=100;
	int a,b;
	for (int i=0; i<numberofcell;i++){
		a=ofRandom(0,windowcol);
		b=ofRandom(0,windowrow);
		Life[a][b].alive=true;
	}
	/*
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addTitle("GuiDraw");
	gui.addColorPicker("BG Color", myColors);
	
	gui.addToggle("blank", toggle1).setNewColumn(true);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	*/
	//toggle1=false;
	//gui.loadFromXML();
	//gui.show();
	
//send the initial message to iphone/ipod/ipad
	ofxOscMessage m1;
	m1.setAddress("/2/slider/4");//speed
	m1.addFloatArg(5);//set initial value to 5
	sender.sendMessage(m1);
	ofxOscMessage m2;
	m2.setAddress( "/2/slider/5" );//# of hits
	m2.addFloatArg(50);//set initial value to 50
	sender.sendMessage( m2 );
	ofxOscMessage m3;
	m3.setAddress( "/2/slider/6" );//deadspeed
	m3.addFloatArg(5);//set initial value to 5
	sender.sendMessage( m3 );
	ofxOscMessage m4;
	m4.setAddress( "/2/fullscreen" );
	m4.addIntArg(0);//toggle is off for fullscreen
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/2/ShowMsg" );
	m5.addIntArg(0);//toggle is off for show msg
	sender.sendMessage( m5 );
}
//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
//--------------------------------------------------------------
void testApp::update(){
	ofSetFrameRate(frames);
	ofBackground(br, bg, bb);
	br=myColors[0];
	bg=myColors[1];
	bb=myColors[2];
	//fill the array with each cell from the Life to map
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			map[i][j].col=Life[i][j].col;
			map[i][j].row=Life[i][j].row;
			map[i][j].alive=Life[i][j].alive;
			map[i][j].dx=Life[i][j].dx;
			map[i][j].dy=Life[i][j].dy;
			map[i][j].nextx=Life[i][j].nextx;
			map[i][j].nexty=Life[i][j].nexty;
			//set numItem to 0
			map[i][j].numItems=0;
			//set numItem to 0
			Life[i][j].numItems=0;
			//set the cell color
			map[i][j].cellcolor=Life[i][j].cellcolor;
			//set the hit number for each cell
			map[i][j].counter=Life[i][j].counter;
		}
	}
	//check how many numbers of neighbor it has
	updateLife();
	
//for oscemote	
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		//xy pad
		if ( m.getAddress() == "/tuio/2Dcur" )
		{	
			if(m.getArgAsString( 0 )=="set"){
				mouseX=m.getArgAsFloat( 2 )*ofGetWidth();
				mouseY=m.getArgAsFloat( 3 )*ofGetHeight();
				mousePressed (mouseX,mouseY,0);
			}
		}
		//background color for red
		else if(m.getAddress()=="/slider/1"){
			br=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[0]=m.getArgAsFloat(0);
		}
		//background color for green
		else if(m.getAddress()=="/slider/2"){
			bg=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[1]=m.getArgAsFloat(0);
		}
		//background color for blue
		else if(m.getAddress()=="/slider/3"){
			bb=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[2]=m.getArgAsFloat(0);
		}
		//framerate (max is 100) 
		else if(m.getAddress()=="/slider/4"){
			frames=m.getArgAsFloat(0)*100;
			if (frames==0)
				frames=1;
		}
		//# of hits (max is 200) 
		else if(m.getAddress()=="/slider/5"){
			pcounter=m.getArgAsFloat(0)*200;
			if (pcounter<5) {
				pcounter=1;
			}
		}
		//deadspeed (max is 80) 
		else if(m.getAddress()=="/slider/6"){
			deadspeed=m.getArgAsFloat(0)*80;
			if (deadspeed<5) {
				deadspeed=1;
			}
		}
		//increase framerate by 1
		else if (m.getAddress()=="/button/A1"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('+');
		}
		//decrease framerate by 1
		else if (m.getAddress()=="/button/B1"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('-');
		}
		//decrease the # of hit by 1
		else if (m.getAddress()=="/button/A2"){
			if(m.getArgAsInt32(0)==1)
			keyPressed(']');
		}
		//increase the # of hit by1
		else if (m.getAddress()=="/button/B2"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('[');
		}
		//this button to set all cell red to 255
		else if (m.getAddress()=="/button/C1"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('r');
		}
		//this button to set all cell green to 255
		else if (m.getAddress()=="/button/C2"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('g');
		}
		//this button to set all cell blue to 255
		else if (m.getAddress()=="/button/C3"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('b');
		}

//touchosc
		//if there is changes for the # of hits, change value (max is 200)
		else if(m.getAddress()=="/2/slider/5"){
			pcounter=m.getArgAsFloat(0)*200;
			if (pcounter<5) {
				pcounter=1;
			}
		}
		//if there is changes for the deadspeed, change value (max is 80) 
		else if(m.getAddress()=="/2/slider/6"){
			deadspeed=m.getArgAsFloat(0)*80;
			if (deadspeed<5) {
				deadspeed=1;
			}
		}
		//if there is changes make for the framerate, change value (max is 100)
		else if(m.getAddress()=="/2/slider/4"){
			frames=m.getArgAsFloat(0)*100;
			if (frames==0){
				frames=1;
			}
		}
		//this button to set all cell red to 255
		else if (m.getAddress()=="/2/C1"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('r');
		}
		//this button to set all cell green to 255
		else if (m.getAddress()=="/2/C2"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('g');
		}
		//this button to set all cell blue to 255
		else if (m.getAddress()=="/2/C3"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('b');
		}
		//this toggle is for the fullscreen,  1 is to show and 0 is not show
		else if (m.getAddress()=="/2/fullscreen"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed('t');
			if(m.getArgAsInt32(0)==1)
				ofHideCursor();
			else
				ofShowCursor();
				
			}
		}
		
		/*
		else if (m.getAddress()=="/2/E1"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed(' ');
			}
		}
		 */
		
		//this toggle is for the ShowMsg, 1 is to show and 0 is not show
		else if(m.getAddress()=="/2/ShowMsg"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed('f');
			}
		}
	}
	
	updateLife();//check if there is any neighbor
	updatePosition();//update the position 
	updateNumOfCircle();//update the number cell in the board
	
}
//--------------------------------------------------------------
// draw() was used to draw all the things on the screen.
// It will show the 40 circles horizotally and 30 circles vertically, and the string messages.
// Each circle will change its color depends on the deadspeed.
//--------------------------------------------------------------
void testApp::draw(){
	//glEnable(GL_TEXTURE_3D);
	//draw all the cells
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			ofSetColor(Life[i][j].red,Life[i][j].green,Life[i][j].blue);	
			Life[i][j].draw(ofGetWidth());
		}
	}
	//ShowMsg if flag is true
	if(flag==true){
		ofSetColor(255,255,255);
		string temp;
		temp="";
		temp+="Press '+' or '-' to increase/decrease the speed \n";
		temp+="Press '[' or ']' to increase/decrease the number of hit to make one alive  "+ ofToString(pcounter)+"\n";
		temp+="Press '1' change the mode to red \n";
		temp+="Press '2' change the mode to green\n";
		temp+="Press '3' change the mode to blue \n";
		temp+="Press 'r' to reset red\n";
		temp+="Press 'g' to reset green\n";
		temp+="Press 'b' to reset blue\n\n";
		temp+="Mode: "+ofToString(mode)+"\n";
		temp+="Speed: "+ofToString(frames)+"\n";
		temp+="Alive Circles: " +ofToString(NumOfALiveCircle)+"\n";
		temp+="Dead Speed: " +ofToString(deadspeed)+"\n";
		ofDrawBitmapString(temp, 10, 10);
	}
	//gui.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
		case '-':
			if(frames>1){
			frames--;
			}
			break;
		case '+':
			frames++;
			break;
		case 'r':
			for (int i=0; i<windowcol;i++){
				for(int j=0; j<windowrow;j++){	
					Life[i][j].red=255;
				}
			}
			break;
		case 'g':
			for (int i=0; i<windowcol;i++){
				for(int j=0; j<windowrow;j++){	
					Life[i][j].green=255;
				}
			}
			break;	
		case 'b':
			for (int i=0; i<windowcol;i++){
				for(int j=0; j<windowrow;j++){	
					Life[i][j].blue=255;
				}
			}
			break;
	/*		
		case '1':mode=1;//
			break;
		case '2':mode=2;
			break;
		case '3':mode=3;
			break;
	 */
		case '[':
			if(pcounter>200) break;
			else pcounter++;
			break;
		case ']':
			if (pcounter<5) {
				pcounter=5;
			
			break;
			}
			else pcounter--;
			break;
	//	case ' ':
	//		gui.toggleDraw();
	//		break;
		case '9':	
			if (deadspeed<5) {
				deadspeed=1;
			break;
			}
			else deadspeed--;
			 break;
		case '0':
			if(deadspeed>200) break;
			else deadspeed++;
			break;
		case 'f':
			flag=!flag;
			break;
		case 't':
			ofToggleFullscreen();
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
//mousePressed() is used for adding/deleting cells in the board. 
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	//convert pressed x position to (0-39)
	int convertx=float(x)/ofGetWidth()*float(windowcol);
	//convert pressed y position to (0-39)
	int converty=float(y)/ofGetHeight()*float(windowrow);
	//set the cell alive or dead at the position u pressed
	if(Life[convertx][converty].alive==false){
		Life[convertx][converty].alive=true;
		Life[convertx][converty].setCells(convertx,converty);
	}
	
	else
		Life[convertx][converty].alive=false;
	printf("mousepressed: %i, %i %i\n", x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

