#ifndef OFX_PACHUBE_INPUT_H
#define OFX_PACHUBE_INPUT_H

#include "ofMain.h"

#include "ofxPachubeFeed.h"

class ofxPachubeInput: public ofxPachubeFeed
{
public:
	ofxPachubeInput(bool _bThreaded = true);
	~ofxPachubeInput();

	bool					input(int _format = OFX_PACHUBE_CSV, bool _force = false);
                            /// supports only CSV input at the moment
	void                    onResponse(ofxPachubeResponse& response);

	void					setDatastreamCount(int _datastrams);
	bool					setValue(int _datastream, float _value);

private:
	std::string				makeCsv();

	float					fLastInput;
};

#endif
