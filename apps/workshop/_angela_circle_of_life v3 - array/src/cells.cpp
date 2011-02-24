/*
 *  cells.cpp
 *  openFrameworks
 *
 *  Created by LEDAProgrammer on 15/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */




Cells();
void cells::update(){
}
void updateLife()
void updatePostion()
void draw()
void isExisted();
vector<ofxCell*> getCells()
void setMaxRingNum(int fMaxRing)
void addCell()
void addCell(int a, int b)
void resetneighbor()
void changedirection(int x)
void changecondition(int i)
int maxRingNum


void cells::resetneighbor(){
	for(int i=0;i<pCircle.size();i++){
		pCircle[i]->neighbor=0;
	}
}
//--------------------------------------------------------------
// The checkneighbor() function will return true if there is any neighbor. 
//
// The parameter: 
//
// return: a boolean(true or false)
//--------------------------------------------------------------
bool cells::checkneighbor(int i, int j){ 
	//if the neighbor position is out of range then return false
	if(pCircle[i]->getNextRing()<0 ||pCircle[i]->getNextRing() > maxRingNum) return false;
	//if both cell is alive 
	
	//if the neighbor goes to the same spot with the current cell
	if( pCircle[i]->getNextRing()==pCircle[j]->getNextRing() && pCircle[i]->getNextStep()=pCircle[j]->getNextStep()){
		return true;
	}
	//if there is a neighbor wants to go to the current cell position
	if(pCircle[i]->getNextRing()==pCircle[j]->ring && pCircle[i]->getNextStep()==pCircle[j]->steps){
		return true;
	}
	//else
	return false;
}

//--------------------------------------------------------------
//updateLife() was used when current cell has neighbors it will set the number of neighors in numItems
//--------------------------------------------------------------
void cells::updateLife(){
	int count;
	for(int i=0;i<pCircle.size();i++){
		count=0;
		for(int j=0;j<pCircle.size();j++){
			if(i!=j){
				if(checkneighbor(i,j)){
					count++;
				}
			}
		}
		pCircle[i]->neighbor=count;
	}
}

//--------------------------------------------------------------
// changedirection() was used for the cell to change direction.
// The parameter: the index number of myCircle
//--------------------------------------------------------------	
void cells::changedirection(int i){

	if(pCircle[i]->direction==1){
		pCircle[i]->direction=3;
	}
	
	else if(pCircl]e[i]->direction==3){
		pCircle[i]->direction=1;
	}
}


void cells::changecondition(int i){
	if(pyCircle[i].condition==0){
		pCircle[i]->condition=1;
	}
	else{
		pCircle[i]->condition=0;
	}
}
/*
 //--------------------------------------------------------------
 //updatePosition() was used for updating the cells position. When the cell has any neighbors, it will change direction.
 // When there is no cell that is alive on the next position then it will update the cell position.
 // When the cell hit the border, then it will change direction.
 //--------------------------------------------------------------
 void testApp::updatePosition(){
 
 //create a temp circle
 tempCircle.resize(myCircle.size());
 
 //if the cell has any neighbors then change direction 
 for(int i=0;i<myCircle.size();i++){
 if(pCircle[i]->neighbor>0||pCircle[i]->getNextRing()<0||pCircle[i]->getNextRing()>maxRingNum){
 changedirection(i);
 }
 }
 
 for(int i=0;i<myCircle.size();i++){
 //if the next position is in range
 if(pCircle[i]->getNextRing()>=0 && pCircle[i]->getNextRing() < maxRingNum){
 //change the position if the next position is empty	
 if(!tempisExisted(pCircle[i]->getNextRing(), pCircle[i]->getNextStep())){
 tempCircle[i].setCell(pCircle[i]->getNextRing(), pCircle[i]->getNextStep());
 tempCircle[i].setMaxRing(maxRingNum);
 tempCircle[i].direction=pCircle[i]->direction;
 tempCircle[i].setColor(pCircle[i]->color.r,pCircle[i]->color.g,pCircle[i]->color.b);
 
 }
 
 //position unchange
 else{
 changedirection(i);
 tempCircle[i]=myCircle[i];
 }
 
 }
 //out of the ring ; nextring<0 and nextring< maxRingNum
 else{
 changedirection(i);
 tempCircle[i]=myCircle[i];
 }
 }
 
 for(int i=0; i<myCircle.size();i++){
 pCircle[i]->setCell(tempCircle[i].ring,tempCircle[i].steps);
 pCircle[i]->direction=tempCircle[i].direction;
 pCircle[i]->color=tempCircle[i].color;
 }
 }	
 */
void cell::updatePosition2(){
	//create a temp circle
	//tempCircle.resize(myCircle.size());
	
	//if the cell has any neighbors then change direction 
	for(int i=0;i<pCircle.size();i++){
		if(pCircle[i]->neighbor>0||pCircle[i]->ring<0||pCircle[i]->ring>maxRingNum){
			pCircle[i]->numOfHit++;
			
			if(pCircle[i]->condition==0){
				if(pCircle[i]->numOfHit%5==0 && pCircle[i]->numOfHit%7==0){
					changedirection(i);
				}
				else if(pCircle[i]->numOfHit%5==0){
					pCircle[i]->increasering();
				}
				else if(pCircle[i]->numOfHit%7==0){
					pCircle[i]->decreasering();
				}
				else{
					changedirection(i);
				}
			}
			
			else if(pCircle[i]->condition==1){
				if(pCircle[i]->numOfHit%5==0 && pCircle[i]->numOfHit%7==0){
					changedirection(i);
				}
				else if(pCircle[i]->numOfHit%5==0){
					pCircle[i]->increasering();
				}
				else if(pCircle[i]->numOfHit%7==0){
					pCircle[i]->decreasering();
				}
				else{
					changedirection(i);
				}
			}
		}
	}
	
	for(int i=0;i<myCircle.size();i++){
		//if the next position is in range
		if(pCircle[i]->ring>=0 && pCircle[i]->ring < maxRingNum){
			//change the position if the next position is empty	
			if(!tempisExisted(pCircle[i]->getNextRing(), pCircle[i]->getNextStep())){
				tempCircle[i].setCell(pCircle[i]->getNextRing(), pCircle[i]->getNextStep());
				tempCircle[i].setMaxRing(maxRingNum);
				tempCircle[i].direction=pCircle[i]->direction;
				tempCircle[i].setColor(pCircle[i]->color.r,pCircle[i]->color.g,pCircle[i]->color.b);
				tempCircle[i].condition=pCircle[i]->condition;
				tempCircle[i].numOfHit=pCircle[i]->numOfHit;
			}
			
			//position unchange direction
			else{
				changedirection(i);
				tempCircle[i].setCell(pCircle[i]->ring, pCircle[i]->steps);
				tempCircle[i].setMaxRing(maxRingNum);
				tempCircle[i].direction=pCircle[i]->direction;
				tempCircle[i].setColor(pCircle[i]->color.r,pCircle[i]->color.g,pCircle[i]->color.b);
				tempCircle[i].condition=pCircle[i]->condition;
				tempCircle[i].numOfHit=pCircle[i]->numOfHit;
				
			}
			
		}
		//out of the ring ; nextring<0 and nextring< maxRingNum
		else{
			
			if(pCircle[i]->ring<0){
				pCircle[i]->increasering();
				pCircle[i]->condition=0;
			}
			else{
				pCircle[i]->decreasering();
				pCircle[i]->condition=1;
			}
			
			//changecondition(i);
			tempCircle[i].setCell(pCircle[i]->ring, pCircle[i]->steps);
			tempCircle[i].setMaxRing(maxRingNum);
			tempCircle[i].direction=pCircle[i]->direction;
			tempCircle[i].setColor(pCircle[i]->color.r,pCircle[i]->color.g,pCircle[i]->color.b);
			tempCircle[i].condition=pCircle[i]->condition;
			tempCircle[i].numOfHit=pCircle[i]->numOfHit;
		}
	}
	
	for(int i=0; i<myCircle.size();i++){
		pCircle[i]->setCell(tempCircle[i].ring,tempCircle[i].steps);
		pCircle[i]->direction=tempCircle[i].direction;
		pCircle[i]->color=tempCircle[i].color;
	}
	tempCircle.erase(tempCircle.begin(),tempCircle.end()); 
}
bool testApp::tempisExisted(int a, int b){
	
	bool temp=false;
	for(int i=0;i<tempCircle.size();i++){
		if(tempCircle[i].ring==a && tempCircle[i].steps==b){
			temp= true;
			return temp;
		}
	}
	return temp;
}


bool testApp::isExisted(int a,int b){
	bool temp=false;
	for(int i=0;i<myCircle.size();i++){
		if(pCircle[i]->ring==a && pCircle[i]->steps==b){
			temp= true;
			return temp;
		}
	}
	return temp;
	
}

//--------------------------------------------------------------
//addNewCell() was used for adding a new cell into the board.
// It will ramdomly pick empty cell in the board and add a new cell into it.
//--------------------------------------------------------------
void testApp::addNewCell(){
	
	int a,b,totb;// a=ring b=steps
	a=ofRandom(0,maxRingNum);
	totb = ceil(PI*(float)a*ringSize/(float)( circle_radius ));
	b=ofRandom(0,totb);
	bool checkalive=true;
	while(checkalive ){
		if (isExisted(a,b)){
			a=ofRandom(0,maxRingNum);	
			totb = ceil(PI*(float)a*ringSize/(float)( circle_radius ));
			b=ofRandom(0,totb);
		}
		else{
			ofxCell temp;
			temp.setCell(a, b);
			temp.setMaxRing(maxRingNum);
			temp.randomdirection();
			temp.condition=0;
			temp.numOfHit=0;
			temp.setColor(ofRandom(0,255),ofRandom(0,0),ofRandom(0,255));
			myCircle.push_back(temp);
			checkalive=false;
		}
	}
	
}
