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
    toColor = ofColor::fromHsb(ofRandom(255),200,255);
    fromColor = ofColor::fromHsb(ofRandom(255),200,255);
}

void Facet::update() {
    
    int thresh = 500;
    int time = ofGetElapsedTimeMillis();
    float lerpAmount = ofxeasing::map(time, 0, thresh, 0.f, 1.f, &ofxeasing::linear::easeIn);
    fromColor.lerp(toColor, lerpAmount);
    
//    ofLog(OF_LOG_NOTICE, "lerpAmount: "+ofToString((float) lerpAmount));
//    ofLog(OF_LOG_NOTICE, "thisColor: "+ofToString((ofColor) thisColor));
//    ofLog(OF_LOG_NOTICE, "deltaTime: "+ofToString((float) time));

    // reset facet color
    if (time > thresh) {
        ofResetElapsedTimeCounter();
//        ofLog(OF_LOG_NOTICE, "are you ever here ##########################");
        toColor = ofColor::fromHsb(ofRandom(255),200,255);
    }
}

void Facet::draw() {
    update();
    ofSetColor(fromColor);
    // draw the shape
    ofBeginShape();
    ofVertices(points);
    ofEndShape();
}

