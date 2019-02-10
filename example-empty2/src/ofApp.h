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
    void keyBindingsEditMode(int key);
    void keyBindingsDebugMode(int key);
    void saveToFile();
    void loadFromFile();
    
    bool debugMode;
    int selectedFacet;
    int selectedVertex;
    
    ofFile saveFile;
    ofFbo canvas;
    
    ofTexture lionTex;
    ofVec2f focusPoint;
    ofVec2f setPoint;
    ofVec2f debugPoint;
    int facetPointsCount;
    
    Facet ff;
    Facet debugFacet;
    Model mm;
    
    ofxSyphonServer lionTextureSyphonServer;
    ofxSyphonClient mClient;
};
