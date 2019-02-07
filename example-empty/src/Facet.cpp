//
//  Facet.cpp
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#include "Facet.h"

//Facet::Facet(ConstTrackerRef t) :
//    // initialization assignment sytnax
//    trackerRef (t)
//{}

void Facet::setup() {
    canvas.allocate(500, 500, GL_RGBA);
    color.set(ofRandom(255),ofRandom(255),ofRandom(255)); // one way of defining digital color is by addressing its 3 components individually (Red, Green, Blue) in a value from 0-255, in this example we're setting each to a random value
}

void Facet::update() {
    
}

void Facet::draw() {
    canvas.begin();
    
    color = hasFace ? color : 100;
    ofSetColor(color);
    ofDrawRectangle(200, 200, 40, 40);
    
    canvas.end();
    
    canvas.draw(0, 0, 500, 500);
}
