#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	cam.setup(1280, 720);
    
    canvas.allocate(1280, 720, GL_RGBA);
    ofEnableSmoothing();
    
    // set up syphon servers
    mClient.setup();
    mainOutputSyphonServer.setName("Syphon Screen Output");
    lionTextureSyphonServer.setName("Syphon Lion Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    ff.update();
    for (auto&& f : mm) {
        f.update();
    }
	cam.update();
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
	ofSetLineWidth(2);
    
    canvas.begin();
    ofClear(255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 2);
    ofFill();
    for (auto&& f : mm) {
        f.draw();
    }
    canvas.end();
    canvas.draw(0, 0);
    
    lionTex = canvas.getTexture();
    
    ofFill();
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    lionTextureSyphonServer.publishTexture(&lionTex);
}

void ofApp::mousePressed(int x, int y, int button) {
    ofLog(OF_LOG_NOTICE, "button pos: " + ofToString((int) x) + ", " + ofToString((int) y));
    ofLog(OF_LOG_NOTICE, "button: " + ofToString((int) button));
    ff.color = ofColor(ofRandom(255), ofRandom(255), 100);
    ff.points.push_back(ofVec2f(x, y));
}

void ofApp::keyPressed(int key) {
    if(key == 'b') {
        ff = Facet();
        ff.setup();
        ofLog(OF_LOG_NOTICE, "begin shape");
    }
    if(key == 'e') {
        ofLog(OF_LOG_NOTICE, "end shape");
        mm.push_back(ff);
    }
}
