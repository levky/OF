/*
 *  yahoofinance.h
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */
#ifndef YAHOOFINANCE
#define YAHOOFINANCE

#include "ofxHttpEvents.h"

class yahoofinance: public ofxHttpEventListener{
	public:
	yahoofinance();
	void seturl(string name);
	void setID(string name);
	void newResponse(ofxHttpResponse &response);
	void updatefinance();
	void draw();

	string responseStr;
	string name;
	string last,date,time,change,open,high,daylow,volume;
	float lastf,changef,openf,highf, daylowf;
	int volumei;
	string myurl;
};
#endif