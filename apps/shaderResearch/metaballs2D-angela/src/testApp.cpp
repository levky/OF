#include "testApp.h"
#define speed 1
void testApp::addblob(){
	blob temp;
	temp.px=ofRandom(0,BLOBS_WIDTH);
	temp.py=ofRandom(0,BLOBS_HEIGHT);
	temp.dx=(speed);
	temp.dy=(speed);
	pblobs.push_back(temp);
}
//--------------------------------------------------------------
void testApp::setup()
{
	for (int a=0;a<10;a++){
		addblob();
	}
	
	int i;
	int j;
	
	ofSetFrameRate( 60 );
	tex.allocate( BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
	texPixels	= new unsigned char[ BLOBS_WIDTH * BLOBS_HEIGHT * 3 ];
	
	vy = new int[ pblobs.size() * HEIGHT ];
	vx = new int[ pblobs.size() * WIDTH ];
}
void testApp::metaEffect(){
	
}

//--------------------------------------------------------------
void testApp::update()
{
	int i;
	int x;
	int y;
	
	//for each blobs
	for( i=0; i<pblobs.size(); ++i )
	{
		pblobs[ i ].px += pblobs[ i ].dx;
		pblobs[ i ].py += pblobs[ i ].dy;
		
		//set min limit to 1
		if( pblobs[ i ].px < 0 ) 
		{
			pblobs[ i ].dx = speed;
		}
		if( pblobs[ i ].px > BLOBS_WIDTH )
		{
			pblobs[ i ].dx = -speed;
		}
		if( pblobs[ i ].py < 0 )
		{
			pblobs[ i ].dy = speed;
		}
		if( pblobs[ i ].py > BLOBS_HEIGHT )
		{
			pblobs[ i ].dy = -speed;
		}
		
		//square the range away from the center of the circle
		for( x = 0; x < BLOBS_WIDTH; x++ )
		{
			vx[ i * BLOBS_WIDTH + x ] = (int)( pow( ( pblobs[ i ].px - x ), 2 ) );
			
		}
		
		for( y = 0; y < BLOBS_HEIGHT; y++ )
		{
			vy[ i * BLOBS_HEIGHT + y ] = (int)( pow( ( pblobs[ i ].py - y ), 2 ) );
		
		}
		
	}
	
	for( y = 0; y < BLOBS_HEIGHT; y++)
	{
		//for each row, scan through the columns
		for ( x = 0; x < BLOBS_WIDTH; x++)
		{
			int j = 0;
			int m = 1;
			
			j = ( x * 3 ) + ( y * BLOBS_WIDTH * 3 );
			
			for ( i = 0; i < pblobs.size(); i++ )
			{
				// Increase this number to make your blobs bigger
			//	if( vy[ i * BLOBS_HEIGHT + y ] <100 ||  vx[ i * BLOBS_HEIGHT + x ] <100){
				m += 60000 / ( vy[ i * BLOBS_HEIGHT + y ] + vx[ i * BLOBS_WIDTH + x ] + 1 );
			//	}
			}
			
			texPixels[ j + 0 ] = (unsigned char)( 0 );
			texPixels[ j + 1 ] = (unsigned char)(0);
			if(m> 2843.9 *exp(-0.007*BLOBS_WIDTH))
			texPixels[ j + 2 ] = (unsigned char)( 255);
			else
			texPixels[ j + 2 ] = (unsigned char)(0);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw()

{

	tex.loadData( texPixels, BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
	tex.draw( 0, 0, WIDTH, HEIGHT);
	ofDrawBitmapString(	ofToString(ofGetFrameRate()), 20, 10);
}

void testApp :: saveOutputImage ()
{
	char fileName[ 255 ];
	
	screenGrab.grabScreen( 0, 0, WIDTH, HEIGHT );
	
	sprintf( fileName, "glitch_%0.3i.png", screenGrabCount );
	
	screenGrab.saveImage( fileName );
	
	++screenGrabCount;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

