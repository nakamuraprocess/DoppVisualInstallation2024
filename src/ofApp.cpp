#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
    stopThread();
}

//--------------------------------------------------------------
void ofApp::setup(){

    views.push_back(new FaceSingleGlitchView());
    views.push_back(new IntervalSceneFirstView());
    views.push_back(new FaceGridNormalView());
    views.push_back(new IntervalSceneSecondView());
    views.push_back(new FaceSingleASsciiView());
    views.push_back(new IntervalSceneThirdView());

    sceneMaxSize = (int)views.size();

    for (int i = 0; i < views.size(); i++) {
        views[i]->setup();
    }

    ofBackground(0);
    ofSetVerticalSync(true);
    //ofToggleFullscreen();
    ofSetFrameRate(60);
    // ofHideCursor();
    // startThread();
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
        sleep(sceneIntervalMillis);
        sceneIndex = sceneCounter % sceneMaxSize;
        sceneCounter++;
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
