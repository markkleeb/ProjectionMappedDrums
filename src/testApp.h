#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSyphon.h"
#include "particle.h"

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
    
    //void circle();
	
	void keyPressed(int key);
	
    float   counter;
    
    int counter1, counter2, counter3;
    
	bool	bSmooth;
	
    ofTexture tex1;
    ofTexture tex2;
    ofTexture tex3;
    
    ofVideoPlayer video1;
    ofVideoPlayer video2;
    ofVideoPlayer video3;
    
	ofxSyphonServer mainOutputSyphonServer;

	
	ofxSyphonClient mClient;
    
    
    ofSerial	mySerial;
    
    char padvalue;
    char lastpadvalue;
    
    bool circle, rect, lines;
    
    vector<particle*> particles;

};

#endif

