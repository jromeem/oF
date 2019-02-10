#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
//    cam.setup(1440, 900);
    
    canvas.allocate(1920, 1080, GL_RGBA);
    ofEnableSmoothing();
    
//    ofSetFullscreen(1);
    printf( "%i, %i, %i, %i", ofGetWidth(), ofGetHeight(), ofGetScreenWidth(), ofGetScreenHeight() );
    
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
//    cam.update();
}

void ofApp::draw() {
    ofSetColor(255);
//    cam.draw(0, 0);
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
    
    // draw focus point
    ofPushStyle();
    ofNoFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawCircle(focusPoint.x, focusPoint.y, 5);
    ofDrawLine(focusPoint.x-5, focusPoint.y, focusPoint.x+5, focusPoint.y);
    ofDrawLine(focusPoint.x, focusPoint.y-5, focusPoint.x, focusPoint.y+5);
    ofPopStyle();
    
    ofFill();
    mClient.draw(50, 50);
//    mainOutputSyphonServer.publishScreen();
    lionTextureSyphonServer.publishTexture(&lionTex);
}

void ofApp::mousePressed(int x, int y, int button) {
//    ofLog(OF_LOG_NOTICE, "button pos: " + ofToString((int) x) + ", " + ofToString((int) y));
//    ofLog(OF_LOG_NOTICE, "button: " + ofToString((int) button));
    if (facetPointsCount > 0) {
        ff.points.push_back(setPoint);
    }
    focusPoint = ofVec2f(x, y);
    setPoint = ofVec2f(x, y);
    ff.color = ofColor(ofRandom(255), ofRandom(255), 100);

    facetPointsCount++;
}

void ofApp::keyPressed(int key) {
    
    // mac DELETE button is OF_KEY_BACKSPACE == 8
    if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) {
        // remove last shape
        if (mm.size() > 0) {
            mm.pop_back();
            ofLog(OF_LOG_NOTICE, "deleting last shape");
        }
    }
    
    // fine point adjusting for each point
    if (key == OF_KEY_LEFT) {
        setPoint.x = focusPoint.x--;
    }
    if (key == OF_KEY_RIGHT) {
        setPoint.x = focusPoint.x++;
    }
    if (key == OF_KEY_UP) {
        setPoint.y = focusPoint.y--;
    }
    if (key == OF_KEY_DOWN) {
        setPoint.y = focusPoint.y++;
    }
    
    // begining and ending a shape
    if (key == 'b') {
        ff = Facet();
        ff.setup();
        ofLog(OF_LOG_NOTICE, "begin shape");
    }
    if (key == 'e') {
        // get last set point
        ff.points.push_back(setPoint);
        ofLog(OF_LOG_NOTICE, "end shape");
        mm.push_back(ff);
        facetPointsCount = 0;
    }
}
