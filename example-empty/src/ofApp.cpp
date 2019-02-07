#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    ff.setTracker(&tracker);
    ff.setup();
	cam.setup(1280, 720);
	tracker.setup();
    tracker.setTolerance(0.999);
    
    yourFaceImage.setUseTexture(true);
    
    // set up syphon servers
    mClient.setup();
    mainOutputSyphonServer.setName("Syphon Screen Output");
    lionTextureSyphonServer.setName("Syphon Lion Output");
    faceTextureSyphonServer.setName("Syphon Face Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    ff.update();
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
	ofSetLineWidth(2);
    
    if (tracker.getFound()) {
//        tracker.draw();
        
        ofVec2f pos = tracker.getPosition();
        float scale = tracker.getScale();

        ofNoFill();
        float faceSize = 50*scale;
        ofVec2f posCentered = ofVec2f(pos.x-faceSize/2.0, pos.y-faceSize/2.0);
        ofDrawRectangle(posCentered, faceSize, faceSize);
        
        ofFill(); // syphon needs this for some reason
        yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
        yourFaceImage.draw(0, 0, 700, 700);
        faceTex = yourFaceImage.getTexture();
//        faceTex.draw(700, 700);
        
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
        ofDrawBitmapString("position: (" + ofToString(pos.x) + ", " + ofToString(pos.x) + ")", 10, 50);
        ofDrawBitmapString("scale: " + ofToString((float) scale), 10, 70);
        ofDrawBitmapString("expression: " + ofToString((float) tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH)), 10, 90);
    }
    
    ff.draw();
    lionTex = ff.canvas.getTexture();
    
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    lionTextureSyphonServer.publishTexture(&lionTex);
    faceTextureSyphonServer.publishTexture(&faceTex);
    
//    ff.draw();
}

void ofApp::mousePressed(int x, int y, int button) {
    ofLog(OF_LOG_NOTICE, "button pos: " + ofToString((int) x) + ", " + ofToString((int) y));
    ofLog(OF_LOG_NOTICE, "button: " + ofToString((int) button));
    ff.color = ofColor(ofRandom(255), ofRandom(255), 100);
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    if(key == 'b') {
        ofLog(OF_LOG_NOTICE, "begin shape");
        tracker.reset();
    }
    if(key == 'e') {
        ofLog(OF_LOG_NOTICE, "end shape");
        tracker.reset();
    }
}
