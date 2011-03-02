#ifndef _XML_EXTENDED_
#define _XML_EXTENDED_


#include "ofxXmlSettings.h"
#include "ofMain.h"
//#include "ofAddons.h"

/* copied straight from ofxXmlSettings */
// a pretty useful tokenization system:
static vector<string> tokenize(const string & str, const string & delim);
static vector<string> tokenize(const string & str, const string & delim)
{
  vector<string> tokens;

  size_t p0 = 0, p1 = string::npos;
  while(p0 != string::npos)
  {
    p1 = str.find_first_of(delim, p0);
    if(p1 != p0)
    {
      string token = str.substr(p0, p1 - p0);
      tokens.push_back(token);
    }
    p0 = str.find_first_not_of(delim, p1);
  }
  return tokens;
}


//----------------------------------------
class ofxXmlExtended: public ofxXmlSettings {

        public:

	
            // we return bool as in loadFile();
            bool loadFromString(const string xmlString) {
                 doc.Parse(xmlString.c_str());
				bool parseOk = !doc.Error(); // if there is an error doc.Error = true;
                storedHandle = TiXmlHandle(&doc);
                // initialize levelfor push/pop
                // see http://www.openframeworks.cc/forum/viewtopic.php?t=615
                level=0;
                return parseOk;
            }

            string getAttribute (string tag, string attribute, string defaultValue, int which = 0) {
                char * tempStr = new char[MAX_TAG_VALUE_LENGTH_IN_CHARS];
                memset(tempStr, 0, MAX_TAG_VALUE_LENGTH_IN_CHARS);
                char * returnPtr = (char *) defaultValue.c_str();
                if (readAttribute(tag, attribute, tempStr, which)){
                    returnPtr = tempStr;
                }
                string returnString(returnPtr);
                delete tempStr;
                return returnString;
            }

        protected:


            bool readAttribute(string tag, string attribute, char * attributeString, int which = 0) {
                vector<string> tokens = tokenize(tag,"#");

                TiXmlHandle attrHandle = storedHandle;
                for(int x=0;x<tokens.size();x++){
                    if(x == 0)attrHandle = attrHandle.ChildElement(tokens.at(x), which);
                    else attrHandle = attrHandle.FirstChildElement( tokens.at(x) );
                }

                //now, clear that vector!
                tokens.clear();

                if (attrHandle.Element()->Attribute(attribute.c_str())){
                    int maxLen = MIN(MAX_TAG_VALUE_LENGTH_IN_CHARS, strlen(attrHandle.ToElement()->Attribute(attribute.c_str())));
                    memcpy(attributeString, attrHandle.ToElement()->Attribute(attribute.c_str()), maxLen);
                    return true;
                }  else {
                    return false;
                }

                return false;

            }



};


#endif
