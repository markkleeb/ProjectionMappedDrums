#include "testApp.h"

const int width = 800;
const int height = 600;

//--------------------------------------------------------------
void testApp::setup(){
	counter = 0;
    
    
    circle = rect = lines  = false;

	ofSetCircleResolution(50);
	
    //ofBackground(0,0,0);
    
    mySerial.setup("/dev/tty.usbserial-FTEZUA8N",115200); 
    
    padvalue = 0;
    lastpadvalue = 0;
	
    bSmooth = false;
	ofSetWindowTitle("graphics example");
    
	mainOutputSyphonServer.setName("Screen Output");

    
	mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
	


    
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void testApp::update(){
	counter = counter + 0.033f;
    
    while(mySerial.available()) {
        padvalue = mySerial.readByte();
        //  padvalue = ofToBinary(padvalue);
        //cout << "value " << ofToBinary(padvalue) << " / 0x" << ofToHex(padvalue) << endl;
        //cout << "value " << ofToBinary(padvalue) << " / " << ((char) padvalue) << "\n";
            }

    //cout << "time " << ofGetUnixTime()-counter1 << "\n";
    

}

bool removeIfDead(particle* p) {
	return p->isDead();
}

bool bitRead(char cur, int position) {
    return cur & (1 << position);
}


//void testApp::circle(){

// ofSetColor(0,0,255);
// ofFill();		// draw "filled shapes"
// ofCircle(100,400,60);

//}


//--------------------------------------------------------------
void testApp::draw(){
	    
	
    if(bitRead(padvalue, 0) && padvalue != lastpadvalue ){ 
        circle = true;
       // cout << "Pad1 " << bitRead(padvalue, 0) << "\n";
    }
    else circle = false;
   
    
    if(bitRead(padvalue, 1)&& padvalue != lastpadvalue ) {
        rect = true;
       // cout << "Pad2 " << bitRead(padvalue, 1) << "\n";
    }
    else rect = false;
    
    
    if(bitRead(padvalue, 2)&& padvalue != lastpadvalue ){
    
        lines = true;
       // cout << "Pad3 " << bitRead(padvalue, 2) << "\n";
    }
   
    else lines = false;
        
    
    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //--------------------------- circles
    ofBackground(255);
    
    if(circle){
        
        counter1 = ofGetUnixTime();
        
        if(ofGetUnixTime() - counter1 > 0){
        
            circle = false;
            
        }
            
        float angle = 0;
        
        ofPushMatrix();
        ofTranslate(100, 250);
        
        for(int i=0; i < 20; i++){
        
        particles.push_back(new particle(ofPoint(0,0)));        
            
        }
            
        for(int i=0; i < particles.size(); i++){
            particles[i]->run();
        }
        
        ofRemove(particles, removeIfDead);
        ofPopMatrix();        
        
    }

         
     //--------------------------- rectangles
    if(rect){ 
        
        counter2 = ofGetUnixTime();
        
        if(ofGetUnixTime() - counter2 > 10){
            
            rect = false;
        }

        
    ofFill();
     for (int i = 0; i < 400; i++){
     ofSetColor((int)ofRandom(0,100));
     ofRect(ofRandom(250,300),ofRandom(150,350),ofRandom(100,300),ofRandom(1,5));
     }
        
        }
    
    
    if(lines&& padvalue != lastpadvalue){
        
        counter3 = ofGetUnixTime();
        
        if(ofGetUnixTime() - counter3 > 10){
            
            lines = false;
        }

        
        ofSetColor(0);
        ofSetLineWidth(1);
        for (int i=0; i < 200; i+=20) {
            
            ofRect(600, 150+i, 200, 10);
        }
        } 
    
    
    
    
    
    // Syphon Stuff
    
    ofSetColor(255, 255, 255);
    
    ofEnableAlphaBlending();
    
    mClient.draw(50, 50);    
    
    mainOutputSyphonServer.publishScreen();
    
   
    
    ofDrawBitmapString("Note this text is not captured by Syphon since it is drawn after publishing.\nYou can use this to hide your GUI for example.", 150,500);    
    
    padvalue = lastpadvalue;
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
}
