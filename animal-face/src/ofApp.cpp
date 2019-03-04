#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::setCamByName(string deviceName) {
    devices = cam.listDevices();
    for(vector<ofVideoDevice>::iterator it = devices.begin(); it != devices.end(); ++it) {
        if(it->deviceName == deviceName) {
            cam.setDeviceID(it->id);
            break;
        }
    }
}

void ofApp::setup() {
    ofSetDataPathRoot("../Resources/data/");
    
    //deviceName = "C922 Pro Stream Webcam";
    deviceName = "HD Pro Webcam C920";
    ofApp::setCamByName(deviceName);
	cam.setup(1280, 720);
    
    tracker.setup();
    tracker.setTolerance(0.001f);
    
    canvas.allocate(1280, 720, GL_RGBA);
    yourFaceImage.setUseTexture(true);
    faceFound = false;
    faceTex.allocate(700, 700, GL_RGBA);
    ofEnableSmoothing();
    
    // set up syphon servers
    mClient.setup();
    faceTextureSyphonServer.setName("Syphon Face Output 1");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    faceFound = tracker.getFound();
    // set the new position and scale of the face that was found
    if (faceFound) {
        facePos = tracker.getPosition();
        faceScale = tracker.getScale();
    }
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void ofApp::draw() {
    cam.draw(0, 0);

    float faceSize = 50*faceScale;
    ofVec2f posCentered = ofVec2f(facePos.x-faceSize/2.0, facePos.y-faceSize/2.0);
    ofNoFill();
//    ofDrawRectangle(posCentered, faceSize, faceSize);
    yourFaceImage.grabScreen(posCentered.x, posCentered.y, faceSize, faceSize);
    yourFaceImage.draw(0, 0, 700, 700);
    screenCap.grabScreen(0, 0, 700, 700);
    faceTex = screenCap.getTexture();
//    faceTex.draw(0, 0, 700, 700);
    
    ofFill();
    mClient.draw(50, 50);
    faceTextureSyphonServer.publishTexture(&faceTex);
}
