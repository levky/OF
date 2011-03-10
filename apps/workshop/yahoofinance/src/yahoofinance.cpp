/*
 *  yahoofinance.cpp
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */

#include "yahoofinance.h"


//--------------------------------------------------------------
//constructor
//--------------------------------------------------------------
yahoofinance::yahoofinance(){
	
}
//--------------------------------------------------------------
// setID() was used for setting for the yahoo finance csv with the parameter ID number
// parameter: a string ID number
//--------------------------------------------------------------
void yahoofinance::setID(string quote){
	myurl="http://download.finance.yahoo.com/d/quotes.csv?s=";
	myurl.append(quote);
	myurl.append("&f=sl1d1c1ohgv");
	
}

//--------------------------------------------------------------
// seturl() was used for setting the url for the Yahoo Finance csv
// parameter: a string of the rss/xml
//--------------------------------------------------------------
void yahoofinance::seturl(string url){
	
	myurl=url;
}

//--------------------------------------------------------------
// newResponse() was used for updating the variables when there is a new HTTP request
// parameter: ofxHttpResponse
//--------------------------------------------------------------
void yahoofinance::newResponse(ofxHttpResponse &response) {

	string 	str=response.responseBody;
	vector<string> tokens;
	
	size_t p0 = 0, p1 = string::npos;
	
	while(p0 != string::npos)
	{
		p1 = str.find_first_of(",", p0);
		if(p1 != p0)
		{	
			string token = str.substr(p0, p1 - p0);
			if( token.substr(0,1)=="\""){
				token=token.substr(1,token.size()-2);
			}
			tokens.push_back(token);
			
		}
		p0 = str.find_first_not_of(",", p1);
	}

	int i=0;
	name=tokens[i];
	i++;
	last=tokens[i];	
	lastf=atof(last.c_str());
	i++;
	date=tokens[i];
	i++;
	change=tokens[i];
	changef=atof(change.c_str());
	i++;
	open=tokens[i];
	openf=atof(open.c_str());
	i++;
	high=tokens[i];
	highf=atof(high.c_str());
	i++;
	daylow=tokens[i];
	daylowf=atof(daylow.c_str());
	i++;
	volume=tokens[i];
	volumei=atoi(volume.c_str());
}

//--------------------------------------------------------------
// updatefinance() was used for getting the updated url file
//--------------------------------------------------------------
void yahoofinance::updatefinance(){
	ofxHttpUtil.addUrl( myurl );
	ofxHttpEvents.addListener(this);				
}
//--------------------------------------------------------------
// draw () was used for showing the informations that we get for the csv
//--------------------------------------------------------------
void yahoofinance::draw(){
	responseStr="";
	responseStr+="\n";
	responseStr+=name;
	responseStr+="\n";
	responseStr+="\nLast: ";
	responseStr+=last;
	responseStr+="\nDate: ";
	responseStr+=date;
	responseStr+="\nChange: ";
	responseStr+=change;
	responseStr+="\nOpen: ";
	responseStr+=open;
	responseStr+="\nDay High: ";
	responseStr+=high;
	responseStr+="\nDay Low: ";
	responseStr+=daylow;
	responseStr+="\nVolume: ";
	responseStr+=volume;
	
	
	
	
	ofDrawBitmapString(responseStr, 20, 60);
}
