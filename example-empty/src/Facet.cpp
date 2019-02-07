//
//  Facet.cpp
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#include "Facet.h"

void Facet::setTracker(TrackerPtr t) {
    trackerPtr = t;
}

//Facet::Facet(ConstTrackerRef t) :
//    // initialization assignment sytnax
//    trackerRef (t)
//{}

void Facet::setup() {
    canvas.allocate(500, 500, GL_RGBA);
    x = ofRandom(0, ofGetWidth());      // give some random positioning
    y = ofRandom(0, ofGetHeight());
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
    dim = 20;
    
    color.set(ofRandom(255),ofRandom(255),ofRandom(255)); // one way of defining digital color is by addressing its 3 components individually (Red, Green, Blue) in a value from 0-255, in this example we're setting each to a random value
}

void Facet::update() {
    if(x < 0 ){
        x = 0;
        speedX *= -1;
    } else if(x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= -1;
    }
    
    if(y < 0 ){
        y = 0;
        speedY *= -1;
    } else if(y > ofGetHeight()){
        y = ofGetHeight();
        speedY *= -1;
    }
    
    x+=speedX;
    y+=speedY;
}

void Facet::draw() {
    canvas.begin();

    if (trackerPtr->getFound()) {
        // finding a face change the visuals
        ofSetColor(100, 100, 100);
        ofDrawRectangle(200, 200, 40, 40);
    } else {
        // no face default visuals
        ofSetColor(color);
        ofDrawRectangle(200, 200, 40, 40);
    }
    
    ofSetColor(color);
    ofDrawCircle(x, y, dim);
    canvas.end();
    
    canvas.draw(0, 0, 500, 500);
}
