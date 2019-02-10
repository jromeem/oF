#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxSyphon.h"
#include "ofxEasing.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
    ofFbo canvas;
	ofVideoGrabber cam;
    ofxFaceTracker tracker;
    
    ofVec2f facePos;
    float faceScale;
    bool faceFound;
    ofImage yourFaceImage;
    
    ofTexture faceTex;
    
    ofxSyphonServer faceTextureSyphonServer;
    ofxSyphonClient mClient;
};
