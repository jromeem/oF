#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Facet.h"
#include "ofxSyphon.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mousePressed(int x, int y, int button);
	
	ofVideoGrabber cam;
    ofxFaceTracker tracker;
    ofImage yourFaceImage;
    
    ofTexture lionTex;
    ofTexture faceTex;
    
    Facet ff;
    
    ofxSyphonServer mainOutputSyphonServer;
    
    // texture lion output
    ofxSyphonServer lionTextureSyphonServer;
    // texture face output
    ofxSyphonServer faceTextureSyphonServer;
    
    ofxSyphonClient mClient;
};
