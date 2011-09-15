/*!
* ofxTriangle by kikko.fr
* -> C++ Triangle warper by Piyush Kumar
* -> Point inside polygon by Theo
*/

#ifndef OFXTRIANGLE_H_INCLUDED
#define OFXTRIANGLE_H_INCLUDED

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <del_interface.hpp>

using namespace tpp;
using namespace std;

typedef struct
{
    ofPoint a;
    ofPoint b;
    ofPoint c;

    float area;

} ofxTriangleData;

class ofxTriangle
{
    public :

        ofxTriangle(){}
        ~ofxTriangle(){}

        // Triangulate a openCV blob
        void triangulate(ofxCvBlob &cvblob, int resolution = 50, int rdmPoints = 0,int tlength=ofGetWidth());
	//void triangulate2(ofPoint &pPoint, int resolution = 50, int rdmPoints = 0);

        // Triangulate a vector of ofPoint
        void addRdmPoint(vector<Delaunay::Point> * v);

        ofPoint getTriangleCenter(ofPoint *tr);
        bool isPointInsidePolygon(ofPoint *polygon,int N, ofPoint p);

        void draw();
        void draw(float x, float y);
        void clear();


        Delaunay* delobject;

        int nTriangles;
        vector <ofxTriangleData> triangles;
		bool ShowShort;
		int Red,Green,Blue,Alpha;
    private :

        ofxCvBlob* blob;
		

};

#endif // OFXTRIANGLE_H_INCLUDED
