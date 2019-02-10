#include <iostream>
#include "ofApp.h"

using namespace ofxCv;

void ofApp::loadFromFile() {
    std::vector<std::string> linesOfTheFile;
    ofBuffer buffer = ofBufferFromFile("facets-vertex-data.txt");
    for (auto line : buffer.getLines()) {
        std::vector<std::string> vertices = ofSplitString(ofTrim(line)," ");
        ofLog(OF_LOG_NOTICE, line);
        ff = Facet();
        ff.setup();
        ofLog(OF_LOG_NOTICE, ofToString(vertices.size()));
        for (int i = 0; i < vertices.size(); i+=2) {
            ofVec2f point = ofVec2f(stoi(vertices[i]), stoi(vertices[i+1]));
            ff.points.push_back(point);
        }
        mm.push_back(ff);
        linesOfTheFile.push_back(line);
    }
}

void ofApp::setup() {
    // load from save file
    ofApp::loadFromFile();
    
    canvas.allocate(1920, 1080, GL_RGBA);
    ofEnableSmoothing();
    
    printf( "%i, %i, %i, %i", ofGetWidth(), ofGetHeight(), ofGetScreenWidth(), ofGetScreenHeight() );
    
    // set up syphon servers
    mClient.setup();
    lionTextureSyphonServer.setName("Syphon Lion Output");
    mClient.set("","Simple Server");
}

void ofApp::update() {
    ff.update();
    for (auto&& f : mm) {
        f.update();
    }
}

void ofApp::draw() {
    ofSetColor(255);
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
    ofDrawLine(focusPoint.x-15, focusPoint.y, focusPoint.x+15, focusPoint.y);
    ofDrawLine(focusPoint.x, focusPoint.y-15, focusPoint.x, focusPoint.y+15);
    ofPopStyle();
    
    ofFill();
    mClient.draw(50, 50);
    lionTextureSyphonServer.publishTexture(&lionTex);
}

void ofApp::mousePressed(int x, int y, int button) {
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
    // end shape
    if (key == 'e') {
        // and get last set point
        ff.points.push_back(setPoint);
        ofLog(OF_LOG_NOTICE, "end shape");
        mm.push_back(ff);
        facetPointsCount = 0;
    }
    
    // save to file
    if (key == 's') {
        ofApp::saveToFile();
    }
}

void ofApp::saveToFile() {
    if (!saveFile.doesFileExist("facets-vertex-data.txt")) {
        ofFile newFile(ofToDataPath("facets-vertex-data.txt"), ofFile::WriteOnly);
        newFile.create();
    }
    saveFile.open("facets-vertex-data.txt",ofFile::WriteOnly);
    for (auto&& f : mm) {
        for (auto&& p : f.points) {
            saveFile << ofToString((int) p.x) + " " + ofToString((int) p.y) + " ";
        }
        saveFile << "\n";
    }
    ofLog(OF_LOG_NOTICE, "facets saved to 'facets-vertex-data.txt'!");
}
