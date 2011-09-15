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
#define speed 1
//--------------------------------------------------------------
testApp::testApp(){
}
void testApp::addblob(){
	blob temp;
	temp.px=ofRandom(0,BLOBS_WIDTH);
	temp.py=ofRandom(0,BLOBS_HEIGHT);
	temp.dx=(speed);
	temp.dy=(speed);
	pblobs.push_back(temp);
}//--------------------------------------------------------------
// setup() runs at the start of the program. It initialize the variables that include the background color, framerate, osc receiver, 
// osc sender, mouse force, flocking, grabbing, gravity, showmsg, boids, gui. 
// Also for touchosc, it will send the initial settings to your iphone/ipod/ipod
// Grabbing,mouseforce,flocking,gravity and fullscreen are set to false. Enable addboids, gui and ShowMsg are set to true. 
// Gravity is set to 0. The boids MaxVelocity is 10, too close distance is 45 and in sight distance is 75.
//--------------------------------------------------------------
void testApp::setup() {
		string XMLFile=ofToDataPath("ipAddress.xml");
	if( XML.loadFile(XMLFile) ){
		XML.loadFile(XMLFile);
		
	}
	else{
		
		XML.clear();
		XML.addTag("Ipod");
		XML.setValue("Ipod", "172.20.10.124", 0);
		XML.popTag();
		XML.saveFile(XMLFile);
	}
	HOST=XML.getValue("Ipod", "0", 0);
	
	br=100;
	bg=100;
	bb=100;

	myColors[0]=.5;
	myColors[1]=.5;
	myColors[2]=1;
	colorRange=1.;
	
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(20);
	receiver.setup(PORT);
	sender.setup(HOST,SPORT);

	bAddBoids = true; //for adding boids
	bShowMsg=false;
	
	bGrabbing =false;
	bMouseForce = false;
	bFlockings = false;
	bAGravity=false;
	bGravity=false;
	
	pbGrabbing =false;
	pbMouseForce = false;
	pbFlockings = false;
	pbAGravity=false;
	pbGravity=false;

	bCheckBound=true;
	
	boids_adding=false;
	boids_delete=false;
	
	//meta
	bmetaball=false;
	tex.allocate( BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
	texPixels	= new unsigned char[ BLOBS_WIDTH * BLOBS_HEIGHT * 3 ];
	

	
	
	//boids
	pBoids=new boids(0);
	boidsMaxVelocity=10;
    boidsTooCloseDist=100.0;
    boidsInSightDist=20.0;
    box2dFPS=30.0;
	boids_limNum=200;
	FAFED=0;
	pBoids->setMaxVelocity(boidsMaxVelocity);
	pBoids->setTooCloseDist(boidsTooCloseDist);
	pBoids->setInSightDist(boidsInSightDist);
	box2d.setFPS(box2dFPS);
    
	//custom particle
	strength = 8.0f;
	damping  = 0.7f;
	minDis   = 100;
	particle_radius=10;
	//p_particle_radius=particle_radius;
	particle_random_radius=true;
	particle_random_color=false;
	
	//box2d
	xg=0;
	yg=9;
	gui_mass=3;
	gui_bounce=0.53;
	gui_friction=0.31;
	box2d.init();
	box2d.setGravity(xg,yg);
	box2d.registerGrabbing();
	box2d.createBounds();
	bUpdatePhysic=false;
	//p_particle_radius=particle_radius;
	
	//blur effect
	number=0;
	stoptime=0;
	blurSlider=10;
	blurSpeed=0.5;
    
//settings for gui
	gui.addToggle("Toggle Mouse Force", bMouseForce);
	gui.addToggle("Toggle grabbing", bGrabbing);
	gui.addToggle("blank", toggle1);
	gui.addToggle("blank", toggle1);
	gui.addTitle("GuiDraw");
	gui.addColorPicker("BG Color", myColors);
	gui.addToggle("Toggle Flockings", bFlockings).setNewColumn(true);
	gui.addButton("subtract one boid", boids_delete);
	gui.addButton("adding one boid", boids_adding);
	//gui.addTitle("subtract one boid");
	gui.addToggle("Toggle gravity", bGravity).setNewColumn(true);
	gui.addToggle("enable/disable adding boids",bAddBoids);
	
	//box2d
	//gui.addPage("box2d");
	gui.addToggle("Update Physics", bUpdatePhysic);
	gui.addToggle("check bound", bCheckBound);
	gui.addSlider("Box2d FPS", box2dFPS, 1, 100);
	gui.addSlider("x gravity",xg,-maxgravity,maxgravity);
	gui.addSlider("y gravity",yg,-maxgravity,maxgravity);
	gui.addSlider("mass", gui_mass,0,50);
	gui.addSlider("bounce", gui_bounce,0,1);
	gui.addSlider("friction", gui_friction,0,1);
	
	//custom particle
//	gui.addPage("custom particle");
	gui.addSlider("strength",strength,0,50);
	gui.addSlider("damping",damping,0,1);
	gui.addSlider("mini Distance",minDis,0,200);
	gui.addToggle("random Radius", particle_random_radius);
	gui.addSlider("radius",particle_radius,1,100);
	gui.addToggle("random Color", particle_random_color);
	gui.addColorPicker("particle Color", myColors);
	gui.addToggle("Update Physics", bUpdatePhysic);
	
	//boids
	//gui.addPage("boids");
	gui.addSlider("Flock/arrive/flee/drift", FAFED,0,3);
	gui.addSlider("Limit Num", boids_limNum, 0, MAXBOIDS);
	gui.addSlider("Max Velocity", boidsMaxVelocity,0,100);
	gui.addSlider("Too Close Distance", boidsTooCloseDist, 0, 100);
	gui.addSlider("In sight distance", boidsInSightDist, 0,100);
	gui.addButton("subtract one boid", boids_delete);
	gui.addButton("adding one boid", boids_adding);
	gui.addToggle("enable/disable adding boids",bAddBoids);
	
	//blur effect
	gui.addSlider("blur",blurSlider,0,20);
	gui.addSlider("colorRange",colorRange,0,1);
	gui.addSlider("blur Speed",blurSpeed,0.1,1);

	//gui.setAutoSave(true);      

	//show gui
//	gui.show();
	gui.hide();
	
//for touchOSC, send the initial settings to iphone/ipod/ipod	
	ofxOscMessage m1;
	m1.setAddress( "/1/MouseForce" );//mouse force
	m1.addIntArg(0);
	sender.sendMessage( m1 );
	ofxOscMessage m2;
	m2.setAddress( "/1/Flocking" );//flocking
	m2.addIntArg(0);
	sender.sendMessage( m2 );
	ofxOscMessage m3;
	m3.setAddress( "/1/Gravity" );//gravity
	m3.addIntArg(0);
	sender.sendMessage( m3 );
	ofxOscMessage m4;
	m4.setAddress( "/1/AddBoid" );//enable or disable adding boid
	m4.addIntArg(1);
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/1/FullScreen" );//fullscreen
	m5.addIntArg(0);
	sender.sendMessage( m5 );
	ofxOscMessage m6;
	m6.setAddress( "/1/ShowGui" );//gui
	m6.addIntArg(0);
	sender.sendMessage( m6 );
	ofxOscMessage m7;
	m7.setAddress("/1/ShowMsg");//showmsg
	m7.addIntArg(0);
	sender.sendMessage(m7);	
	ofxOscMessage m8;
	m8.setAddress("/1/boidsMaxVelocity");
	m8.addFloatArg(boidsMaxVelocity);
	sender.sendMessage(m8);
	ofxOscMessage m9;
	m9.setAddress("/1/boidsTooCloseDist");  
	m9.addFloatArg(boidsTooCloseDist);
	sender.sendMessage(m9);
	ofxOscMessage m10;
	m10.setAddress( "/1/boidsInSightDist" );
	m10.addFloatArg(boidsInSightDist);//toggle is off for show msg
	sender.sendMessage( m10 );
	ofxOscMessage m11;
	m11.setAddress( "/1/box2dFPS" );
	m11.addFloatArg(box2dFPS);//toggle is off for show msg
	sender.sendMessage( m11 );
	
	ofxOscMessage m12;
	m12.setAddress("/1/boids_limNum");
	m12.addFloatArg(boids_limNum);
	sender.sendMessage(m12);
	ofxOscMessage m13;
	m13.setAddress("/1/xg");
	m13.addFloatArg(xg);
	sender.sendMessage(m13);
	ofxOscMessage m14;
	m14.setAddress("/1/yg");
	m14.addFloatArg(yg);
	sender.sendMessage(m14);
	ofxOscMessage m15;
	m15.setAddress("/1/gui_mass");
	m15.addFloatArg(gui_mass);
	sender.sendMessage(m15);
	ofxOscMessage m16;
	m16.setAddress("/1/gui_bounce");
	m16.addFloatArg(gui_bounce);
	sender.sendMessage(m16);
	ofxOscMessage m17;
	m17.setAddress("/1/gui_friction");
	m17.addFloatArg(gui_friction);
	sender.sendMessage(m17);
	ofxOscMessage m18;
	m18.setAddress("/1/strength");
	m18.addFloatArg(strength);
	sender.sendMessage(m18);
	ofxOscMessage m19;
	m19.setAddress("/1/damping");
	m19.addFloatArg(damping);
	sender.sendMessage(m19);
	ofxOscMessage m20;
	m20.setAddress("/1/minDis");
	m20.addFloatArg(minDis);
	sender.sendMessage(m20);
	ofxOscMessage m21;
	m21.setAddress("/1/particle_random_radius");
	m21.addIntArg(particle_random_radius);
	sender.sendMessage(m21);
	ofxOscMessage m22;
	m22.setAddress("/1/particle_radius");
	m22.addFloatArg(particle_radius);
	sender.sendMessage(m22);
	ofxOscMessage m23;
	m23.setAddress("/1/particle_random_color");
	m23.addIntArg(particle_random_color);
	sender.sendMessage(m23);
	ofxOscMessage m24;
	m24.setAddress("/1/slider/1");
	m24.addFloatArg(myColors[0]);
	sender.sendMessage(m24);
	ofxOscMessage m25;
	m25.setAddress("/1/slider/2");
	m25.addFloatArg(myColors[1]);
	sender.sendMessage(m25);
	ofxOscMessage m26;
	m26.setAddress("/1/slider/3");
	m26.addFloatArg(myColors[2]);
	sender.sendMessage(m26);
	ofxOscMessage m27;
	m27.setAddress("/1/bUpdatePhusic");
	m27.addIntArg(bUpdatePhysic);
	sender.sendMessage(m27);
	ofxOscMessage m28;
	m28.setAddress("/1/Grabbing");
	m28.addIntArg(bGrabbing);
	sender.sendMessage(m28);
	ofxOscMessage m29;
	m29.setAddress("/1/FAFED");
	m29.addIntArg(FAFED);
	sender.sendMessage(m29);
	ofxOscMessage m30;
	m30.setAddress("/1/blurSlider");
	m30.addFloatArg(blurSlider);
	sender.sendMessage(m30);
	ofxOscMessage m31;
	m31.setAddress("/1/colorRange");
	m31.addFloatArg(colorRange);
	sender.sendMessage(m31);
	ofxOscMessage m32;
	m32.setAddress("/1/blurSpeed");
	m32.addFloatArg(blurSlider);
	sender.sendMessage(m32);
	
	blur.setup(ofGetWidth(), ofGetHeight());
}
//--------------------------------------------------------------
void testApp::metaupdate()
{
	int i;
	int x;
	int y;
	
	//for each blobs
	for( i=0; i<pblobs.size(); ++i )
	{
	

		//square the range away from the center of the circle
		for( x = 0; x < BLOBS_WIDTH; x++ )
		{
			m_vx[ i * BLOBS_WIDTH + x ] = (int)( pow( (pBoids->getBoids()[i]->getPosition().x/ofGetWidth()*BLOBS_WIDTH - x ), 2 ) );
			
		}
		
		for( y = 0; y < BLOBS_HEIGHT; y++ )
		{
			m_vy[ i * BLOBS_HEIGHT + y ] = (int)( pow( ( pBoids->getBoids()[i]->getPosition().y/ofGetHeight()*BLOBS_HEIGHT - y ), 2 ) );
			
		}
		
	}
	
	for( y = 0; y < BLOBS_HEIGHT; y++)
	{
		//for each row, scan through the columns
		for ( x = 0; x < BLOBS_WIDTH; x++)
		{
			int j = 0;
			int m = 1;
			
			j = ( x * 3 ) + ( y * BLOBS_WIDTH * 3 );
			
			for ( i = 0; i < pblobs.size(); i++ )
			{
				// Increase this number to make your blobs bigger
				//	if( vy[ i * BLOBS_HEIGHT + y ] <100 ||  vx[ i * BLOBS_HEIGHT + x ] <100){
				m += 6000 / ( m_vy[ i * BLOBS_HEIGHT + y ] + m_vx[ i * BLOBS_WIDTH + x ] + 1 );
				//	}
			}
			
		
		//	if(m> 2843.9 *exp(-0.007*BLOBS_WIDTH)){
			if(m> 2843.9 *exp(-0.007*BLOBS_WIDTH)){
				texPixels[ j + 0 ] = (unsigned char)( 0 );
				texPixels[ j + 1 ] = (unsigned char)(100);
				texPixels[ j + 2 ] = (unsigned char)( 255);
			}
			else{
				texPixels[ j + 0 ] = (unsigned char)(0);
				texPixels[ j + 1 ] = (unsigned char)(0);
				texPixels[ j + 2 ] = (unsigned char)(0);
			}
		}
	}
}

//--------------------------------------------------------------
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
			mtimer=ofGetElapsedTimef()+ 2.5;
			bFlockings=false;
			bGravity=false;
		}
	}
	//when flocking change to true,mouse force and gravity will change to false
	if(pbFlockings!=bFlockings){
		if(bFlockings){
			bMouseForce=false;
			bGravity=false;
		}
	}
	//when gravity is true, the program will send osc message to touchosc, telling it that the mouse force and flocking is false
	if(pbGravity!=bGravity){
		if(bGravity){
			bMouseForce=false;
			bFlockings=false;
		}
	}
}
//--------------------------------------------------------------
//sendOscFlag() was used after check flag. It is for touchosc only and it will send the osc message to the ipod/iphone. 
//For example:	when mouse force is true, flocking and gravity is false
//				when flocking is true, mouse force and gravity is false
//				when gravity is true, mouse force and flocking is false
//
//--------------------------------------------------------------
void testApp::sendOscFlag(){

	//send osc message to touchosc
	ofxOscMessage m1;
	ofxOscMessage m2;
	ofxOscMessage m3;
			
	if(bMouseForce){
		m1.setAddress( "/1/MouseForce" );
		m1.addIntArg(1);
		sender.sendMessage( m1 );
	}
	else{
		m1.setAddress( "/1/MouseForce" );
		m1.addIntArg(0);
		sender.sendMessage( m1 );
	}
	if(bFlockings){
		m2.setAddress( "/1/Flocking" );
		m2.addIntArg(1);
		sender.sendMessage( m2 );
	}
	else{
		m2.setAddress( "/1/Flocking" );
		m2.addIntArg(0);
		sender.sendMessage( m2 );
	}
	if(bGravity){
		m3.setAddress( "/1/Gravity" );
		m3.addIntArg(1);
		sender.sendMessage( m3 );
		}
	else{
		m3.setAddress( "/1/Gravity" );
		m3.addIntArg(0);
		sender.sendMessage( m3 );
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
	if(!particle_random_radius){
		r=particle_radius;
	}
	p.setPhysics(gui_mass,gui_bounce,gui_friction);//set mass=3, bounce=0.53, friction=0.31
	p.setup(box2d.getWorld(), mouseX, mouseY, r);

	p.color.r = ofRandom(0, 100);
	p.color.g = ofRandom(0, 100); 
	p.color.b = ofRandom(0, 100);
	p.masterRed=100;
	p.masterBlue=100;
	p.masterGreen=100;
	
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
//parseOSCMsg() was used for decoding the different OSC messages and determine what is the appropriate actions.
// There is two type of osc interface they are:
//     0 - oscemote 
//     1 - touchOSC
//--------------------------------------------------------------
void testApp::parseOSCMsg(){
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		switch(OSCInterface){
			case 0: 
				//OSCemote
				//if there is changes make on the mouse pad for oscemote
				if ( m.getAddress() == "/tuio/2Dcur" )
				{	
					if(m.getArgAsString( 0 )=="set"){
						bmouse=true;
						timer=ofGetElapsedTimef()+ 1.0f;
						
						//add boid if you enable adding boids and you are less then maxboids
						if(bAddBoids && pBoids->getNumBoids()<MAXBOIDS){
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
				//for red
				else if(m.getAddress()=="/slider/1"){
					myColors[0]=m.getArgAsFloat(0);
				}
				//for green
				else if(m.getAddress()=="/slider/2"){
					myColors[1]=m.getArgAsFloat(0);
				}
				//for blue
				else if(m.getAddress()=="/slider/3"){
					myColors[2]=m.getArgAsFloat(0);
				}
				//if mouse force button is pressed
				else if (m.getAddress()=="/button/A1"){
					timer=ofGetElapsedTimef()+ 5.0f;
					mtimer=ofGetElapsedTimef()+ 5.0f;
					
					//if mouse force is on and gravity is false, then change the toggle for mouse force
					if(m.getArgAsInt32(0)==1)
						bMouseForce = !bMouseForce;
					
				}
				//if flocking button is pressed and gravity is false, then change the toggle for flocking
				else if (m.getAddress()=="/button/A2"){
					if(m.getArgAsInt32(0)==1)
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
				//when accelerometer is on , change the toggle of mouse force, and flocking to false and gravity to true
				else if (m.getAddress()=="/acceleration/xyz"){
					bAGravity=true;
					gtimer=ofGetElapsedTimef()+ 1.0f;
					xg = m.getArgAsFloat( 0 )*maxgravity;
					yg = m.getArgAsFloat( 1 )*maxgravity*-1;
				}
				//if the accelerometer is pressed
				//else if (m.getAddress()=="/accelerometer")
				
				break;
				
			case 1:
				//TouchOSC
				
				//if there is any changes make on the mouse pad for touchosc
				if ( m.getAddress() == "/1/touchosc/set" )
				{	
					//add boids if you have enable adding boids and the boids are less then maxboids
					if(bAddBoids && pBoids->getNumBoids()<MAXBOIDS){
						mouseX=m.getArgAsFloat( 0)*ofGetWidth();
						mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
						target.set(mouseX,mouseY,0);
						addBoids(mouseX,mouseY);
						if(bmetaball){
							m_vy = new int[ (pblobs.size()+1) * ofGetHeight() ];
							m_vx = new int[ (pblobs.size()+1) * ofGetWidth() ];
							
							addblob();
						}
					}
					//if not add boids, just get the mouse position 
					else{
						mouseX=m.getArgAsFloat( 0)*ofGetWidth();
						mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
						target.set(mouseX,mouseY,0);
					}
				}
				//MouseForce	
				else if (m.getAddress()=="/1/MouseForce"){ 
					
					timer=ofGetElapsedTimef()+ 5.0f;
					mtimer=ofGetElapsedTimef()+ 5.0f;
					//if change mouse force to true and gravity is false, set the toggle of mouse force to true
					if(m.getArgAsInt32(0)==1)
						bMouseForce = true;
					//if change to false if gravity is false, then set the toggle of mouse force to false
					else if(m.getArgAsInt32(0)==0 && bMouseForce==true)
						bMouseForce = false;
				}
				//Flocking
				else if (m.getAddress()=="/1/Flocking"){
					
					//if change flocking to true and gravity false, then change flocking to true
					if(m.getArgAsInt32(0)==1)
						bFlockings = true;
					//if change flocking to false and gravity is false, then change flocking to false
					if(m.getArgAsInt32(0)==0)
						bFlockings = false;
				}
				//Grabbing
				else if (m.getAddress()=="/1/Grabbing"){
					//change grabbing to true
					if(m.getArgAsInt32(0)==1)
						bGrabbing = true;
					//change grabbing to false
					if(m.getArgAsInt32(0)==0)
						bGrabbing = false;
				}
				//button for delete boid
				else if (m.getAddress()=="/1/DeleteBoid"){
					if(m.getArgAsInt32(0)==1){
						deleteBoids();
						
						if(bmetaball){
							pblobs.clear();	
							for(int a=0;a<pBoids->getNumBoids() ;a++){
								addblob();
							}
						}
					}
				}
				//toggle turns on to enable adding boid, turns off to disable it
				else if(m.getAddress()=="/1/AddBoid"){
					if(m.getArgAsInt32(0)==1)
						bAddBoids = true;
					if(m.getArgAsInt32(0)==0)
						bAddBoids = false;
				}
				//toggle button for gui
				else if (m.getAddress()=="/1/ShowGui"){
					if(m.getArgAsInt32(0)==1)
						gui.show();
					if(m.getArgAsInt32(0)==0)
						gui.hide();
				}
				//background color for red
				else if(m.getAddress()=="/1/slider/1"){
					//br=m.getArgAsFloat(0)*255;
					//ofBackground(br,bg,bb);
					myColors[0]=m.getArgAsFloat(0);
				}
				//background color for green
				else if(m.getAddress()=="/1/slider/2"){
					//bg=m.getArgAsFloat(0)*255;
					//ofBackground(br,bg,bb);
					myColors[1]=m.getArgAsFloat(0);
				}
				//background color for blue
				else if(m.getAddress()=="/1/slider/3"){
					//	bb=m.getArgAsFloat(0)*255;
					//	ofBackground(br,bg,bb);
					myColors[2]=m.getArgAsFloat(0);
				}
				//toggle button for fullscreen
				else if(m.getAddress()=="/1/FullScreen"){
					if(m.getArgAsInt32(0)==0){
						ofSetFullscreen(false);
					ofShowCursor();} 
					else {
						ofSetFullscreen(true);
					ofHideCursor();}
				}
				//toggle button for redraw boundary
				else if(m.getAddress()=="/1/Window"){
					if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
						keyPressed('w');
				}
				//gravity
				else if (m.getAddress()=="/1/Gravity"){
					//change grabbing to true
					if(m.getArgAsInt32(0)==1)
						bGravity = true;
					//change grabbing to false
					if(m.getArgAsInt32(0)==0)
						bGravity = false;
				}
				//if the accelerometer is on, set the x and y gravity
				else if(m.getAddress()=="/accxyz") {
					bAGravity=true;
					gtimer=ofGetElapsedTimef()+ 1.0f;
					xg = m.getArgAsFloat( 0 )*maxgravity;
					yg = m.getArgAsFloat( 1 )*maxgravity*-1;
				}
				//toggle button for show message
				else if(m.getAddress()=="/1/ShowMsg") {	
					if(m.getArgAsInt32(0)==0){
						bShowMsg=false;
					}
					else
						bShowMsg=true;
				}
				else if(m.getAddress()=="/1/box2dFPS"){
					box2dFPS=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/xg"){
					xg=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/yg"){
					yg=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/gui_mass"){
					gui_mass=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/gui_bounce"){
					gui_bounce=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/gui_friction"){
					gui_friction=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/strength"){
					strength=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/damping"){
					damping=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/minDis"){
					minDis=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/particle_radius"){
					particle_radius=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/boids_limNum"){
					boids_limNum=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/boidsMaxVelocity"){
					boidsMaxVelocity=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/boidsTooCloseDist"){
					boidsTooCloseDist=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/boidsInSightDist"){
					boidsInSightDist=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/boids_adding"){
					if(m.getArgAsInt32(0)==1)
						boids_adding=true;
					else
						boids_adding=false;
				}
				else if(m.getAddress()=="/1/particle_random_radius"){
					if(m.getArgAsInt32(0)==1)
						particle_random_radius=true;
					else
						particle_random_radius=false;
					
				}
				else if(m.getAddress()=="/1/particle_random_color"){
					if(m.getArgAsInt32(0)==1)
						particle_random_color=true;
					else
						particle_random_color=false;
				}
				else if(m.getAddress()=="/1/bUpdatePhysic"){
					if(m.getArgAsInt32(0)==1)
						bUpdatePhysic=true;
					//else
					//	bUpdatePhysic=false;
				}
				else if(m.getAddress()=="/1/FAFED"){
					ofxOscMessage m1;
					m1.setAddress( "/1/FAFED" );//mouse force
					
					
					if(m.getArgAsInt32(0)==0){
						mode=0;
						FAFED=0;
					
					}
					else if(m.getArgAsInt32(0)==1){
						mode='a';
						FAFED=1;
					}
					else if(m.getArgAsInt32(0)==2){
						mode='f';
						FAFED=2;
					}
					else if(m.getArgAsInt32(0)==3){
						mode='s';
						FAFED=3;
					}
					m1.addIntArg(FAFED);
					sender.sendMessage( m1 );
				}
				/*
				else if(m.getAddress()=="/1/FAFED/explode"){
					if(m.getArgAsInt32(0)==1){
						mode='e';
						FAFED=4;
					}	
				}
				 */
				else if(m.getAddress()=="/1/stoptime"){
					if(m.getArgAsInt32(0)==1){
						keyPressed('=');
					}	
				}
				else if(m.getAddress()=="/1/blur"){
					if(m.getArgAsInt32(0)==1){
						//number=ofRandom(0,1000);
						number=blurSlider;
					}	
				}
				else if(m.getAddress()=="/1/blurSlider"){
					blurSlider=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/blurSpeed"){
					blurSpeed=m.getArgAsFloat(0);
				}
				else if(m.getAddress()=="/1/colorRange"){
					colorRange=m.getArgAsFloat(0);
				}
				
				else if(m.getAddress()=="bandstrength") {
					
					int getx= 0;
					if (m.getArgAsFloat(0) > 0)
						getx+=m.getArgAsFloat(0);
					if (m.getArgAsFloat(1) > 0)
						getx+=m.getArgAsFloat(1);
					if (m.getArgAsFloat(2) > 0)
						getx+=m.getArgAsFloat(2);
					
					number= getx/40.0;
					
				}
				else if(m.getAddress()=="attack") {
					keyPressed('=');
					
				}
				
				break;
		}
	}
}
//--------------------------------------------------------------
//checkGravity was used to set the gravity. When gravity is false it will set to zero and when it is true it will set to the xg and yg 
// values that got it from the osc accelerometer
//--------------------------------------------------------------
void testApp::checkGravity(){
	//set gravity to 0 if false
	if(bGravity==false)
		box2d.setGravity(0,0);
	if (bGravity==true)
		box2d.setGravity(xg, yg);
	
	//if accelerometer button is off
	if(gtimer< ofGetElapsedTimef()){
		ofxOscMessage m5;
		m5.setAddress( "/1/Gravity" );
		m5.addIntArg(0);  //gravity set to 0
		sender.sendMessage( m5 );
		bAGravity=false;
		//bGravity=false;
	}
}

void testApp::checkMode(){
	
	switch (FAFED) {
		case 1:
			pBoids->flock();
			pBoids->arrive(target);
			break;
		case 2:
			pBoids->flock();
			pBoids->flee(target);
			
			break;
		case 4:
			pBoids->flock();
			pBoids->explode();
			mode = 0;
			break;
		case 3:
			pBoids->drift();
			break;
		//case 'e':
		//	if (OSCCONTROL) {
		//		for (int i = 0; i < p3DTact.size(); i++) {
		//			boidsemitter(p3DTact[i]->x, p3DTact[i]->y);
		//		}
		//	}
		//	pBoids->drift();
		//	break;
		default:
			pBoids->flock();
			break;
	}
	pBoids->bounce();
	pBoids->update();

		for(int i=0; i<customParticles.size(); i++){
			customParticles[i].addAttractionPoint(pBoids->getBoids()[i]->getPosition().x,pBoids->getBoids()[i]->getPosition().y,strength,pBoids->getInSightDist() );
			customParticles[i].addDamping(damping,damping);
		}

}
void testApp::updatePhysic(){
	for(int i=0; i<customParticles.size(); i++) {
		customParticles[i].circle.density= gui_mass;
		customParticles[i].circle.restitution = gui_bounce;
		customParticles[i].circle.friction= gui_friction;
		//customParticles[i].setRadius(particle_radius);
		
	}	
	
}
				  
//--------------------------------------------------------------
// changeMasterColor() was used for updating the master color after you make changes in the Gui or in the ipod/iphone.
//--------------------------------------------------------------
void testApp::changeMasterColor(){
	for(int i=0; i<customParticles.size(); i++) {
		customParticles[i].masterRed=myColors[0]*255;
		customParticles[i].masterGreen=myColors[1]*255;
		customParticles[i].masterBlue=myColors[2]*255;
	}	
}
//--------------------------------------------------------------
//update() gets called repeatedly. It runs just before draw() so this place is for any updating of variables.
// For example:  for oscemote, if there is changes make on the mouse pad it will check whether it can add boid or not. 
//				If you have enable adding boids then you will add one boid on screen, the point is where you touch on the mouse pad. 
//				If there is nothing change on the mouse pad for 2.5 sec the toggle for mouse force will set to false.
//--------------------------------------------------------------
void testApp::update() {
	if(bmetaball){
		m_vy = new int[ pblobs.size() * ofGetHeight() ];
		m_vx = new int[ pblobs.size() * ofGetWidth() ];
	}
	if(UseOSC){
		if(number>.001)
		{
			//blurSpeed should be( 0 - .99)
			number*=(blurSpeed);
		}
		else
			number=0;
	}
	else{
		if(number>1)
		{
			number*=0.5;
		}
		else
			number=0;
	}
	
	if(stoptime>=1)
	{
		stoptime-=1;
	}
	else
		stoptime=0;

	if(pwidth!=ofGetWidth()){
		blur.setup( ofGetWidth(), ofGetHeight());
	}
//--------------------------------------------------------------
	if(boids_delete){
		deleteBoids();
		boids_delete=false;
	}
	
	if(boids_adding){
		addBoids(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()));
		boids_adding=false;
	}
	while(pBoids->getNumBoids()>boids_limNum)
	{
		deleteBoids();
	}
	
//--------------------------------------------------------------	
	//receive message from OSC
	if (UseOSC) 
		parseOSCMsg();
	
	checkGravity();
	checkFlag();
	changeMasterColor();
	sendOscFlag();
	
	//if stop time end
	if(stoptime<1){
		if(bmetaball){
			metaupdate();
		}
		
		if (bUpdatePhysic){
			updatePhysic();
			bUpdatePhysic=false;
		}
		
		//change parameters for boids
		pBoids->setMaxVelocity(boidsMaxVelocity );
		pBoids->setTooCloseDist(boidsTooCloseDist);
		pBoids->setInSightDist(boidsInSightDist);
		box2d.setFPS(box2dFPS);
		
		//if the width or height is changed, redraw boundary
		if(pwidth!=ofGetWidth()||pheight!=ofGetHeight())
			keyPressed('w');
		
		//if there is nothing changes on the mouse pad for 2.5sec the toggle for mouse force is set to false 
		if (  mtimer < ofGetElapsedTimef() && bmouse==false && UseOSC ){
			bMouseForce=false;
		}
		//if timer is less then elapesed time, clear pboids2
		if ( timer < ofGetElapsedTimef() ){
			pBoids2.clear();
		}
		//mouse force
		//if there is nothing changes on the mouse pad for 2.5sec then it will change the mouse force to false
		if(bMouseForce) {
			mtimer=ofGetElapsedTimef()+ 2.5;
			
			
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
			mode=0;
			for (int i=0;i<customParticles.size();i++){
				pBoids->getBoids()[i]->setPosition(customParticles[i].getPosition().x,customParticles[i].getPosition().y);
				pBoids->getBoids()[i]->setVelocity(customParticles[i].getVelocity().x,customParticles[i].getVelocity().y);
				
				
			}
		}
		//flocking
		if(bFlockings){
			checkMode();
		}
		
		//grabbing
		if (bGrabbing) box2d.enableGrabbing();
		else box2d.disableGrabbing();
		
	
		
		//p_particle_radius=particle_radius;
		toggle1=false;
		pbGrabbing =bGrabbing;
		pbMouseForce = bMouseForce;
		pbFlockings = bFlockings;
		pbAGravity =bAGravity;
		pbGravity = bGravity;
		pwidth=ofGetWidth();
		pheight=ofGetHeight();
		
		box2d.update();	
	}
	

}
//--------------------------------------------------------------
// draw() was used to draw all the 2d objects on the screen.
// It will show the box2d, the custom particles, the string messages, and gui.
//--------------------------------------------------------------
void testApp::draw() {
	
	blur.setBlurParams(4, number);
	blur.beginRender();
		
	if(!bmetaball){
	for(int i=0; i<customParticles.size(); i++) {
		//if(particle_random_radius)
			//customParticles[i].draw1(particle_random_color,colorRange);
		//parameters: random color , color range: 0-same color 1-more random
		customParticles[i].draw1(true,colorRange);
		
		//else
		//	customParticles[i].draw2(particle_radius ,particle_random_color);
	}
		
	}
	else{
		
		blur.setBlurParams(4, 2);
		
		
		
		tex.loadData( texPixels, BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
		//glPushMatrix();
		tex.draw( 0, 0, ofGetWidth(),ofGetHeight());
		//glPopMatrix();
		int xnum=pblobs.size();
		ofDrawBitmapString(	ofToString(ofGetFrameRate()), 20, 10);	
		ofDrawBitmapString(	ofToString(xnum), 20, 40);	
		//if(pBoids->getNumBoids()>0){
		//ofDrawBitmapString(ofToString(pBoids->getBoids()[0]->getPosition().x), 20, 60);
			//ofDrawBitmapString(ofToString(pBoids->getNumBoids()),20,60);
		//}
		
	}
	
	box2d.draw();
	blur.endRender();
	blur.draw(0, 0, ofGetWidth(), ofGetHeight(), true);
	
	
	//stores the mouse position 
	px = mouseX;
	py = mouseY;

	if(bShowMsg){
		ofSetColor(255, 255, 255);
		string info = "";
		info += "listening for osc messages on port" + ofToString( PORT )+" send on: "+ ofToString( SPORT )+"\n";
		info += "Press [f] to toggle Mouse Force ["+ofToString(bMouseForce)+"]\n"; 
		info += "Press [b] to toggle flockings   ["+ofToString(bFlockings)+"]\n";
		info += "Press [h] to toggle gravity     ["+ofToString(bGravity)+"]\n";
		info += "Press [g] to toggle grabbing    ["+ofToString(bGrabbing)+"]\n";
		info += "Press [z] for adding custom particle\n";
		info += "Press [q] for delete particle\n";
		info += "Press [m] to show this message\n";
		info += "Press [space bar] to show the Gui\n";
		info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
		info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
	
		ofDrawBitmapString(info, 30, 30);
	}
 
	gui.draw();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	if(key == 'a'){
		if (bmetaball==false){
			for(int a=0;a<pBoids->getNumBoids() ;a++){
				addblob();
			}
			
			bmetaball=true;
		}
		else if(bmetaball==true)
		{	
			pblobs.clear();
			bmetaball=false;
		}
	}
	if(key == 'f'){
		bMouseForce = !bMouseForce;
	}
	if(key=='b'){ 
		bFlockings = !bFlockings;
	}	
	if(key=='h'){
		bGravity=!bGravity;
	}
	if(key=='g'){
		bGrabbing= !bGrabbing;
	}
	if(key == 'z') {
		addBoids(mouseX,mouseY);
		if(bmetaball){
			m_vy = new int[ (pblobs.size()+1) * ofGetHeight() ];
			m_vx = new int[ (pblobs.size()+1) * ofGetWidth() ];
		
		addblob();
	}
	}	
	if(key =='q'){
		deleteBoids();
		if(bmetaball){
			pblobs.clear();	
			for(int a=0;a<pBoids->getNumBoids() ;a++){
				addblob();
			}
		}
	}
	if(key =='w'){						//create the window boarder
		box2d.getWorld()->DestroyBody(box2d.ground);
		box2d.createBounds();
	}
	if(key=='m'){
		bShowMsg=!bShowMsg;
	}
	if(key == 't') {
		ofToggleFullscreen();
	}
	if(key==' ')gui.toggleDraw();
	
	if(key=='=')	{
		stoptime=2;
	}
	if(key=='[')gui.prevPage();
	if(key==']')gui.nextPage();
	
	if(key=='p')gui.nextPageWithBlank();
}
//--------------------------------------------------------------
void testApp::keyReleased(int key) {	
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
		//number=x;
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {	
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	if(!UseOSC)
	number=x;
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}
//--------------------------------------------------------------
void testApp::resized(int w, int h){
}
