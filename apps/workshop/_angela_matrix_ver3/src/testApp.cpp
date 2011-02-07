/* testApp.cpp
 * Created by Angela Chim
 * Summary: This program is similar to the Game of Life. When the cell collides with any neighbors around it, it will
 * change direction. Everytime it hit with another cell it will change its colors, depend on which stage it is on. 
 * When the cell hits at a certain number, it will die and another cell become alive. 
 * Created: December 2010 
 * Modified on: Febuary 2011
 */

#include "testApp.h"

//--------------------------------------------------------------
//sColorIsEqualSliderColor() was used for updating the cell's color. It will use the slider color
// parameter: is the index number of the array
//--------------------------------------------------------------
void testApp ::sColorIsEqualSliderColor(int i){
	sColor1[i]=sliderColor1[i];
	sColor2[i]=sliderColor2[i];
	sColor3[i]=sliderColor3[i];
	sColor4[i]=sliderColor4[i];
	sColor5[i]=sliderColor5[i];
}
//--------------------------------------------------------------
//sliderColorIsEqualsColor() was used for updating all the slider color
// parameter: is the index number of the array
//--------------------------------------------------------------
void testApp:: sliderColorIsEqualsColor(int i){
	sliderColor1[i]=sColor1[i];
	sliderColor2[i]=sColor2[i];
	sliderColor3[i]=sColor3[i];
	sliderColor4[i]=sColor4[i];
	sliderColor5[i]=sColor5[i];
}

//--------------------------------------------------------------
// setStage() was used for setting the stage parameters, such as the direction of each stage, 
// the size of the stage, and the color range between the stage.
//--------------------------------------------------------------
void testApp::setStage(){
	//size of the step for the stage
	steps=10;
	//choose left=0 right=1 opp=2
	stage1= right;
	stage2= left;
	stage3= opp;
	stage4= opp;
	sColor1[0]=1;
	sColor2[0]=1;
	sColor2[1]=1;
	sColor3[1]=1;
	sColor4[1]=1;
	sColor4[2]=1;
	sColor5[2]=1;
	
	
	//send the initial message to iphone/ipod/ipad for ( touchOSC )
	ofxOscMessage m1;
	m1.setAddress("/2/slider/FrameRate");//speed
	m1.addFloatArg(5);//set initial value to 5
	sender.sendMessage(m1);
	ofxOscMessage m2;
	m2.setAddress( "/2/ShowGui" );
	m2.addIntArg(1);//toggle is off for fullscreen
	sender.sendMessage( m2 );
	ofxOscMessage m4;
	m4.setAddress( "/2/FullScreen" );
	m4.addIntArg(0);//toggle is off for fullscreen
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/2/ShowMsg" );
	m5.addIntArg(0);//toggle is off for show msg
	sender.sendMessage( m5 );
	ofxOscMessage m6;
	m6.setAddress( "/3/Steps" );
	m6.addIntArg(10);//toggle is off for show msg
	sender.sendMessage( m6 );
	ofxOscMessage m7;
	m7.setAddress( "/3/Hits" );
	m7.addIntArg(41);//toggle is off for show msg
	sender.sendMessage( m7 );
	
	
}
//--------------------------------------------------------------
//turnleft() was used for mapping the current position to the left position.
//	example: when the current position was pointing to the North, the next position will be NorthWest.
//--------------------------------------------------------------
void testApp::turnleft(int x,int y){
	//North
	if(Life[x][y].dx==0 && Life[x][y].dy==-1){
		Life[x][y].dx=-1;
		Life[x][y].dy=-1;
	}
	//NW
	else if(Life[x][y].dx==-1 && Life[x][y].dy==-1){
		Life[x][y].dx=-1;
		Life[x][y].dy=0;
	}
	//W
	else if(Life[x][y].dx==-1 && Life[x][y].dy==0){
		Life[x][y].dx=-1;
		Life[x][y].dy=1;
	}
	//SW
	else if(Life[x][y].dx=-1 && Life[x][y].dy==1){
		Life[x][y].dx=0;
		Life[x][y].dy=1;
	}
	//S
	else if(Life[x][y].dx==0 && Life[x][y].dy==1){
		Life[x][y].dx=1;
		Life[x][y].dy=1;
	}
	//SE
	else if(Life[x][y].dx==1 && Life[x][y].dy==1){
		Life[x][y].dx=1;
		Life[x][y].dy=0;
	}
	//E
	else if(Life[x][y].dx==1 && Life[x][y].dy==0){
		Life[x][y].dx=1;
		Life[x][y].dy=-1;
	}
	//NE
	else if(Life[x][y].dx==1 && Life[x][y].dy==-1){
		Life[x][y].dx=0;
		Life[x][y].dy=-1;
	}
	//if both equal zero
	else if(Life[x][y].dx==0 && Life[x][y].dy==0){
		Life[x][y].randomdirection();
		Life[x][y].randomdirection();
	}
}
//--------------------------------------------------------------
//turnright() was used for mapping the current position to the right position.
//	example: when the current position was pointing to the North, the next position will be NorthEast.
//--------------------------------------------------------------
void testApp::turnright(int x,int y){
	//N
	if(Life[x][y].dx==0 && Life[x][y].dy==-1){
		Life[x][y].dx=1;
		Life[x][y].dy=-1;
	}
	//NW
	else if(Life[x][y].dx==-1 && Life[x][y].dy==-1){
		Life[x][y].dx=0;
		Life[x][y].dy=-1;
	}
	//W
	else if(Life[x][y].dx==-1 && Life[x][y].dy==0){
		Life[x][y].dx=-1;
		Life[x][y].dy=-1;
	}
	//SW
	else if(Life[x][y].dx=-1 && Life[x][y].dy==1){
		Life[x][y].dx=-1;
		Life[x][y].dy=0;
	}
	//S
	else if(Life[x][y].dx==0 && Life[x][y].dy==1){
		Life[x][y].dx=-1;
		Life[x][y].dy=1;
	}
	//SE
	if(Life[x][y].dx==1 && Life[x][y].dy==1){
		Life[x][y].dx=0;
		Life[x][y].dy=1;
	}
	//E
	else if(Life[x][y].dx==1 && Life[x][y].dy==0){
		Life[x][y].dx=1;
		Life[x][y].dy=1;
	}
	//NE
	else if(Life[x][y].dx==1 && Life[x][y].dy==-1){
		Life[x][y].dx=1;
		Life[x][y].dy=0;
	}
	//if both equal zero
	else if(Life[x][y].dx==0 && Life[x][y].dy==0){
		Life[x][y].randomdirection();
		Life[x][y].randomdirection();
	}
}
//--------------------------------------------------------------
//turnopposite() was used for mapping the current position to the opposite position.
//	example: when the current position was pointing to the North, the next position will be South.
//--------------------------------------------------------------
void testApp::turnopposite(int x,int y){
	//turn opposite direction
    Life[x][y].dx*=-1;
	Life[x][y].dy*=-1;
	
	//if both equal zero
	if(Life[x][y].dx==0 && Life[x][y].dy==0){
		Life[x][y].randomdirection();
		Life[x][y].randomdirection();
	}
}
//--------------------------------------------------------------
// changedirection() was used for the cell to change direction and it will subtract that cell deadspeed.
// The parameter: contain the x and y position of the 2d matrix. x is in the range between 0 to 39.  
//					y is in the range between 0 to 29.
//--------------------------------------------------------------
void testApp::changedirection(int x,int y){	
	Life[x][y].counter+=1;
	if(Life[x][y].counter>0 && Life[x][y].counter<=steps){
		if(stage1==0) turnleft(x,y);
		else if(stage1==1) turnright(x,y);
		else if(stage1==2) turnopposite(x,y);
	}
	if(Life[x][y].counter>steps && Life[x][y].counter<=2*steps){
		if(stage2==0) turnleft(x,y);
		else if(stage2==1) turnright(x,y);
		else if(stage2==2) turnopposite(x,y);	
	}
	if(Life[x][y].counter>2*steps && Life[x][y].counter<=3*steps){
		if(stage4==0) turnleft(x,y);
		else if(stage3==1) turnright(x,y);
		else if(stage3==2) turnopposite(x,y);
	}
	if(Life[x][y].counter>3*steps ){
		if(stage4==0) turnleft(x,y);
		else if(stage4==1) turnright(x,y);
		else if(stage4==2) turnopposite(x,y);
	}
	
	if (Life[x][y].counter==aliveSlider){
		addNewCell();
	}
	
	//example: steps=5; if Life.counter>20  which is (21 and more ) it will die
	if (Life[x][y].counter>steps*4)
	{ 
		map[x][y].alive=false;
		Life[x][y].alive=false;
		Life[x][y].counter=0;
		map[x][y].counter=0;
	}
}
//--------------------------------------------------------------
// The checkneighbor() function will return true if there is any neighbor. 
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
			return true;
		}
		//if there is a neighbor wants to go to the current cell position
		if(map[x][y].getnextx()==map[curx][cury].col&&map[x][y].getnexty()==map[curx][cury].row){
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
//addNewCell() was used for adding a new cell into the board.
// It will ramdomly pick empty cell in the board and add a new cell into it.
//--------------------------------------------------------------
void testApp::addNewCell(){
	int a,b;
	a=ofRandom(0,windowcol);
	b=ofRandom(0,windowrow);
	if(debug==1){
	bool checkalive=true;
	while(checkalive && CalcNumOfCircle()<1200 ){
		if (Life[a][b].alive==true){
			a=ofRandom(0,windowcol);
			b=ofRandom(0,windowrow);
		}
		else{
			Life[a][b].alive=true;
			Life[a][b].setCells(a,b);
			Life[a][b].counter=0;
			checkalive=false;
		}
	}
	}
	if (debug==2){
	Life[a][b].alive=true;
	Life[a][b].setCells(a,b);
	Life[a][b].counter=0;
	}
}
//--------------------------------------------------------------
//deleteCell() was used for deleting a cell from the board.
// It will ramdomly pick a cell that is alive and delete the cell.
//--------------------------------------------------------------
void testApp::deleteCell(){
	int a,b;
	a=ofRandom(0,windowcol);
	b=ofRandom(0,windowrow);
	bool emptyCell=true;
	while(emptyCell && !CalcNumOfCircle()==0 ){
		if (Life[a][b].alive==false){
			a=ofRandom(0,windowcol);
			b=ofRandom(0,windowrow);
		}
		else{
			Life[a][b].alive=false;
			Life[a][b].setCells(a,b);
			Life[a][b].counter=0;
			emptyCell=false;
		}
	}
}
//--------------------------------------------------------------
//updateMap() was used for updating all the elements from the Life array to the Map array.
//--------------------------------------------------------------
void testApp::updateMap(){
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			map[x][y].col=Life[x][y].col;
			map[x][y].row=Life[x][y].row;
			map[x][y].alive=Life[x][y].alive;
			map[x][y].dx=Life[x][y].dx;
			map[x][y].dy=Life[x][y].dy;
			map[x][y].nextx=Life[x][y].nextx;
			map[x][y].nexty=Life[x][y].nexty;
			map[x][y].numItems=Life[x][y].numItems;
			map[x][y].counter=Life[x][y].counter;
			map[x][y].red=Life[x][y].red;
			map[x][y].green=Life[x][y].green;
			map[x][y].blue=Life[x][y].blue;
		}
	}
}
//--------------------------------------------------------------
//updatePosition() was used for updating the cells position. When the cell has any neighbors, it will change direction.
// When there is no cell that is alive on the next position then it will update the cell position.
// When the cell hit the border, then it will change direction.
//--------------------------------------------------------------
void testApp::updatePosition(){
	updateMap();
	
	int tempx,tempy;
	int tr,tg,tb;
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
				
				//if the next position is in range
				if(tempx<windowcol && tempy<windowrow&&tempx>=0 &&tempy>=0){
					//change the position if the current cell is alive and if the next position is empty
					if(Life[tempx][tempy].alive==false){
						Life[tempx][tempy].alive= true;
						Life[x][y].alive=false;
						tr=Life[tempx][tempy].red;
						tg=Life[tempx][tempy].green;
						tb=Life[tempx][tempy].blue;
						Life[tempx][tempy].dx=map[x][y].dx;
						Life[tempx][tempy].dy=map[x][y].dy;
						Life[tempx][tempy].red=map[x][y].red;
						Life[tempx][tempy].green=map[x][y].green;
						Life[tempx][tempy].blue=map[x][y].blue;
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
					}
					if( tempy<0 || tempy>windowrow-1){
						Life[x][y].dy*=-1;
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
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			count=0;
			//check if there is any neighbor
			if(checkneighbor(x-2,y-2,x,y)) {
				count++;
			}
			if(checkneighbor(x-1,y-2,x,y)) {
				count++;
			}
			if(checkneighbor(x,y-2,x,y)) {
				count++;
			}
			if(checkneighbor(x+1,y-2,x,y)) {
				count++;
			}
			if(checkneighbor(x+2,y-2,x,y)) {
				count++;
			}
			if(checkneighbor(x-2,y-1,x,y)) {
				count++;
			}		
			if(checkneighbor(x+2,y-1,x,y)) {
				count++;
			}	
			if(checkneighbor(x-2,y,x,y)) {
				count++;
			}	
			if(checkneighbor(x+2,y,x,y)) {
				count++;
			}
			if(checkneighbor(x-2,y+1,x,y)) {
				count++;
			}	
			if(checkneighbor(x+2,y+1,x,y)) {
				count++;
			}
			if(checkneighbor(x-2,y+2,x,y)) {
				count++;
			}
			if(checkneighbor(x-1,y+2,x,y)) {
				count++;
			}
			if(checkneighbor(x,y+2,x,y)) {
				count++;
			}
			if(checkneighbor(x+1,y+2,x,y)) {
				count++;
			}
			if(checkneighbor(x+2,y+2,x,y)) {
				count++;
			}
			
			//check if there is any neighbor
			if(checkneighbor(x-1,y-1,x,y)) count++;
			if(checkneighbor(x,y-1,x,y)) count++;
			if(checkneighbor(x+1,y-1,x,y)) count++;
			
			if(checkneighbor(x-1,y,x,y)) count++;
			if(checkneighbor(x+1,y,x,y)) count++;
			
			if(checkneighbor(x-1,y+1,x,y)) count++;
			if(checkneighbor(x,y+1,x,y)) count++;
			if(checkneighbor(x+1,y+1,x,y)) count++;

			if (count>0)
				Life[x][y].numItems=count;
		}
	}
}
//--------------------------------------------------------------
//updateColor() was used to update the color of each cell.  
// The equation for the first range is:  first color - (diff between first and second color)/steps*(counter)
//				second range is: second color - (diff between second and third color)/steps*(counter-steps)
//--------------------------------------------------------------
void testApp::updateColor(){
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			//counter 0-4
			if(Life[x][y].counter>=0 && Life[x][y].counter<steps){
				Life[x][y].red=(sColor1[0]*255-(sColor1[0]-sColor2[0])/steps*255*(Life[x][y].counter));
				Life[x][y].green=(sColor1[1]*255-(sColor1[1]-sColor2[1])/steps*255*(Life[x][y].counter));
				Life[x][y].blue=(sColor1[2]*255-(sColor1[2]-sColor2[2])/steps*255*(Life[x][y].counter));
			}
			//counter 5-9
			if(Life[x][y].counter>=steps && Life[x][y].counter<2*steps){	
				Life[x][y].red=(sColor2[0]*255-(sColor2[0]-sColor3[0])/steps*255*(Life[x][y].counter-steps));
				Life[x][y].green=(sColor2[1]*255-(sColor2[1]-sColor3[1])/steps*255*(Life[x][y].counter-steps));
				Life[x][y].blue=(sColor2[2]*255-(sColor2[2]-sColor3[2])/steps*255*(Life[x][y].counter-steps));
			}
			//counter 10-14
			if(Life[x][y].counter>=2*steps && Life[x][y].counter<3*steps){
				Life[x][y].red=(sColor3[0]*255-(sColor3[0]-sColor4[0])/steps*255*(Life[x][y].counter-steps*2));
				Life[x][y].green=(sColor3[1]*255-(sColor3[1]-sColor4[1])/steps*255*(Life[x][y].counter-steps*2));
				Life[x][y].blue=(sColor3[2]*255-(sColor3[2]-sColor4[2])/steps*255*(Life[x][y].counter-steps*2));
				
			}
			//counter 15 and more
			if(Life[x][y].counter>=3*steps ){
				Life[x][y].red=(sColor4[0]*255-(sColor4[0]-sColor5[0])/steps*255*(Life[x][y].counter-steps*3));
				Life[x][y].green=(sColor4[1]*255-(sColor4[1]-sColor5[1])/steps*255*(Life[x][y].counter-steps*3));
				Life[x][y].blue=(sColor4[2]*255-(sColor4[2]-sColor5[2])/steps*255*(Life[x][y].counter-steps*3));
			}
		}
	}
}
//--------------------------------------------------------------
//updateNumOfCircle() was used for calculating the number of cells in the board. 
// It stores the number in the variable called NumOfALiveCircle.
//--------------------------------------------------------------
void testApp::updateNumOfCircle(){
	NumOfALiveCircle=0;
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			if( Life[x][y].alive==true){
				NumOfALiveCircle++;
			}
		}
	}
}
//--------------------------------------------------------------
//CalcNumOfCircle() was used for calculating the number of cells in the board. 
// Return: an integer of the number of cell in the board
//--------------------------------------------------------------
int testApp::CalcNumOfCircle(){
	int temp=0;
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			if( Life[x][y].alive==true){
			temp++;
			}
		}
	}
	   return temp;
}
//--------------------------------------------------------------
// parseOSCMsg() was used for decoding the different OSC messages and determine what is the appropriate actions.
// There is two type of osc interface they are:
//     0 - oscemote 
//     1 - touchOSC
//--------------------------------------------------------------
void testApp::parseOSCMsg(){
	//for oscemote	
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		switch(OSCInterface){
			case 0: 
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
					myColors[0]=m.getArgAsFloat(0);
				}
				//background color for green
				else if(m.getAddress()=="/slider/2"){
					myColors[1]=m.getArgAsFloat(0);
				}
				//background color for blue
				else if(m.getAddress()=="/slider/3"){
					myColors[2]=m.getArgAsFloat(0);
				}
				//framerate (max is 100) 
				else if(m.getAddress()=="/slider/4"){
					frames=m.getArgAsFloat(0)*100;
					if (frames==0)
						frames=1;
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
				break;
			case 1:
				//touchOSC
				//if there is changes make for the framerate, change value (max is 100)
				if(m.getAddress()=="/2/slider/FrameRate"){
					frames=m.getArgAsFloat(0)*100;
					if (frames==0){
						frames=1;
					}
				}
				//this toggle is for the fullscreen,  1 is to show and 0 is not show
				else if (m.getAddress()=="/2/FullScreen"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						keyPressed('t');
						if(m.getArgAsInt32(0)==1)
							ofHideCursor();
						else
							ofShowCursor();
					}
				}
				//this toggle is for the ShowMsg, 1 is to show and 0 is not show
				else if(m.getAddress()=="/2/ShowMsg"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						keyPressed('f');
					}
				}
				//this toggle is for showing the gui, 1 is to show gui and 0 is not show
				else if(m.getAddress()=="/2/ShowGui"){
					if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
						keyPressed(' ');
					}
				}
				//this is the xy pad to change the color
				else if(m.getAddress()=="/3/xy1"){
					float x=m.getArgAsFloat( 0);
					float y=m.getArgAsFloat( 1 );
					
					float px = x - .5;						// point x from center.
					float py = y - .5;						// point x from center.
					float pl = sqrt( px * px + py * py );	// point length from center.
					float pa = atan2( px, py );				// point angle around center.
					
					pa =(pa/(2*PI)*360-180)*-1;
					pl /= 0.5;//radius
					
					ofColor color;
					color=getCircularColor(pa,pl,1);
					ofLog(OF_LOG_ERROR,"pa="+ ofToString(pa)+" pl= "+ofToString(pl));
				
					if(enable1){
						sColor1[0]=color.r/255;
						sColor1[1]=color.g/255;
						sColor1[2]=color.b/255;
					}
					if(enable2){
						sColor2[0]=color.r/255;
						sColor2[1]=color.g/255;
						sColor2[2]=color.b/255;
					
					}
					if(enable3){
						sColor3[0]=color.r/255;
						sColor3[1]=color.g/255;
						sColor3[2]=color.b/255;
					
					}
					if(enable4){
						sColor4[0]=color.r/255;
						sColor4[1]=color.g/255;
						sColor4[2]=color.b/255;
				
					}
					if(enable5){
						sColor5[0]=color.r/255;
						sColor5[1]=color.g/255;
						sColor5[2]=color.b/255;
		
					}
					sliderColorIsEqualsColor(0);
					sliderColorIsEqualsColor(1);
					sliderColorIsEqualsColor(2);
									
				}
				//enable and disable toggles
				else if(m.getAddress()=="/3/multitoggle2/1/1"){
					if(m.getArgAsInt32(0)==1){
						enable1=true;
					}
					if(m.getArgAsInt32(0)==0){
						enable1=false;
					}
				}
				else if(m.getAddress()=="/3/multitoggle2/1/2"){
					if(m.getArgAsInt32(0)==1){
						enable2=true;
					}
					if(m.getArgAsInt32(0)==0){
						enable2=false;
					}
				}
				else if(m.getAddress()=="/3/multitoggle2/1/3"){
					if(m.getArgAsInt32(0)==1){
						enable3=true;
					}
					if(m.getArgAsInt32(0)==0){
						enable3=false;
					}
				}
				else if(m.getAddress()=="/3/multitoggle2/1/4"){
					if(m.getArgAsInt32(0)==1){
						enable4=true;
					}
					if(m.getArgAsInt32(0)==0){
						enable4=false;
					}
				}
				else if(m.getAddress()=="/3/multitoggle2/1/5"){
					if(m.getArgAsInt32(0)==1){
						enable5=true;
					}
					if(m.getArgAsInt32(0)==0){
						enable5=false;
					}
				}
				//slider for stage1
				else if (m.getAddress()=="/3/Stage1"){
					if(m.getArgAsFloat(0)<0.5){
						stage1=left;
					}
					else if (m.getArgAsFloat(0)<1.5){
						stage1=right;
					}
					else {
						stage1=opp;
					}
				}
				//slider for stage2
				else if (m.getAddress()=="/3/Stage2"){
					if(m.getArgAsFloat(0)<0.5){
						stage2=left;
					}
					else if (m.getArgAsFloat(0)<1.5){
						stage2=right;
					}
					else {
						stage2=opp;
					}
				}
				//slider for stage3
				else if (m.getAddress()=="/3/Stage3"){
					if(m.getArgAsFloat(0)<0.5){
						stage3=left;
					}
					else if (m.getArgAsFloat(0)<1.5){
						stage3=right;
					}
					else {
						stage3=opp;
					}
				}
				//slider for stage4
				else if (m.getAddress()=="/3/Stage4"){
					if(m.getArgAsFloat(0)<0.5){
						stage4=left;
					}
					else if (m.getArgAsFloat(0)<1.5){
						stage4=right;
					}
					else {
						stage4=opp;
					}
				}
				//slider for the size of each steps
				else if (m.getAddress()=="/3/Steps"){
					steps=m.getArgAsInt32(0);
				}
				//Number of Hits to make one alive
				else if (m.getAddress()=="/3/Hits"){
					aliveSlider=m.getArgAsInt32(0);
				}
				break;
		}
	}
}

//--------------------------------------------------------------
// setupGui() was used for setting the gui interface. 
//--------------------------------------------------------------
void testApp::setupGui(){
	wColor[0]=1;
	
	gui.addSlider("Stage1",stage1,0,2);
	gui.addSlider("Stage2",stage2,0,2);
	gui.addSlider("Stage3",stage3,0,2);
	gui.addSlider("Stage4",stage4,0,2);
	gui.addColorPicker("Colors", myColors);
	gui.addSlider("Size of each Stage",steps,1,10);
	gui.addSlider("Add a Cell when it hit", aliveSlider,1,42);
	
	for (int i=0;i<4;i++){
		sliderColorIsEqualsColor(i);
	}

	
	gui.addColorPicker("first", sliderColor1).setNewColumn(true);
	gui.addColorPicker("Stage1-Stage2", sliderColor2);
	gui.addColorPicker("Stage2-Stage3", sliderColor3);
	gui.addColorPicker("Stage3-Stage4", sliderColor4);
	gui.addColorPicker("end", sliderColor5);
	gui.addToggle("enable1",enable1).setNewColumn(true);
	gui.addToggle("enable2",enable2);
	gui.addToggle("enable3",enable3);
	gui.addToggle("enable4",enable4);
	gui.addToggle("enable5",enable5);
	//gui.addPage("Add a new page");

	gui.addColorPicker2d("1",wColor).setNewColumn(true);

	gui.show();
}

//--------------------------------------------------------------
// setup() runs at the start of the program. It initialize the variables such as the background color, framerate, osc receiver, 
// osc sender, the cells column and row, and then it will add 100 cell into the board.
// Also for touchosc, it will send the initial settings to your iphone/ipod/ipod
// ShowMsg and fullscreen are set to false. Framerate and deadspeed is set to 5. The hit rate is set to 50.
//--------------------------------------------------------------
void testApp::setup(){
	enable1=enable2=enable3=enable4=enable5=false;
	
	frames=5;
	aliveSlider=41;
	//background colors
	myColors[0]=0;
	myColors[1]=0;
	myColors[2]=0;
	
	//flags for Message and gui
	flag=false;
	showGui=true;
	
	//setting up the receive and send ports
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);
	
	//set the cell col and row
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){

			Life[x][y].setCells(x,y);
		}
	}
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			map[x][y].setCells(x,y);
		}
	}
	
	//add 100 new cells
	numberOfCell=100;
	for (int i=0; i<numberOfCell;i++){
		addNewCell();
	}
	
	//setting for each stage and their color range
	setStage();
	
	//setting of gui
	setupGui();
	
}

	
//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
//--------------------------------------------------------------
void testApp::update(){

	ofSetFrameRate(frames);
	ofBackground(myColors[0]*255, myColors[1]*255, myColors[2]*255);
	
	//update the map values from the Life array
	updateMap();
	
	//set numItem to 0 for each cell
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			map[x][y].numItems=0;
			Life[x][y].numItems=0;
		}
	}
	
	if(useOSC) parseOSCMsg();
	updateLife();//check if there is any neighbor
	updatePosition();//update the position 
	//if slider changed then update the scolors
	for (int i=0;i<4;i++){
		if(psliderColor1[i]!=sliderColor1[i] ||
		   psliderColor2[i]!=sliderColor2[i]||
		   psliderColor3[i]!=sliderColor3[i]||
		   psliderColor4[i]!=sliderColor4[i]||
		   psliderColor5[i]!=sliderColor5[i]){
			sColorIsEqualSliderColor(i);
		}
	}
	//if the colorwheel changed then update the scolors and slider colors
	for (int i=0;i<4;i++){
		if(pwColor[i]!=wColor[i] ){
			if(enable1){
				sColor1[i]=wColor[i];				
			}
			if(enable2){
				sColor2[i]=wColor[i];		
			}
			if(enable3){
				sColor3[i]=wColor[i];		
			}
			if(enable4){
				sColor4[i]=wColor[i];		
			}
			if(enable5){
				sColor5[i]=wColor[i];		
			}
		
			sliderColorIsEqualsColor(i);
		}
	}
	
	updateColor();
	updateNumOfCircle();//update the number cell in the board
	
	for (int i=0;i<4;i++){
		psliderColor1[i]=sliderColor1[i];
		psliderColor2[i]=sliderColor2[i];
		psliderColor3[i]=sliderColor3[i];
		psliderColor4[i]=sliderColor4[i];
		psliderColor5[i]=sliderColor5[i];
		pwColor[i]=wColor[i];
			}
}
//--------------------------------------------------------------
//getCircularColor() was used for calculating the color from the color point you get from the color wheel
// parameter: float angle (from 0 to 360); float radius(0-1) ; scale (0-1)
// return: ofColor
//--------------------------------------------------------------
ofColor testApp::getCircularColor( float angle, float radius, float scale )
{
	radius = MIN( 1.0, MAX( 0.0, radius ) );
	
	angle -= floor( angle / 360 ) * 360;
	if( angle < 0 )
		angle += 360;
	
	float da;
	
	ofColor c;
	
	if( angle < 60 )
	{
		da  = angle / 60;
		c.r = (int)( 255 * scale );
		c.g = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.b = (int)( 255 * ( 1 - radius ) * scale );
		c.a = 255;
	}
	else if( angle < 120 )
	{
		da  = ( 120 - angle ) / 60;
		c.r = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.g = (int)( 255 * scale );
		c.b = (int)( 255 * ( 1 - radius ) * scale );
		c.a = 255;
	}
	else if( angle < 180 )
	{
		da  = 1 - ( 180 - angle ) / 60;
		c.r = (int)( 255 * ( 1 - radius ) * scale );
		c.g = (int)( 255 * scale );
		c.b = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.a = 255;
	}
	else if( angle < 240 )
	{
		da  = ( 240 - angle ) / 60;
		c.r = (int)( 255 * ( 1 - radius ) * scale );
		c.g = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.b = (int)( 255 * scale );
		c.a = 255;
	}
	else if( angle < 300 )
	{
		da  = 1 - ( 300 - angle ) / 60;
		c.r = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.g = (int)( 255 * ( 1 - radius ) * scale );
		c.b = (int)( 255 * scale );
		c.a = 255;
	}
	else if( angle <= 360 )
	{
		da  = ( 360 - angle ) / 60;
		c.r = (int)( 255 * scale );
		c.g = (int)( 255 * ( 1 - radius ) * scale );
		c.b = (int)( 255 * ( da + ( 1 - da ) * ( 1 - radius ) ) * scale );
		c.a = 255;
	}
	
	return c;
}
//--------------------------------------------------------------
// draw() was used to draw all the things on the screen.
// It will show the 40 circles horizotally and 30 circles vertically, and the string messages.
// Each circle will change its color depends on which stage they are on.
//--------------------------------------------------------------
void testApp::draw(){
	
	//-----------

	
	//---------------
	
	//draw all the cells
 
	for (int x=0; x<windowcol;x++){
		for(int y=0; y<windowrow;y++){
			ofSetColor(Life[x][y].red,Life[x][y].green,Life[x][y].blue);	
			Life[x][y].draw(ofGetWidth(),ofGetHeight());
		}
	}
	//ShowMsg if flag is true
	if(flag){
		ofSetColor(255,0,0);
		string temp;
		temp="";
		temp+="Press '+' or '-' to increase/decrease the speed \n";
		temp+="Speed: "+ofToString(frames)+"\n";
		temp+="Alive Circles: " +ofToString(NumOfALiveCircle)+"\n";
		temp+="Size of the steps: " +ofToString(steps)+"\n";
		temp+="Add a Circle after this number of Hit: " +ofToString(aliveSlider)+"\n";
		temp+="Stage1: " +ofToString(stage1)+"\n";
		temp+="Stage2: " +ofToString(stage2)+"\n";
		temp+="Stage3: " +ofToString(stage3)+"\n";
		temp+="Stage4: " +ofToString(stage4)+"\n";
		temp+="Timer: " +ofToString(ofGetElapsedTimef() )+"\n";
		ofDrawBitmapString(temp, 10, 20);
	}
	int bx = 2;
	int by = 2;
	
	//top left color
	//ofSetColor( sColor1[0]*255, sColor1[1]*255, sColor1[2]*255, sColor1[3] );
	//ofRect( 0 + bx, 0 + by, 100 - bx * 2, 100 - by * 2 );
	
	gui.draw();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
		case '-':
			//frame has to be greather than one
			if(frames>1){
				frames--;
			}
			break;
		case '+':
				frames++;
			break;
		case '[':
			if(aliveSlider>1)
				aliveSlider--;
			break;
		case ']':
			if(aliveSlider<42)
				aliveSlider++;
			break;
		case ';':
			if(steps>1)
				steps--;
			break;
		case '\'':
			if(steps<10)
				steps++;
			break;
		case 'f':
			//for showMsg
			flag=!flag;
			break;
		case 't':
			ofToggleFullscreen();
			break;
		case ' ':
			gui.toggleDraw();
			showGui=!showGui;
			break;
		case 'a':
			addNewCell();
			break;
		case 'o':
			gui.prevPage();
			break;
		case 'p':
			gui.nextPage();
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
//mousePressed() is used for adding/deleting cells in the board. 
//---------------------------------------- ---------------------
void testApp::mousePressed(int x, int y, int button){
	
	//convert pressed x position to (0-39)
	int convertx=float(x)/ofGetWidth()*float(windowcol);
	//convert pressed y position to (0-39)
	int converty=float(y)/ofGetHeight()*float(windowrow);
	
	//log_error to show the dx and dy of the cell
	ofLog(OF_LOG_ERROR, ofToString(Life[convertx][converty].dx) );
	ofLog(OF_LOG_ERROR, ofToString(Life[convertx][converty].dy) );
	
	//enable to add/delete a cell with the mouse when the gui is not showing
	if(!showGui){
		//set the cell alive or dead at the position u pressed
		if(Life[convertx][converty].alive==false){
			Life[convertx][converty].alive=true;
			Life[convertx][converty].setCells(convertx,converty);
		}
		else
			Life[convertx][converty].alive=false;
		
	}
	printf("mousepressed: %i, %i %i\n", x, y, button);
	
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}