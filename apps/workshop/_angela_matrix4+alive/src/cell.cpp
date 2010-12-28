/*
 *  cell.cpp
 *  openFrameworks
 *
 *  Created by LEDAProgrammer on 14/10/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"
#include "cell.h"
Cells::Cells(){
	alive=false;
	numItems=0;
	red=0;
	blue=0;
	green=0;
	dx=0;
	dy=0;
	nextx=0;
	nexty=0;
	cellcolor=1;
	counter=0;
	dspeed=1;
}
void Cells::setCells(int i,int j){
	col=i;
	row=j;
	dspeed=5;
	//red=ofRandom(100, 255);
	//green=ofRandom(100, 255);
	//blue=ofRandom(100, 255);
	red=255;
	green=255;
	blue=255;
	randomdirection();
	randomMode();
	
	counter=0;
	
}
void Cells::resetcounter(){
	counter=0;
}

void Cells::randomMode(){
	int temp3;
	temp3=ofRandom(0,900);
	if(temp3<300) cellcolor=1;
	else if(temp3<600) cellcolor=2;
	else cellcolor=3;
}
	
void Cells::randomdirection(){
	int temp1,temp2;
	
	//set random dx
	temp1=ofRandom(0,900);
	if(temp1<300) dx=1;
	else if(temp1<600) dx=0;
	else dx=-1;
	//set nextx
	nextx=col+dx;
	
	//set random dy to -1 or 1 if dx =0
	temp2=ofRandom(0,900);
	if(dx==0){
		if(temp2<450) dy=-1;
		else dy=1;
	}
	//or else dy=0,-1,1
	else {
		if(temp2<300) dy=1;
		else if(temp2<600) dy=0;
		else dy=-1;
	}
	//set nexty
	nexty=row+dy;
}


void Cells::setcol(int pCol){
	col=pCol;
}
void Cells::setrow(int pRow){
	row=pRow;
}

int Cells::getnextx(){
	nextx=col+dx;
	return nextx;
}

int Cells::getnexty(){
	nexty=row+dy;
	return nexty;
}
void Cells::setnextx(int pX){
	nextx=pX;
}
void Cells::setnexty(int pY){
	nexty=pY;
}
int Cells::getXDirection(){
	return dx;
}
int Cells::getYDirection(){
	return dy;
}
void Cells::setXDirection(int pdx){
	dx=pdx;
}
void Cells::setYDirection(int pdy){
	dy=pdy;
}
void Cells::draw(int width){
	if(alive)
	{
		
		ofSetColor(	red,green,blue);
		ofCircle(width/windowcol/2+col*width/windowcol, width/windowcol/2+row*width/windowcol,width/windowcol/2 );
		
		/*
		glPushMatrix();
		glTranslatef(width/windowcol/2+col*width/windowcol,width/windowcol/2+row*width/windowcol, 0);
		// ofCircle(0,0,width/windowcol/2);
		 glutSolidSphere(10,10,10);
		glPopMatrix();
		 */
		
	}
}
void Cells::addCrashes(int mode){
	//show red
	if (mode==1){
		if(blue<10||green<10)
			alive=false;
		else{
			blue-=dspeed;
			green-=dspeed;
		}
	}
	//show green
	if(mode==2){
		if(blue<10||red<10)
			alive=false;
		else{
			blue-=dspeed;
			red-=dspeed;
		}
	}
	//show blue
	if(mode==3){
		if(red<10||green<10)
			alive=false;
		else{
			red-=dspeed;
			green-=dspeed;
		}
	}
}
	

