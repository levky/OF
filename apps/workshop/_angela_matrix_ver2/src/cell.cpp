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
//set cell 
void Cells::setCells(int i,int j){
	col=i;
	row=j;
	dspeed=5;
	red=255;
	green=255;
	blue=255;
	randomdirection();
	randomMode();
	counter=0;
}
//set counter to zero
void Cells::resetcounter(){
	counter=0;
}
//randomly pick a color for the cell(red,green or blue)
void Cells::randomMode(){
	int temp3;
	temp3=ofRandom(0,900);
	if(temp3<300) cellcolor=1;
	else if(temp3<600) cellcolor=2;
	else cellcolor=3;
}
//randomly set a direction for the cell
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

//set column
void Cells::setcol(int pCol){
	col=pCol;
}
//set row
void Cells::setrow(int pRow){
	row=pRow;
}
//get the next position x
int Cells::getnextx(){
	nextx=col+dx;
	return nextx;
}
//get the next position y
int Cells::getnexty(){
	nexty=row+dy;
	return nexty;
}
//set the next position x
void Cells::setnextx(int pX){
	nextx=pX;
}
//set the next position y
void Cells::setnexty(int pY){
	nexty=pY;
}
//get direction x
int Cells::getXDirection(){
	return dx;
}
//get direction y
int Cells::getYDirection(){
	return dy;
}
//set direction x
void Cells::setXDirection(int pdx){
	dx=pdx;
}
//set direcion y
void Cells::setYDirection(int pdy){
	dy=pdy;
}
//draw all cell that is alive
void Cells::draw(int width,int height){
	if(alive)
	{
		
		ofSetColor(	red,green,blue);
		//ofCircle( );
		ofEllipse(width/windowcol/2+col*width/windowcol, height/windowrow/2+row*height/windowrow,width/windowcol,height/windowrow);
		/*
		glPushMatrix();
		glTranslatef(width/windowcol/2+col*width/windowcol,width/windowcol/2+row*width/windowcol, 0);
		// ofCircle(0,0,width/windowcol/2);
		 glutSolidSphere(10,10,10);
		glPopMatrix();
		 */
		
	}
}
//subtract the deadspeed of each cell(cellcolor/mode 1=red, 2=green, 3=blue)
void Cells::addCrashes(int mode){
	//for red
	if (mode==1){
		if(blue<10||green<10)
			alive=false;
		else{
			blue-=dspeed;
			green-=dspeed;
		}
	}
	//for green
	if(mode==2){
		if(blue<10||red<10)
			alive=false;
		else{
			blue-=dspeed;
			red-=dspeed;
		}
	}
	//for blue
	if(mode==3){
		if(red<10||green<10)
			alive=false;
		else{
			red-=dspeed;
			green-=dspeed;
		}
	}
}
	

