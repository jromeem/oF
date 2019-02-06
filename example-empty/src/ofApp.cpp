#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	cam.setup(1280, 720);
	tracker.setup();
    tracker.setTolerance(0.999);
    
    yourFaceImage.setUseTexture(true);
    
    // set up syphon servers
    mClient.setup();
    mainOutputSyphonServer.setName("Syphon Screen Output");
    individualTextureSyphonServer.setName("Syphon Texture Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
	ofSetLineWidth(2);
    tracker.draw();
    
    ofVec2f pos = tracker.getPosition();
    float scale = tracker.getScale();

    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    ofDrawBitmapString("position: (" + ofToString(pos.x) + ", " + ofToString(pos.x) + ")", 10, 50);
    ofDrawBitmapString("scale: " + ofToString((float) scale), 10, 70);
    ofNoFill();
    float faceSize = 50*scale;
    ofVec2f posCentered = ofVec2f(pos.x-faceSize/2.0, pos.y-faceSize/2.0);
    ofDrawRectangle(posCentered, faceSize, faceSize);
    
    ofFill(); // syphon needs this for some reason
    yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
    yourFaceImage.draw(0, 0, 700, 700);
    tex = yourFaceImage.getTexture();
    tex.draw(700, 700);
    
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    individualTextureSyphonServer.publishTexture(&tex);
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
