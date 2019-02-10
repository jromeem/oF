//
//  Facet.h
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#ifndef Facet_h
#define Facet_h

#include "ofMain.h"
#include "ofxEasing.h"
#include "ofxFaceTracker.h"

class Facet {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup();    // setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    
    bool hasFace;
    
    ofColor fromColor;
    ofColor toColor;
    ofColor thisColor;
    
    std::vector<ofVec2f> points;
    
    ofColor color;  // color using ofColor type
    
private: // place private functions or variables declarations here
    float deltaTime;
    void setRandomColors();
};

#endif /* Facet_h */