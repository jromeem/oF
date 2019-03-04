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
    void setCamByName(string deviceList);
	
    ofFbo canvas;
    string deviceName;
    vector<ofVideoDevice> devices;
	ofVideoGrabber cam;
    
    ofxFaceTracker tracker;
    
    ofVec2f facePos;
    float faceScale;
    bool faceFound;
    ofTexture faceTex;
    ofImage yourFaceImage;
    ofImage screenCap;
    
    ofxSyphonServer faceTextureSyphonServer;
    ofxSyphonClient mClient;
};
