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
    mainOutputSyphonServer.setName("Syphon Screen Output");
    lionTextureSyphonServer.setName("Syphon Lion Output");
    faceTextureSyphonServer.setName("Syphon Face Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    ff.update();
//    for (auto&& f : mm) {
//        f.update();
//    }
    faceFound = tracker.getFound();
    // set the new position and scale of the face that was found
    if (faceFound) {
        facePos = tracker.getPosition();
        faceScale = tracker.getScale();
    }
    // set all facets if the face was found
    for (auto&& f : mm) {
        f.hasFace = faceFound;
    }
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
	ofSetLineWidth(2);
    
    if (faceFound) {
        // update the postion and scale on the found face
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
        ofDrawBitmapString("position: (" + ofToString(facePos.x) + ", " + ofToString(facePos.x) + ")", 10, 50);
        ofDrawBitmapString("scale: " + ofToString((float) faceScale), 10, 70);
        ofDrawBitmapString("expression: " + ofToString((float) tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH)), 10, 90);
        //tracker.draw();
    } else {
        ofDrawBitmapString("face not found!", 10, 20);
    }

    float faceSize = 50*faceScale;
    ofVec2f posCentered = ofVec2f(facePos.x-faceSize/2.0, facePos.y-faceSize/2.0);
    ofNoFill();
    ofDrawRectangle(posCentered, faceSize, faceSize);
    yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
    
    yourFaceImage.draw(0, 0, 700, 700);
//    faceTex = yourFaceImage.getTexture();
    
    canvas.begin();
    ofClear(255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 2);
    ofFill();
    for (auto&& f : mm) {
        f.draw();
    }
    canvas.end();
    canvas.draw(0, 0);
    
    faceTex = yourFaceImage.getTexture();
    lionTex = canvas.getTexture();
    
    ofFill();
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    lionTextureSyphonServer.publishTexture(&lionTex);
    faceTextureSyphonServer.publishTexture(&faceTex);
}

void ofApp::mousePressed(int x, int y, int button) {
    ofLog(OF_LOG_NOTICE, "button pos: " + ofToString((int) x) + ", " + ofToString((int) y));
    ofLog(OF_LOG_NOTICE, "button: " + ofToString((int) button));
    ff.color = ofColor(ofRandom(255), ofRandom(255), 100);
    ff.points.push_back(ofVec2f(x, y));
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
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
