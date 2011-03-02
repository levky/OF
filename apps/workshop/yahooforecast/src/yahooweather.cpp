/*
 *  yahooweather.cpp
 *  emptyExample
 *
 *  Created by Angela Chim
 *  Created: March 2011
 *
 */

#include "yahooweather.h"


//--------------------------------------------------------------
//constructor
//--------------------------------------------------------------
yahooweather::yahooweather(){
	unit=true;
}
//--------------------------------------------------------------
// setID() was used for setting for the yahoo Weather RSS feed with the parameter ID number
// parameter: a string ID number
//--------------------------------------------------------------
void yahooweather::setID(string name){
	myurl="http://weather.yahooapis.com/forecastrss?w=";
	myurl.append(name);
	if(unit){
		myurl.append("&u=c");
	}
}
//--------------------------------------------------------------
// setunit() was used for setting the unit to celsius or Fahrenheit
// suggest that setunit should called before setID
// parameter: a bool variable (false =Fahrenheit , true=Celsius)
//--------------------------------------------------------------
void yahooweather::setunit(bool a){
	unit=a;
}

//--------------------------------------------------------------
// seturl() was used for setting the url for the Yahoo Weather RSS feed
// parameter: a string of the rss/xml
//--------------------------------------------------------------
void yahooweather::seturl(string name){
	
	myurl=name;
}

//--------------------------------------------------------------
// newResponse() was used for updating the variables when there is a new HTTP request
// parameter: ofxHttpResponse
//--------------------------------------------------------------
void yahooweather::newResponse(ofxHttpResponse &response) {
	
	XML.loadFromBuffer(response.responseBody); // parse string
    XML.pushTag("rss"); // change relative root to rss
	XML.pushTag("channel");
	
	title=XML.getValue("title", "", 0);
	link=XML.getValue("link", "", 0);
	
	atm_hum=XML.getAttribute("yweather:atmosphere","humidity","empty",0);//code 34
	atm_vis=XML.getAttribute("yweather:atmosphere","visibility","empty",0);
	atm_pre=XML.getAttribute("yweather:atmosphere","pressure","empty",0);
	atm_ris=XML.getAttribute("yweather:atmosphere","rising","empty",0);
	ast_rise=XML.getAttribute("yweather:astronomy","sunrise","empty",0);
	ast_set=XML.getAttribute("yweather:astronomy","sunset","empty",0);
	
	humidity = atof(atm_hum.c_str());
	visibility = atof(atm_vis.c_str());
	pressure = atof(atm_pre.c_str());
	rising = "";
	if(atm_ris=="0")
		rising="steady";
	else if(atm_ris=="1")
		rising="rising";
	else if(atm_ris=="2")
		rising="falling";
	
	XML.pushTag("item");
	
	item_title =XML.getValue("title", "empty", 0);
	item_geolat =XML.getValue("geo:lat", "empty", 0);
	item_geolong =XML.getValue("geo:long", "empty", 0);
	item_pubDate =XML.getValue("pubDate", "empty", 0);
	item_link =XML.getValue("link", "empty", 0);
	con_text =XML.getAttribute("yweather:condition","text","empty",0);
	con_code=XML.getAttribute("yweather:condition","code","empty",0);//code 34
	con_temp=XML.getAttribute("yweather:condition","temp","empty",0);
	con_date=XML.getAttribute("yweather:condition","date","empty",0);
	description=XML.getValue("description", "empty", 0);
		
	int numEntries = XML.getNumTags("yweather:forecast");
	
	for (int i = 0; i < numEntries; i++) {
		fore_day[i]=XML.getAttribute("yweather:forecast","day","empty",i);
		fore_date[i]=XML.getAttribute("yweather:forecast","date","empty",i);
		fore_low[i]=XML.getAttribute("yweather:forecast","low","empty",i);
		fore_high[i]=XML.getAttribute("yweather:forecast","high","empty",i);
		fore_text[i]=XML.getAttribute("yweather:forecast","text","empty",i);
		fore_code[i]=XML.getAttribute("yweather:forecast","code","empty",i);
	}
	XML.popTag();
	XML.popTag();
	XML.popTag();
}

//--------------------------------------------------------------
// updateweather() was used for getting the updated rss/xml
//--------------------------------------------------------------
void yahooweather::updateweather(){
	ofxHttpUtil.addUrl( myurl );
	ofxHttpEvents.addListener(this);				
}
//--------------------------------------------------------------
// draw () was used for showing the informations that we get for the rss/xml 
//--------------------------------------------------------------
void yahooweather::draw(){
	
	responseStr="";
	responseStr+=title;
	responseStr+="\nPublished Date: ";
	responseStr+=item_pubDate;
	//------------------------------
	responseStr+="\n\nCondition:";
	responseStr+="\n     Date: ";
	responseStr+=con_date;
	responseStr+="\n     ";
	responseStr+=con_text;
	responseStr+="\n     Temperature: ";
	responseStr+=con_temp;
	//------------------------------
	responseStr+="\n     Humidity: ";
	responseStr+=atm_hum;
	responseStr+="\n     Visibility: ";
	responseStr+=atm_vis;
	responseStr+="\n     Pressure: ";
	responseStr+=atm_pre;
	responseStr+="  "+rising+" ("+atm_ris+")";
	responseStr+="\n     Sunrise: ";
	responseStr+=ast_rise;
	responseStr+="\n     Sunset: ";
	responseStr+=ast_set;
	//------------------------------
	
	//forecast
	responseStr+="\n\nForecast:\n";
	for(int i=0; i<2;i++){
		responseStr+=fore_day[i];
		responseStr+=", ";
		responseStr+=fore_date[i];
		responseStr+="\n     High: "+fore_high[i]+"     Low: "+fore_low[i];
		responseStr+="\n     ";
		responseStr+=fore_text[i];
		responseStr+="\n";
		responseStr+="\n";
	}
	//------------------------------	

	ofDrawBitmapString(responseStr, 20, 60);
}
