//
//  Facet.cpp
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#include "Facet.h"
#include "ofxEasing.h"
using namespace ofxeasing;

void Facet::setup() {
    toColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
    fromColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

void Facet::update() {
    int time = ofGetElapsedTimeMillis();
    int thresh = 4000;
    float lerpAmount = ofxeasing::map(time, 0, thresh, 0.f, 1.f, &ofxeasing::linear::easeIn);
    thisColor = fromColor.getLerped(toColor, lerpAmount);
//    ofLog(OF_LOG_NOTICE, "lerpAmount: "+ofToString((float) lerpAmount));
//    ofLog(OF_LOG_NOTICE, "thisColor: "+ofToString((ofColor) thisColor));
//    ofLog(OF_LOG_NOTICE, "deltaTime: "+ofToString((float) time));
    
    // reset facet color
    if (time > thresh) {
        ofResetElapsedTimeCounter();
        ofLog(OF_LOG_NOTICE, "are you ever here ##########################");
        toColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
//        thisColor = toColor;
//        fromColor = toColor;
    }
}

void Facet::draw() {
    update();
    
    ofSetColor(fromColor);
    ofDrawRectangle(0, 0, 20, 20);
    ofSetColor(thisColor);
    ofDrawRectangle(20, 0, 20, 20);
    ofSetColor(toColor);
    ofDrawRectangle(40, 0, 20, 20);
    
    ofSetColor(thisColor);
    // draw the shape
    ofBeginShape();
    ofVertices(points);
    ofEndShape();
}

