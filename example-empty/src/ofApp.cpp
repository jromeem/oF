#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
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
    
    if (faceFound) {
        // update the postion and scale on the found face
//        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
//        ofDrawBitmapString("position: (" + ofToString(facePos.x) + ", " + ofToString(facePos.x) + ")", 10, 50);
//        ofDrawBitmapString("scale: " + ofToString((float) faceScale), 10, 70);
//        ofDrawBitmapString("expression: " + ofToString((float) tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH)), 10, 90);
        //tracker.draw();
    } else {
//        ofDrawBitmapString("face not found!", 10, 20);
    }

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
