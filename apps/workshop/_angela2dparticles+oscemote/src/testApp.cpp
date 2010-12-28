
#include "testApp.h"
#include "ofxBox2dBaseShape.h"



//--------------------------------------------------------------
testApp::testApp(){
}



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
	bAddBoids = true; //for oscemote
	bAGravity=false;

	
	pbGrabbing =false;
	pbMouseForce = false;
	pbFlockings = false;
	pbAGravity=false;
	bShowMsg=true;
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
//box2d.disableGrabbing();
	box2d.registerGrabbing();
	box2d.createBounds();
	
	pBoids=new boids(0);
	pBoids->setMaxVelocity(10);
	pBoids->setTooCloseDist(45.0);
	pBoids->setInSightDist(75.0);
	
	
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
	gui.show();
	ofxOscMessage m1;
	m1.setAddress( "/1/A1" );
	m1.addIntArg(0);
	sender.sendMessage( m1 );
	ofxOscMessage m2;
	m2.setAddress( "/1/A2" );
	m2.addIntArg(0);
	sender.sendMessage( m2 );
	ofxOscMessage m3;
	m3.setAddress( "/1/gravity" );
	m3.addIntArg(0);
	sender.sendMessage( m3 );
	ofxOscMessage m4;
	m4.setAddress( "/1/B3" );
	m4.addIntArg(1);
	sender.sendMessage( m4 );
	ofxOscMessage m5;
	m5.setAddress( "/1/fullscreen" );
	m5.addIntArg(0);
	sender.sendMessage( m5 );
	ofxOscMessage m6;
	m6.setAddress( "/1/E1" );
	m6.addIntArg(1);
	sender.sendMessage( m6 );
	ofxOscMessage m7;
	m7.setAddress("/1/ShowMsg");
	m7.addIntArg(1);
	sender.sendMessage(m7);

}

//--------------------------------------------------------------
void testApp::checkFlag(){
	if(pbMouseForce!=bMouseForce){
		if(bMouseForce){
			//bGrabbing=false;
			bMouseForce=true;
			bFlockings=false;
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
	if(pbFlockings!=bFlockings){
		if(bFlockings){
			//bGrabbing=false;
			bMouseForce=false;
			bFlockings=true;
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

void testApp::addBoids(float mouseX, float mouseY){
	float r = ofRandom(3, 10);		// a random radius 4px - 20px
	CustomParticle p;
	p.setPhysics(3, 0.53, 0.31);
	p.setup(box2d.getWorld(), mouseX, mouseY, r);
	p.color.r = ofRandom(20, 100);
	p.color.g = ofRandom(20, 255);;
	p.color.b = ofRandom(150, 255);
	customParticles.push_back(p);
	pBoids->addBoid();
	
}	

void testApp::deleteBoids(){
	if(customParticles.size()>0){
		customParticles[customParticles.size()-1].destroyShape();
		customParticles.pop_back();
		pBoids->subtractBoid();
	}
}

	

//--------------------------------------------------------------
void testApp::update() {

	if(pwidth!=ofGetWidth()||pheight!=ofGetHeight())
		keyPressed('w');
	
	
	if(bAGravity==true){
	ofxOscMessage m5;
	m5.setAddress( "/1/gravity" );
	m5.addIntArg(0);
	sender.sendMessage( m5 );
	}
	bAGravity=false;
	if (  mtimer < ofGetElapsedTimef()&&bmouse==false ){
		bMouseForce=false;
	}
	if ( timer < ofGetElapsedTimef() ){
		pBoids2.clear();
	}
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		if ( m.getAddress() == "/tuio/2Dcur" )
		{	
			if(m.getArgAsString( 0 )=="set"){
				bmouse=true;
				timer=ofGetElapsedTimef()+ 1.0f;
				
				//add boids
				if(bAddBoids  ){
				
					mouseX=m.getArgAsFloat( 2 )*ofGetWidth();
					mouseY=m.getArgAsFloat( 3 )*ofGetHeight();
					addBoids(mouseX,mouseY);
					
				}
				//if not add boids
				else{
					
					if(pBoids2.size() < m.getArgAsInt32(1)){
						pBoids2.push_back(new boid());
						pBoids2[m.getArgAsInt32(1)-1]->setPosition(m.getArgAsFloat( 2 )*ofGetWidth(), m.getArgAsFloat( 3 )*ofGetHeight());
					}
			
					else{
						pBoids2[m.getArgAsInt32(1)-1]->setPosition(m.getArgAsFloat( 2 )*ofGetWidth(), m.getArgAsFloat( 3 )*ofGetHeight());
					}	

				}
			}//finish set
			
			if(m.getArgAsString( 0 )=="alive"){
				if(m.getNumArgs()>1){
					mtimer=ofGetElapsedTimef()+ 2.5;
					bmouse=true;
				}
				else {
					mtimer=ofGetElapsedTimef()+ 2.5;
					bmouse=false;
				}
			}
		}
		if ( m.getAddress() == "/1/touchosc/set" )
		{	
			
				//bmouse=true;
				//timer=ofGetElapsedTimef()+ 1.0f;
				
				//add boids
				if(bAddBoids && pBoids->getNumBoids()<MAXBOIDS){
					mouseX=m.getArgAsFloat( 0)*ofGetWidth();
					mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
					addBoids(mouseX,mouseY);
				}
				//if not add boids
				else{
					
					mouseX=m.getArgAsFloat( 0)*ofGetWidth();
					mouseY=m.getArgAsFloat( 1 )*ofGetHeight();
					
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
		else if (m.getAddress()=="/button/A1"){
			timer=ofGetElapsedTimef()+ 5.0f;
			mtimer=ofGetElapsedTimef()+ 5.0f;
			
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
			bMouseForce = !bMouseForce;
			
		}
		else if (m.getAddress()=="/button/A2"){
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
			bFlockings = !bFlockings;
		}
		else if (m.getAddress()=="/button/B1"){
			if(m.getArgAsInt32(0)==1)
			bGrabbing = !bGrabbing;
		}
		else if (m.getAddress()=="/button/B2"){
			deleteBoids();
		}
		else if(m.getAddress()=="/button/B3"){
			if(m.getArgAsInt32(0)==1)
			bAddBoids = !bAddBoids;
		}
		else if (m.getAddress()=="/button/E1"){
			if(m.getArgAsInt32(0)==1)
			gui.toggleDraw();
		}
		else if (m.getAddress()=="/acceleration/xyz"){
			bMouseForce=false;
			bFlockings=false;
			bAGravity=true;
			float xg = m.getArgAsFloat( 0 )*maxgravity;
			float yg = m.getArgAsFloat( 1 )*maxgravity*-1;
			box2d.setGravity(xg, yg);
		}
		else if (m.getAddress()=="/accelerometer"){
			if(m.getArgAsInt32(0)==0)
				bAGravity=false;
			else
				bAGravity=true;
		}
		//TouchOSC
		//MouseForce
		else if (m.getAddress()=="/1/A1"){
			box2d.setGravity(0,0);
			timer=ofGetElapsedTimef()+ 5.0f;
			mtimer=ofGetElapsedTimef()+ 5.0f;
			
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
				bMouseForce = true;
			else if(m.getArgAsInt32(0)==0 && bMouseForce==true && bAGravity==false)
				bMouseForce = false;
		}
		//Flocking
		else if (m.getAddress()=="/1/A2"){
			box2d.setGravity(0,0);
			if(m.getArgAsInt32(0)==1 && bAGravity==false)
				bFlockings = true;
			if(m.getArgAsInt32(0)==0 && bAGravity==false)
				bFlockings = false;
		}
		else if (m.getAddress()=="/1/B1"){
			if(m.getArgAsInt32(0)==1)
				bGrabbing = true;
			if(m.getArgAsInt32(0)==0)
				bGrabbing = false;
		}
		else if (m.getAddress()=="/1/B2"){
			if(m.getArgAsInt32(0)==1)
				deleteBoids();
		}
		else if(m.getAddress()=="/1/B3"){
			if(m.getArgAsInt32(0)==1)
				bAddBoids = true;
			if(m.getArgAsInt32(0)==0)
				bAddBoids = false;
			
		}
		else if (m.getAddress()=="/1/E1"){
			if(m.getArgAsInt32(0)==1)
				gui.toggleDraw();
			if(m.getArgAsInt32(0)==0)
				gui.toggleDraw();
		}
		else if(m.getAddress()=="/1/slider/1"){
			br=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[0]=m.getArgAsFloat(0);
		}
		else if(m.getAddress()=="/1/slider/2"){
			bg=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[1]=m.getArgAsFloat(0);
		}
		else if(m.getAddress()=="/1/slider/3"){
			bb=m.getArgAsFloat(0)*255;
			ofBackground(br,bg,bb);
			myColors[2]=m.getArgAsFloat(0);
		}
		else if(m.getAddress()=="/1/fullscreen"){
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
			keyPressed('t');

		}
		else if(m.getAddress()=="/1/window"){
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
			keyPressed('w');
		}
		else if(m.getAddress()=="/accxyz") {

			bMouseForce=false;
			bFlockings=false;
			bAGravity=true;
			float xg = m.getArgAsFloat( 0 )*maxgravity;
			float yg = m.getArgAsFloat( 1 )*maxgravity*-1;
			box2d.setGravity(xg, yg);
		}
		else if(m.getAddress()=="/1/ShowMsg") {	
			if(m.getArgAsInt32(0)==0||m.getArgAsInt32(0)==1)
				keyPressed('m');
		}
			
	}
			
	checkFlag();
	box2d.update();
	if(bMouseForce) {
		mtimer=ofGetElapsedTimef()+ 2.5;
		float strength = 8.0f;
		float damping  = 0.7f;
		float minDis   = 100;
		if(pBoids2.size()>0){
			for(int i=0; i<customParticles.size(); i++) {
				customParticles[i].addAttractionPoint(pBoids2[i % pBoids2.size()]->getPosition().x, pBoids2[i % pBoids2.size()]->getPosition().y, strength, minDis);
				customParticles[i].addDamping(damping, damping);
			}
		}
		else{
			for(int i=0; i<customParticles.size(); i++) {
				customParticles[i].addAttractionPoint(mouseX, mouseY, strength, minDis);
				customParticles[i].addDamping(damping, damping);
			}
		}
	}
	if(!bFlockings){
			for (int i=0;i<customParticles.size();i++){
				pBoids->getBoids()[i]->setPosition(customParticles[i].getPosition().x,customParticles[i].getPosition().y);
				pBoids->getBoids()[i]->setVelocity(customParticles[i].getVelocity().x,customParticles[i].getVelocity().y);
			}
	}
	
			
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

