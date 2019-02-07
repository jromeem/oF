#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Facet.h"
#include "ofxSyphon.h"
#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
    using Model = std::vector<Facet>;
    
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mousePressed(int x, int y, int button);
	
    ofFbo canvas;
	ofVideoGrabber cam;
    ofxFaceTracker tracker;
    
    ofVec2f facePos;
    float faceScale;
    bool faceFound;
    ofImage yourFaceImage;
    
    ofTexture lionTex;
    ofTexture faceTex;
    
    Facet ff;
    Model mm;
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer lionTextureSyphonServer;
    ofxSyphonServer faceTextureSyphonServer;
    ofxSyphonClient mClient;
};
