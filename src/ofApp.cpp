#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
    waitForThread();
    stopThread();
}

//--------------------------------------------------------------
void ofApp::setup(){
    windowWidth = ofGetWidth();
    windowHeight = ofGetHeight();

    // Load images
    for (int i = 0; i < faceDataMaxSize; i++) {
        bool load = imageFacesData[i].load("images/face_" + ofToString(i) + ".jpg");
        imageFacesData[i].resize(windowHeight, windowHeight);
        imageFacesData[i].setImageType(OF_IMAGE_COLOR);
        if (!load) {
            ofLog() << "Failed to load image: " << "images/face_" + ofToString(i) + ".jpg";
            continue;
        }
        cout << imageFacesData[i].getWidth() << " : " << imageFacesData[i].getHeight() << " : " << imageFacesData[i].getPixels().getNumChannels() << endl;
    }

    // Init Scenes
    views.push_back(new FaceSingleGlitchView());
    views.push_back(new ParticipantsNameView());
    views.push_back(new FaceSingleGlitchView());
    for (int i = 0; i < views.size(); i++) {
        views[i]->setImgPtr(imageFacesData);
        views[i]->setup(windowWidth, windowHeight);
    }

    ofBackground(0);
    ofSetVerticalSync(true);
    //ofToggleFullscreen();
    ofSetFrameRate(60);
    ofHideCursor();
    startThread();
}

//--------------------------------------------------------------
void ofApp::update(){
    views[sceneIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    views[sceneIndex]->draw();
}

//--------------------------------------------------------------
void ofApp::threadedFunction() {
    while (isThreadRunning()) {
        sceneIndex = sceneCounter % (int)views.size();
        for (int i = 0; i < views.size(); i++) {
            if (sceneIndex == i) {
                views[sceneIndex]->start();
            }
            else {
                views[i]->stop();
            }
        }
        sceneCounter++;
        sleep(sceneIntervalMillis);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
