#ifndef OFX_PACHUBE_OUTPUT_H
#define OFX_PACHUBE_OUTPUT_H

#include "ofMain.h"

#include "ofxPachubeFeed.h"

class ofxPachubeOutput: public ofxPachubeFeed
{
public:
	ofxPachubeOutput(bool _bThreaded = true);
	~ofxPachubeOutput();

	bool					output(int _format = OFX_PACHUBE_CSV, bool _force = false);
	bool                    parseResponseEeml(string _response);
	bool                    parseResponseCsv(string _response);
	void                    onResponse(ofxPachubeResponse& response);

	ofxPachubeLocation&		getLocation() {return location;}
	std::string&			getTitle() {return sTitle;}
	std::string&			getStatus() {return sStatus;}
	std::string&			getDescription() {return sDescription;}
	std::string&			getWebsite() {return sWebsite;}
	std::string&            getUpdated() {return sUpdated;}

private:

	/// INFO ABOUT FEED ->
 	std::string				sTitle;
	std::string				sStatus;
	std::string				sDescription;
	std::string				sWebsite;

	std::string             sUpdated;

	ofxPachubeLocation		location;
	/// <- INFO

    float                   fLastOutput;
};

#endif
