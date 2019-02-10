#include "ofApp.h"


int main() {
    ofSetupOpenGL(920, 580, OF_WINDOW);
    //ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
    
    return ofRunApp(std::make_shared<ofApp>());
}
