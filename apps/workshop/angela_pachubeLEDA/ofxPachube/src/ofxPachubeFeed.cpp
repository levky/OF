#include "ofxPachubeFeed.h"

#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"
#include "Poco/StreamConverter.h"
#include "Poco/URIStreamOpener.h"

#include "Poco/Exception.h"

#include <fstream>


ofxPachubeFeed::ofxPachubeFeed(bool _bThreaded)
{
    bThreaded = _bThreaded;
	bVerbose = true;

	sApiUrl = "http://www.pachube.com/api/";
	sApiKey = "";
	iFeedId = -1;

	fMinInterval = OFX_PACHUBE_MIN_INTERVAL;
	bRequestQueued = false;
	bLastRequestOk = true;
	fLastResponseTime = -1.f;

    if (bThreaded)
        startThread();
}

ofxPachubeFeed::~ofxPachubeFeed()
{
    if (bThreaded)
        stopThread();
}

void
ofxPachubeFeed::setMinInterval(float fSeconds)
{
	if (fSeconds > OFX_PACHUBE_MIN_INTERVAL)
		fMinInterval = fSeconds;
}

void
ofxPachubeFeed::setApiKey(std::string _sApiKey)
{
	sApiKey = _sApiKey;
}

void
ofxPachubeFeed::setFeedId(int _iId)
{
	iFeedId = _iId;
}
//
void 
ofxPachubeFeed::setCsvUrl(string _url)
{
	iurl=_url;
}
void 
ofxPachubeFeed::setXmlUrl(string _url)
{
	xurl=_url;
}
void
ofxPachubeFeed::threadedFunction()
{
    if (bVerbose) printf("[PACHUBE] Thread started\n");
    while (true)
    {
        // check if new request is available
        if (bRequestQueued)
        {
            if (bVerbose) printf("[PACHUBE] new request available\n");

            sendRequest(request);

            bRequestQueued = false;
        }

        // sleep
        ofSleepMillis(1000);
    }
}

void
ofxPachubeFeed::sendRequest(ofxPachubeRequest request)
{
    try{
        URI uri( request.url.c_str() );
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        HTTPClientSession session(uri.getHost(), uri.getPort());
        session.setTimeout(Timespan(request.timeout, 0));

        HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
        if (request.method == OFX_PACHUBE_PUT)
            req.setMethod(HTTPRequest::HTTP_PUT);

        /// headers
        for(unsigned int i=0; i<request.headerIds.size(); i++){
            const std::string name = request.headerIds[i].c_str();
            const std::string val = request.headerValues[i].c_str();
            req.set(name, val);
        }

        req.set("Content-Length", ofToString((int)request.data.length()));

        if (bVerbose) printf("[PACHUBE] ------------------------------\n");
        if (bVerbose) printf("[PACHUBE] write data request\n");
        session.sendRequest(req) << request.data;

        if (bVerbose) printf("[PACHUBE] about to receive a response\n");
        HTTPResponse res;
        istream& rs = session.receiveResponse(res);
        if (bVerbose) printf("[PACHUBE] received a session response\n");

        if (bVerbose) printf("[PACHUBE] create new response object\n");
		ofxPachubeResponse response = ofxPachubeResponse(res, rs, path, request.format);

        if (bVerbose) printf("[PACHUBE] broadcast response event\n");
    	ofNotifyEvent(responseEvent, response, this);

        if (bVerbose) printf("[PACHUBE] ------------------------------\n\n");

    }catch (Exception& exc){
        printf("[PACHUBE] Poco exception nr %d: %s\n", exc.code(), exc.displayText().c_str());
        bLastRequestOk = false;
    }
}

float
ofxPachubeFeed::getValue(int _datastream)
{
	if (_datastream < pData.size())
		return pData.at(_datastream).fValue;

	return 0.f;
}

ofxPachubeData*
ofxPachubeFeed::getDataStruct(int _datastream)
{
	if (_datastream >= pData.size())
		return NULL;

	return &pData.at(_datastream);
}
