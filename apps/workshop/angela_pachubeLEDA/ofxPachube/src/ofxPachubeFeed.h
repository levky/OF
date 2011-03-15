/// This is an openFrameworks addon for talking to Pachube
/// www.openframeworks.cc
/// www.pachube.com
///
/// Works with of pre-release 0.06
///
/// Written by CJ
/// www.carljohanrosen.com
///
///
/// There is an issue with threading and broken internet connection which causes the
/// app to crash if connection was broken when the application was started. Therefore
/// the addon has the possibility to run non-threaded which causes the app to hang
/// while waiting for www.pachube.com to respond. The choice is yours...
///
/// Dependencies:
/// ofxThread

#ifndef OFX_PACHUBE_FEED_H
#define OFX_PACHUBE_FEED_H

#include "ofMain.h"
#include "ofxThread.h"

#define OFX_PACHUBE_MIN_INTERVAL    5
#define OFX_PACHUBE_GET             0
#define OFX_PACHUBE_PUT             1
#define OFX_PACHUBE_CSV             0
#define OFX_PACHUBE_EEML            1


#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Timespan.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
//using Poco::Net::HTMLForm;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Timespan;

struct ofxPachubeLocation
{
	std::string				sDomain;
	std::string				sExposure;
	std::string				sDisposition;

	std::string				sName;
	std::string				sLat;
	std::string				sLon;
};

struct ofxPachubeData
{
	int						iId;
	std::vector<std::string> pTags;
	float					fValue;
	float					fValueMin;
	float					fValueMax;
};

struct ofxPachubeRequest
{
    ofxPachubeRequest()
    {
    }
    ~ofxPachubeRequest(){
        clearHeaders();
    }

	int             method;             /// GET or PUT
	int             format;             /// CSV or EEML
	string          url;
	int             timeout;            /// connection timeout

	vector <string> headerIds;          /// http header values/ids
	vector <string> headerValues;

	string          data;

    // ----------------------------------------------------------------------
	void addHeader(string id, string value){
        headerIds.push_back( id );
        headerValues.push_back( value );
	}
	// ----------------------------------------------------------------------
	void clearHeaders(){
	    headerIds.clear();
        headerValues.clear();
	}
};

struct ofxPachubeResponse
{
    ofxPachubeResponse(HTTPResponse& pocoResponse, std::istream &bodyStream, string _url, int _format)
    {
        status=pocoResponse.getStatus();
		timestamp=pocoResponse.getDate();
		reasonForStatus=pocoResponse.getReasonForStatus(pocoResponse.getStatus());
		contentType = pocoResponse.getContentType();

		StreamCopier::copyToString(bodyStream, responseBody);
        url = _url;
        format = _format;
    }
    ~ofxPachubeResponse()
    {}

	int             status; 				/// return code for the response ie: 200 = OK
	string          reasonForStatus;		/// text explaining the status
	string          responseBody;		    /// the actual response
	string          contentType;			/// the mime type of the response
	Poco::Timestamp timestamp;		        /// time of the response
	string          url;
	int             format;                 /// CSV/EEML
};

class ofxPachubeFeed: public ofxThread
{
public:
	ofxPachubeFeed(bool _bThreaded);
	virtual ~ofxPachubeFeed();

	void					setMinInterval(float fSeconds);
	void					setApiKey(std::string _sApiKey);
	void					setFeedId(int _iId);
	int						getFeedId()
                            {return iFeedId;}
	//
	void					setCsvUrl(string _url);
	void					setXmlUrl(string _xml);
	void					setVerbose(bool _bVerbose)
                            {bVerbose = _bVerbose;}

    bool                    getLastRequestOk()
                            {return bLastRequestOk;}
    float                   getLastResponseTime()
                            {return fLastResponseTime;}

	int						getDatastreamCount() {return pData.size();}
	float					getValue(int _datastream);
	ofxPachubeData*			getDataStruct(int _datastream);

protected:
    bool                    bThreaded;

	bool                    bRequestQueued;
	ofxPachubeRequest       request;
	void                    threadedFunction();
    void                    sendRequest(ofxPachubeRequest request);

    ofEvent<ofxPachubeResponse> responseEvent;
    virtual void            onResponse(ofxPachubeResponse& response) =0;
                            /// dummy function, just to make ofxPachubeFeed impossible to instantiate
    bool                    bLastRequestOk;
    float                   fLastResponseTime;


	bool					bApiKeyOk;
	std::string				sApiKey;

	string                  sApiUrl;
	string					iurl;
	string					xurl;
	int						iFeedId;

	/// FEED DATA ->
	std::vector<std::string>::iterator itTags;
	std::vector<ofxPachubeData>::iterator itData;
	std::vector<ofxPachubeData> pData;
	/// <- FEED DATA

	float					fMinInterval;

	bool					bVerbose;
};

#endif
