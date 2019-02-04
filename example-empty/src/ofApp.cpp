#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	cam.setup(1280, 720);
	tracker.setup();
    tracker.setTolerance(0.50);
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
    
//    ofPolyline noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
//    ofSetColor(ofColor::red);
//    noseBase.draw();
//    ofDrawCircle(noseBase.getCentroid2D(), 8 * tracker.getScale());
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    ofDrawBitmapString("position: (" + ofToString(pos.x) + ", " + ofToString(pos.x) + ")", 10, 50);
    ofDrawBitmapString("scale: " + ofToString((float) scale), 10, 70);
    ofNoFill();
//    ofSetRectMode(OF_RECTMODE_CENTER);
    float faceSize = 50*scale;
    ofVec2f posCentered = ofVec2f(pos.x-faceSize/2.0, pos.y-faceSize/2.0);
    ofDrawRectangle(posCentered, faceSize, faceSize);
//    ofSetRectMode(OF_RECTMODE_CORNER);
    
    yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
    yourFaceImage.draw(0, 0, 300, 300);
    
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
