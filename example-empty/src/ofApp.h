#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxSyphon.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    ofImage yourFaceImage;
    
    ofTexture tex;
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    
    ofxSyphonClient mClient;
};
