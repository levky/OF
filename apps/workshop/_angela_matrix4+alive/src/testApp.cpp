#include "testApp.h"


	
void testApp::changedirection(int x,int y){
    Life[x][y].dx*=-1;
	Life[x][y].dy*=-1;
	//mode=ofRandom(1,4);
	Life[x][y].addCrashes(Life[x][y].cellcolor);
}
	 
bool testApp::checkneighbor(int x,int y,int curx,int cury){ 
	if(x<0 ||x >windowcol-1 ||y<0 ||y>windowrow-1) return false;
	//if both cell is alive 
	if (Life[x][y].alive && Life[curx][cury].alive)
	{ 
		if( map[x][y].getnextx()==map[curx][cury].getnextx() && map[x][y].getnexty()==map[curx][cury].getnexty()){
			if(map[x][y].cellcolor==map[curx][cury].cellcolor){
				if(map[x][y].counter<pcounter)
					Life[x][y].counter+=1;
				else
				{	
					int a,b;
					a=ofRandom(0,windowcol);
					b=ofRandom(0,windowrow);
					Life[a][b].alive=true;
					Life[a][b].setCells(a,b);
					Life[x][y].counter=10;
					map[x][y].counter=0;
				}
			}
			return true;
		}
		if(map[x][y].getnextx()==map[curx][cury].col&&map[x][y].getnexty()==map[curx][cury].row){
			if(map[x][y].cellcolor==map[curx][cury].cellcolor){
				if(map[x][y].counter<pcounter)
					Life[x][y].counter+=1;
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
			if(map[x][y].numItems>0){
				changedirection(x,y);
			}
			
			tempx=map[x][y].col+map[x][y].dx;
			tempy=map[x][y].row+map[x][y].dy;
			if(	map[x][y].alive){
				NumOfALiveCircle++;
				if(tempx<windowcol && tempy<windowrow&&tempx>=0 &&tempy>=0){
					//if the next position dont have neighbour, change position if it is alive
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
	
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);
	
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
	
	//random set cell alive
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
	toggle1=false;
	//gui.loadFromXML();
	//gui.show();
	ofxOscMessage m1;
	m1.setAddress("/2/slider/4");//speed
	m1.addFloatArg(5);
	sender.sendMessage(m1);
	ofxOscMessage m2;
	m2.setAddress( "/2/slider/5" );
	m2.addFloatArg(50);
	sender.sendMessage( m2 );
	ofxOscMessage m3;
	m3.setAddress( "/2/slider/6" );
	m3.addFloatArg(5);
	sender.sendMessage( m3 );
	ofxOscMessage m4;
	m4.setAddress( "/2/fullscreen" );
	m4.addIntArg(0);
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/2/ShowMsg" );
	m5.addIntArg(0);
	sender.sendMessage( m5 );
}

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
			map[i][j].cellcolor=Life[i][j].cellcolor;
			map[i][j].counter=Life[i][j].counter;
		}
	}

	updateLife();
	
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		if ( m.getAddress() == "/tuio/2Dcur" )
		{	
			if(m.getArgAsString( 0 )=="set"){
				mouseX=m.getArgAsFloat( 2 )*ofGetWidth();
				mouseY=m.getArgAsFloat( 3 )*ofGetHeight();
				mousePressed (mouseX,mouseY,0);
			}
		}
		
		else if(m.getAddress()=="/slider/1"){
			br=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[0]=m.getArgAsFloat(0);
		}
		else if(m.getAddress()=="/slider/2"){
			bg=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[1]=m.getArgAsFloat(0);
		}
		else if(m.getAddress()=="/slider/3"){
			bb=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[2]=m.getArgAsFloat(0);
		}
		
		else if(m.getAddress()=="/slider/4"){
			frames=m.getArgAsFloat(0)*100;
			if (frames==0)
				frames=1;
		}
		
		else if(m.getAddress()=="/slider/5"){
			pcounter=m.getArgAsFloat(0)*200;
		}
		else if(m.getAddress()=="/slider/6"){
			deadspeed=m.getArgAsFloat(0)*200;
		}
					
		else if (m.getAddress()=="/button/A1"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('+');
		}
		else if (m.getAddress()=="/button/B1"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('-');
		}
		else if (m.getAddress()=="/button/A2"){
			if(m.getArgAsInt32(0)==1)
			keyPressed(']');
		}
		else if (m.getAddress()=="/button/B2"){
			if(m.getArgAsInt32(0)==1)
			keyPressed('[');
		}
		else if (m.getAddress()=="/button/C1"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('r');
		}
		else if (m.getAddress()=="/button/C2"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('g');
		}
		else if (m.getAddress()=="/button/C3"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('b');
		}

//touchosc
		
		else if(m.getAddress()=="/2/slider/5"){
			pcounter=m.getArgAsFloat(0)*200;
			if (pcounter<5) {
				pcounter=1;
			}
		}
		else if(m.getAddress()=="/2/slider/6"){
			deadspeed=m.getArgAsFloat(0)*80;
			if (deadspeed<5) {
				deadspeed=1;
			}
		}

		else if(m.getAddress()=="/2/slider/4"){
			frames=m.getArgAsFloat(0)*100;
			if (frames==0){
				frames=1;
			}
		}
		else if (m.getAddress()=="/2/C1"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('r');
		}
		else if (m.getAddress()=="/2/C2"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('g');
		}
		else if (m.getAddress()=="/2/C3"){
			if(m.getArgAsInt32(0)==1)
				keyPressed('b');
		}
		else if (m.getAddress()=="/2/fullscreen"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed('t');
			}
		}
		
		/*
		else if (m.getAddress()=="/2/E1"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed(' ');
			}
		}
		 */
		
		else if(m.getAddress()=="/2/ShowMsg"){
			if(m.getArgAsInt32(0)==1||m.getArgAsInt32(0)==0){
				keyPressed('f');
			}
		}
	}
	updateLife();
	updatePosition();
	updateNumOfCircle();
	
}

//--------------------------------------------------------------
void testApp::draw(){
	glEnable(GL_TEXTURE_3D);
	for (int i=0; i<windowcol;i++){
		for(int j=0; j<windowrow;j++){
			ofSetColor(Life[i][j].red,Life[i][j].green,Life[i][j].blue);	
			Life[i][j].draw(ofGetWidth());
		}
	}
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
			
		case '1':mode=1;
			break;
		case '2':mode=2;
			break;
		case '3':mode=3;
			break;
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
		case ' ':
			gui.toggleDraw();
			break;
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

