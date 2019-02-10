#include "ofApp.h"


int main() {
    ofSetupOpenGL(192, 108, OF_WINDOW);
    
    return ofRunApp(std::make_shared<ofApp>());
}
