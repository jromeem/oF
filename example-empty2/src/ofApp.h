#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Facet.h"
#include "ofxSyphon.h"
#include "ofxEasing.h"

class ofApp : public ofBaseApp {
public:
    using Model = std::vector<Facet>;
    
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void mousePressed(int x, int y, int button);
	
    ofFbo canvas;
    
    ofTexture lionTex;
    ofVec2f focusPoint;
    ofVec2f setPoint;
    int facetPointsCount;
    
    Facet ff;
    Model mm;
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer lionTextureSyphonServer;
    ofxSyphonServer faceTextureSyphonServer;
    ofxSyphonClient mClient;
};
