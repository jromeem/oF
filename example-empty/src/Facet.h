//
//  Facet.h
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#ifndef Facet_h
#define Facet_h

#include "ofMain.h"
#include "ofxFaceTracker.h"

using TrackerPtr = ofxFaceTracker*;

class Facet {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup();    // setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    
    // variables
    float x;       // position
    float y;
    float speedY;   // speed and direction
    float speedX;
    int dim;        // size
    
    TrackerPtr trackerPtr;     // keep a pointer of the tracker
    
    ofColor color;  // color using ofColor type
    ofFbo canvas;
    
    void setTracker(TrackerPtr t);
//    Facet(ConstTrackerRef trackerRef);  // constructor - used to initialize an object,
//                                        // if no properties are passed the program sets them to the default value
//    Facet(const Facet& other) = default;
//    Facet& operator=(const Facet&) = default;
private: // place private functions or variables declarations here
};

#endif /* Facet_h */
