#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
    ofSetDataPathRoot("../Resources/data/");
    
	cam.setup(1280, 720);
	
    tracker.setup();
    tracker.setTolerance(0.001f);
    
    canvas.allocate(1280, 720, GL_RGBA);
    yourFaceImage.setUseTexture(true);
    faceFound = false;
    ofEnableSmoothing();
    
    // set up syphon servers
    mClient.setup();
    faceTextureSyphonServer.setName("Syphon Face Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    faceFound = tracker.getFound();
    // set the new position and scale of the face that was found
    if (faceFound) {
        facePos = tracker.getPosition();
        faceScale = tracker.getScale();
    }
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void ofApp::draw() {
    cam.draw(0, 0);

    float faceSize = 50*faceScale;
    ofVec2f posCentered = ofVec2f(facePos.x-faceSize/2.0, facePos.y-faceSize/2.0);
    ofNoFill();
//    ofDrawRectangle(posCentered, faceSize, faceSize);
    yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
    yourFaceImage.draw(0, 0, 700, 700);
    faceTex = yourFaceImage.getTexture();
    
    ofFill();
//    mClient.draw(50, 50);
    faceTextureSyphonServer.publishTexture(&faceTex);
}
