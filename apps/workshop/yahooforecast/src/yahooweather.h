/*
 *  yahooweather.h
 *  emptyExample
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */
#ifndef YAHOOWEATHER
#define YAHOOWEATHER

#include "ofxXmlExtended.h"
#include "ofxHttpEvents.h"
#include <iostream>

class yahooweather: public ofxHttpEventListener{
	public:
	yahooweather();
	void seturl(string name);
	void setID(string name);
	void setunit(bool a);
	void newResponse(ofxHttpResponse &response);
	void updateweather();
	void draw();

	ofxXmlExtended XML;
	bool unit;
	
	string responseStr;
	string title,width,height,link; 
	string item_title,item_geolat,item_geolong,item_link,item_pubDate;
	string con_text,con_code,con_temp,con_date;
	string description;
	string fore_day[5],fore_date[5],fore_low[5],fore_high[5],fore_text[5],fore_code[5];
	string ast_rise,ast_set;
	string atm_hum,atm_vis,atm_pre,atm_ris;
	float humidity,visibility,pressure;
	string rising;
	string myurl;
};
#endif