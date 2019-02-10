#pragma once

#include <memory>

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
    void facets2Mesh();
    
    bool debugMode;
    int selectedFacet;
    int selectedVertex;
    
    ofFile saveFile;
    ofFbo canvas;
    
    ofTexture lionTex;
    std::shared_ptr<ofVec2f> focusPoint;
    std::shared_ptr<ofVec2f> setPoint;
    std::shared_ptr<ofVec2f> debugPoint;
    int facetPointsCount;
    
    Facet ff;
    Facet debugFacet;
    Model mm;
    
    ofxSyphonServer lionTextureSyphonServer;
    ofxSyphonClient mClient;
};
