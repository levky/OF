/*
 * Title: testApp.cpp
 * Created by Angela Chim
 * Summary: This program is in a 2D particle system. In this program you can use mouse force, flocking, grabbing,
 * gravity, adding and deleting boid.  Also this program has implemented with the osc, which allow you to control the program
 * using our customize touchosc interface or the oscemote interface.
 * Created: December 2010
 */
#include "testApp.h"
#include "ofxBox2dBaseShape.h"

//--------------------------------------------------------------
testApp::testApp(){
}

//--------------------------------------------------------------
// setup() runs at the start of the program. It initialize the variables that include the background color, framerate, osc receiver, 
// osc sender, mouse force, flocking, grabbing, gravity, showmsg, boids, gui. 
// Also for touchosc, it will send the initial settings to your iphone/ipod/ipod
// Grabbing,mouseforce,flocking,gravity and fullscreen are set to false. Enable addboids, gui and ShowMsg are set to true. 
// Gravity is set to 0. The boids MaxVelocity is 10, too close distance is 45 and in sight distance is 75.
//--------------------------------------------------------------
void testApp::setup() {

	br=20;
	bg=20;
	bb=20;
	myColors[0]=20/255;
	myColors[1]=20/255;
	myColors[2]=20/255;
	ofSetVerticalSync(true);
	ofBackground(20, 20, 20);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(20);
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);
	bGrabbing =false;
	bMouseForce = false;
	bFlockings = false;
	bAddBoids = true; //for adding boids
	bAGravity=false;
	
	pbGrabbing =false;
	pbMouseForce = false;
	pbFlockings = false;
	pbAGravity=false;
	bShowMsg=true;
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	box2d.createBounds();
	
	pBoids=new boids(0);
	pBoids->setMaxVelocity(10);
	pBoids->setTooCloseDist(45.0);
	pBoids->setInSightDist(75.0);
	
//settings for gui
	gui.addToggle("Toggle Mouse Force", bMouseForce);
	gui.addToggle("Toggle grabbing", bGrabbing);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addTitle("GuiDraw");
	gui.addColorPicker("BG Color", myColors);
	
	gui.addToggle("Toggle Flockings", bFlockings).setNewColumn(true);
	gui.addTitle("subtract one boid");

	gui.addToggle("Toggle gravity", bAGravity).setNewColumn(true);
	gui.addToggle("enable/disable adding boids",bAddBoids);

	//gui.loadFromXML();
	
	//show gui
	gui.show();
	
//for touchOSC, send the initial settings to iphone/ipod/ipod	
	ofxOscMessage m1;
	m1.setAddress( "/1/A1" );//mouse force
	m1.addIntArg(0);
	sender.sendMessage( m1 );
	ofxOscMessage m2;
	m2.setAddress( "/1/A2" );//flocking
	m2.addIntArg(0);
	sender.sendMessage( m2 );
	ofxOscMessage m3;
	m3.setAddress( "/1/gravity" );//gravity
	m3.addIntArg(0);
	sender.sendMessage( m3 );
	ofxOscMessage m4;
	m4.setAddress( "/1/B3" );//enable or disable adding boid
	m4.addIntArg(1);
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/1/fullscreen" );//fullscreen
	m5.addIntArg(0);
	sender.sendMessage( m5 );
	ofxOscMessage m6;
	m6.setAddress( "/1/E1" );//gui
	m6.addIntArg(1);
	sender.sendMessage( m6 );
	ofxOscMessage m7;
	m7.setAddress("/1/ShowMsg");//showmsg
	m7.addIntArg(1);
	sender.sendMessage(m7);

}

//--------------------------------------------------------------
//checkFlag() was used for checking the flags of the program.  
//For example:	when mouse force is true, flocking and gravity is false
//				when flocking is true, mouse force and gravity is false
//				when gravity is true, mouse force and flocking is false
//
//--------------------------------------------------------------
void testApp::checkFlag(){
	if(pbMouseForce!=bMouseForce){
		//when mouse force change to true, flocking and gravity will change to false
		if(bMouseForce){
			//bGrabbing=false;
			bMouseForce=true;
			mtimer=ofGetElapsedTimef()+ 2.5;
			bFlockings=false;
			//send osc message to touchosc, to tell it that the mouse force is true and flocking is false
			ofxOscMessage m1;
			m1.setAddress( "/1/A1" );
			m1.addIntArg(1);
			sender.sendMessage( m1 );
			ofxOscMessage m2;
			m2.setAddress( "/1/A2" );
			m2.addIntArg(0);
			sender.sendMessage( m2 );
		}
	}
	//when flocking change to true,mouse force and gravity will change to false
	if(pbFlockings!=bFlockings){
		if(bFlockings){
			//bGrabbing=false;
			bMouseForce=false;
			bFlockings=true;
			//send osc message to touchosc, telling it that the mouse force is true and flocking is false
			ofxOscMessage m3;
			m3.setAddress( "/1/A1" );
			m3.addIntArg(0);
			sender.sendMessage( m3 );
			ofxOscMessage m4;
			m4.setAddress( "/1/A2" );
			m4.addIntArg(1);
			sender.sendMessage( m4 );
		}
	}
	//when gravity is true, the program will send osc message to touchosc, telling it that the mouse force and flocking is false
	if(bAGravity==true){
		ofxOscMessage m3;
		m3.setAddress( "/1/A1" );
		m3.addIntArg(0);
		sender.sendMessage( m3 );
		ofxOscMessage m4;
		m4.setAddress( "/1/A2" );
		m4.addIntArg(0);
		sender.sendMessage( m4 );
		ofxOscMessage m5;
		m5.setAddress( "/1/gravity" );
		m5.addIntArg(1);
		sender.sendMessage( m5 );
	}
}
//--------------------------------------------------------------
//addBoids() was used for adding boid into the 2d particle box
//The parameters:	mouseX was a float number from 0 to the window width
//					mouseY was a float number from 0 to the window height
//
//--------------------------------------------------------------
void testApp::addBoids(float mouseX, float mouseY){
	float r = ofRandom(3, 10);		// a random radius 3px - 10x
	CustomParticle p;
	p.setPhysics(3, 0.53, 0.31);//set mass=3, bounce=0.53, friction=0.31
	p.setup(box2d.getWorld(), mouseX, mouseY, r);
	p.color.r = ofRandom(20, 100);
	p.color.g = ofRandom(20, 255);;
	p.color.b = ofRandom(150, 255);
	customParticles.push_back(p);
	pBoids->addBoid();
}	
//--------------------------------------------------------------
//deleteBoids() was used for delete one boid in the 2d particle box.
//The custom particle required to have one or more particle in the system.
//--------------------------------------------------------------
void testApp::deleteBoids(){
	if(customParticles.size()>0){
		customParticles[customParticles.size()-1].destroyShape();
		customParticles.pop_back();
		pBoids->subtractBoid();
	}
}
//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
// For example:  for oscemote, if there is changes make on the mouse pad it will check whether it can add boid or not. 
//				If you have enable adding boids then you will add one boid on screen, the point is where you touch on the mouse pad. 
//				If there is nothing change on the mouse pad for 2.5 sec the toggle for mouse force will set to false.
//--------------------------------------------------------------
void testApp::update() {
	
	checkFlag();
	box2d.update();
//if the width or height is changed, redraw boundary
	if(pwidth!=ofGetWidth()||pheight!=ofGetHeight())
		keyPressed('w');
	
	//if gravity button is on
	if(bAGravity==true){
	ofxOscMessage m5;
	m5.setAddress( "/1/gravity" );
	m5.addIntArg(0);//gravity set to 0
	sender.sendMessage( m5 );
	}
	bAGravity=false;//set gravity to false
	
	//if there is nothing changes on the mouse pad for 2.5sec the toggle for mouse force is set to false 
	if (  mtimer < ofGetElapsedTimef()&&bmouse==false ){
		bMouseForce=false;
	}
	//if timer is less then elapesed time, clear pboids2
	if ( timer < ofGetElapsedTimef() ){
		pBoids2.clear();
	}
	//receive message from OSC
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		//if there is changes make on the mouse pad for oscemote
		if ( m.getAddress() == "/tuio/2Dcur" )
		{	
			if(m.getArgAsString( 0 )=="set"){
				bmouse=true;
				timer=ofGetElapsedTimef()+ 1.0f;
				
				//add boid if you enable adding boids
				if(bAddBoids){
					mouseX=m.getArgAsFloat( 2 )*ofGetWidth();
					mouseY=m.getArgAsFloat( 3 )*ofGetHeight();
					addBoids(mouseX,mouseY);
					
				}
				//if not add boids
				else{
					//add new boid for pboids2,then set position for new boid
					if(pBoids2.size() < m.getArgAsInt32(1)){
						pBoids2.push_back(new boid());
						pBoids2[m.getArgAsInt32(1)-1]->setPosition(m.getArgAsFloat( 2 )*ofGetWidth(), m.getArgAsFloat( 3 )*ofGetHeight());
					}
					//set position for the boids
					else{
						pBoids2[m.getArgAsInt32(1)-1]->setPosition(m.getArgAsFloat( 2 )*ofGetWidth(), m.getArgAsFloat( 3 )*ofGetHeight());
					}	

				}
			}//finish set
			
			
			if(m.getArgAsString( 0 )=="alive"){
				//if there is more then 1 mouse point is alive , add mtimer by 2.5sec and set bmouse to true
				if(m.getNumArgs()>1){
					mtimer=ofGetElapsedTimef()+ 2.5;
					bmouse=true;
				}
				//if only one mouse point , add mtimer by 2.5 sec and set bmouse to false
				else {
					mtimer=ofGetElapsedTimef()+ 2.5;
					bmouse=false;
				}
			}
		}
//for touchosc
		//if there is any changes make on the mouse pad for touchosc
		if ( m.getAddress() == "/1/touchosc/set" )
		{	
				//add boids if you have enable adding boids and the boids are less then maxboids
				if(bAddBoids && pBoids->getNumBoids()<MAXBOIDS){
					mouseX=m.getArgAsFloat( 0)*ofGetWidth();
					mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
					addBoids(mouseX,mouseY);
				}
				//if not add boids, just get the mouse position 
				else{
					
					mouseX=m.getArgAsFloat( 0)*ofGetWidth();
					mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
					
				}
		}
		//background for red
		else if(m.getAddress()=="/slider/1"){
			br=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[0]=m.getArgAsFloat(0);
		}
		//background for green
		else if(m.getAddress()=="/slider/2"){
			bg=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[1]=m.getArgAsFloat(0);
		}
		//background for blue
		else if(m.getAddress()=="/slider/3"){
			bb=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[2]=m.getArgAsFloat(0);
		}
		//if mouse force button is pressed
		else if (m.getAddress()=="/button/A1"){
			timer=ofGetElapsedTimef()+ 5.0f;
			mtimer=ofGetElapsedTimef()+ 5.0f;
			
			//if mouse force is on and gravity is false, then change the toggle for mouse force
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
			bMouseForce = !bMouseForce;
			
		}
		//if flocking button is pressed and gravity is false, then change the toggle for flocking
		else if (m.getAddress()=="/button/A2"){
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
			bFlockings = !bFlockings;
		}
		//change toggle for grabbing
		else if (m.getAddress()=="/button/B1"){
			if(m.getArgAsInt32(0)==1)
			bGrabbing = !bGrabbing;
		}
		//delete boids when button is pressed
		else if (m.getAddress()=="/button/B2"){
			deleteBoids();
		}
		//add boids when button is pressed
		else if(m.getAddress()=="/button/B3"){
			if(m.getArgAsInt32(0)==1)
			bAddBoids = !bAddBoids;
		}
		//show the gui 
		else if (m.getAddress()=="/button/E1"){
			if(m.getArgAsInt32(0)==1)
			gui.toggleDraw();
		}
		//when acceleration is on , change the toggle of mouse force, and flocking to false and gravity to true
		else if (m.getAddress()=="/acceleration/xyz"){
			bMouseForce=false;
			bFlockings=false;
			bAGravity=true;
			float xg = m.getArgAsFloat( 0 )*maxgravity;
			float yg = m.getArgAsFloat( 1 )*maxgravity*-1;
			box2d.setGravity(xg, yg);
		}
		//if the accelerometer is pressed
		else if (m.getAddress()=="/accelerometer"){
			//if accelerometer is off then set gravity to false
			if(m.getArgAsInt32(0)==0)
				bAGravity=false;
			//else set gravity to true
			else
				bAGravity=true;
		}
	//TouchOSC
		//MouseForce	
		else if (m.getAddress()=="/1/A1"){ 
			//set gravity to 0
			box2d.setGravity(0,0);
			timer=ofGetElapsedTimef()+ 5.0f;
			mtimer=ofGetElapsedTimef()+ 5.0f;
			//if change mouse force to true and gravity is false, set the toggle of mouse force to true
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
				bMouseForce = true;
			//if change to false if gravity is false, then set the toggle of mouse force to false
			else if(m.getArgAsInt32(0)==0 && bMouseForce==true && bAGravity==false)
				bMouseForce = false;
		}
		//Flocking
		else if (m.getAddress()=="/1/A2"){
			//set gravity to 0
			box2d.setGravity(0,0);
			//if change flocking to true and gravity false, then change flocking to true
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
				bFlockings = true;
			//if change flocking to false and gravity is false, then change flocking to false
			if(m.getArgAsInt32(0)==0 && bAGravity==false)
				bFlockings = false;
		}
		//grabbing
		else if (m.getAddress()=="/1/B1"){
			//change grabbing to true
			if(m.getArgAsInt32(0)==1)
				bGrabbing = true;
			//change grabbing to false
			if(m.getArgAsInt32(0)==0)
				bGrabbing = false;
		}
		//button for delete boid
		else if (m.getAddress()=="/1/B2"){
			if(m.getArgAsInt32(0)==1)
				deleteBoids();
		}
		//toggle turns on to enable adding boid, turns off to disable it
		else if(m.getAddress()=="/1/B3"){
			if(m.getArgAsInt32(0)==1)
				bAddBoids = true;
			if(m.getArgAsInt32(0)==0)
				bAddBoids = false;
			
		}
		//toggle button for gui
		else if (m.getAddress()=="/1/E1"){
			if(m.getArgAsInt32(0)==1)
				gui.toggleDraw();
			if(m.getArgAsInt32(0)==0)
				gui.toggleDraw();
		}
		//background color for red
		else if(m.getAddress()=="/1/slider/1"){
			br=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[0]=m.getArgAsFloat(0);
		}
		//background color for green
		else if(m.getAddress()=="/1/slider/2"){
			bg=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[1]=m.getArgAsFloat(0);
		}
		//background color for blue
		else if(m.getAddress()=="/1/slider/3"){
			bb=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[2]=m.getArgAsFloat(0);
		}
		//toggle button for fullscreen
		else if(m.getAddress()=="/1/fullscreen"){
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
			keyPressed('t');

		}
		//toggle button for redraw boundary
		else if(m.getAddress()=="/1/window"){
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
			keyPressed('w');
		}
		//if the accelerometer is on, set the x and y gravity
		else if(m.getAddress()=="/accxyz") {

			bMouseForce=false;
			bFlockings=false;
			bAGravity=true;
			float xg = m.getArgAsFloat( 0 )*maxgravity;
			float yg = m.getArgAsFloat( 1 )*maxgravity*-1;
			box2d.setGravity(xg, yg);
		}
		//toggle button for show message
		else if(m.getAddress()=="/1/ShowMsg") {	
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
				keyPressed('m');
		}
			
	}
			

	//mouse force
	//if there is nothing changes on the mouse pad for 2.5sec then it will change the mouse force to false
	if(bMouseForce) {
		mtimer=ofGetElapsedTimef()+ 2.5;
		float strength = 8.0f;
		float damping  = 0.7f;
		float minDis   = 100;
		//if there is one or more mouse points, separate the boids equally to the mouse points
		if(pBoids2.size()>0){
			for(int i=0; i<customParticles.size(); i++) {
				customParticles[i].addAttractionPoint(pBoids2[i % pBoids2.size()]->getPosition().x, pBoids2[i % pBoids2.size()]->getPosition().y, strength, minDis);
				customParticles[i].addDamping(damping, damping);
			}
		}
		//or else attract all boids into one point
		else{
			for(int i=0; i<customParticles.size(); i++) {
				customParticles[i].addAttractionPoint(mouseX, mouseY, strength, minDis);
				customParticles[i].addDamping(damping, damping);
			}
		}
	}
	//if flocking turns off, set each boid their position and velocity
	if(!bFlockings){
			for (int i=0;i<customParticles.size();i++){
				pBoids->getBoids()[i]->setPosition(customParticles[i].getPosition().x,customParticles[i].getPosition().y);
				pBoids->getBoids()[i]->setVelocity(customParticles[i].getVelocity().x,customParticles[i].getVelocity().y);
			}
	}
	
	//flocking
	if(bFlockings){
	
		pBoids->flock();
		pBoids->bounce();
		pBoids->update();

		float strength = 8.0f;
		float damping  = 0.7f;
		float minDis   = 100;
		
//		for(int i=0; i<circles.size(); i++){
//			circles[i].addAttractionPoint(pBoids->getBoids()[i]->getPosition().x,pBoids->getBoids()[i]->getPosition().y,strength,pBoids->getInSightDist() );
//			circles[i].addDamping(damping,damping);
//		}
		
		for(int i=0; i<customParticles.size(); i++){
		customParticles[i].addAttractionPoint(pBoids->getBoids()[i]->getPosition().x,pBoids->getBoids()[i]->getPosition().y,strength,pBoids->getInSightDist() );
		customParticles[i].addDamping(damping,damping);
		}
	}
	//grabbing
	if (bGrabbing) box2d.enableGrabbing();
	else box2d.disableGrabbing();

	toggle1=false;
	pbGrabbing =bGrabbing;
	pbMouseForce = bMouseForce;
	pbFlockings = bFlockings;
	pbAGravity =bAGravity;
	pwidth=ofGetWidth();
	pheight=ofGetHeight();
		
}
//--------------------------------------------------------------
// draw() was used to draw all the 2d objects on the screen.
// It will show the box2d, the custom particles, the string messages, and gui.
//--------------------------------------------------------------
void testApp::draw() {
	
//	for(int i=0; i<circles.size(); i++) {
//		circles[i].draw();
//	}
//	for(int i=0; i<polygons.size(); i++) {
//		polygons[i].draw();
//	}
//	for(int i=0; i<boxes.size(); i++) {
//		boxes[i].draw();
//	}
	for(int i=0; i<customParticles.size(); i++) {
		customParticles[i].draw();
	}
	
	box2d.draw();
	
	//stores the mouse position 
	px = mouseX;
	py = mouseY;
	
	if(bShowMsg){
		string info = "";
		info += "Press [f] to toggle Mouse Force ["+ofToString(bMouseForce)+"]\n"; 
		info += "Press [b] to toggle flockings   ["+ofToString(bFlockings)+"]\n";
		info += "Press [g] to toggle grabbing    ["+ofToString(bGrabbing)+"]\n";
		//info += "Press [c] for circles\n";
		info += "Press [z] for adding custom particle\n";
		info += "Press [q] for delete particle\n";
		info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
		info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
		info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
		ofSetColor(255, 255, 255);
		string buf;
		buf = "listening for osc messages on port" + ofToString( PORT )+" send on: "+ ofToString( SPORT );
		ofDrawBitmapString( buf, 10, 20 );
		ofDrawBitmapString(info, 30, 30);
	}
	gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
/*	
	if(key == 'c') {
		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		ofxBox2dCircle circle;
		circle.setPhysics(0.4, 0, 0);
		circle.setup(box2d.getWorld(), mouseX, mouseY, r);
		circles.push_back(circle);
	}
 */

	if(key == 'z') {
		float r = ofRandom(3, 10);		// a random radius 4px - 20px
		addBoids(mouseX,mouseY);
	}	
	if(key=='g'){
		bGrabbing= !bGrabbing;
		if (bGrabbing) box2d.enableGrabbing();
		else box2d.disableGrabbing();
	}
	if(key == 'f'){
		bMouseForce = !bMouseForce;
		mtimer=ofGetElapsedTimef()+ 2.5;
	}
	if(key == 't') {
		ofToggleFullscreen();
	}
	if(key=='b'){ 
		box2d.setGravity(0,0);
		bFlockings = !bFlockings;
		
		if(bFlockings==true){
			for (int i=0;i<customParticles.size();i++){
				pBoids->getBoids()[i]->setPosition(customParticles[i].getPosition().x,customParticles[i].getPosition().y);
				pBoids->getBoids()[i]->setVelocity(customParticles[i].getVelocity().x,customParticles[i].getVelocity().y);
			}
		}
	}

	if(key==' ')gui.toggleDraw();
	if(key=='[')gui.prevPage();
	if(key==']')gui.nextPage();
	if(key=='p')gui.nextPageWithBlank();
	
	if(key =='q'){
		deleteBoids();
	}
	if(key =='w'){
		box2d.getWorld()->DestroyBody(box2d.ground);
		box2d.createBounds();
	}
	if(key=='m'){
		bShowMsg=!bShowMsg;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
	
}
