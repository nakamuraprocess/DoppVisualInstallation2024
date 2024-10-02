#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {

}

//--------------------------------------------------------------
void ofApp::setup(){
    windowWidth = ofGetWidth();
    windowHeight = ofGetHeight();

    // Load images
    for (int i = 0; i < faceDataMaxSize; i++) {
        string faceDataPath = "images/face_" + ofToString(i) + ".jpg";
        if (imageFacesData[i].load(faceDataPath)) {
            imageFacesData[i].setImageType(OF_IMAGE_COLOR);
            cout << faceDataPath
            << " x: " << imageFacesData[i].getWidth()
            << " y: " << imageFacesData[i].getHeight()
            << " c: " << imageFacesData[i].getPixels().getNumChannels()
            << endl;
        }
        else {
            cout << "Failed to load image: " << faceDataPath;
        }
    }

    // Init Scenes
    BaseView* faceSingleGlitchView = new FaceSingleGlitchView();
    BaseView* faceGridNormalView = new FaceGridNormalView();
    BaseView* participantsNameView = new ParticipantsNameView();

    views.push_back(faceSingleGlitchView);
    views.push_back(participantsNameView);
    views.push_back(faceGridNormalView);
    views.push_back(participantsNameView);

    for (int i = 0; i < views.size(); i++) {
        views[i]->setImgPtr(imageFacesData, faceDataMaxSize);
        views[i]->setup(windowWidth, windowHeight);
    }

    ofBackground(0);
    ofHideCursor();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::update(){
    timer(ofGetElapsedTimef());
    views[sceneIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    views[sceneIndex]->draw();
}

//--------------------------------------------------------------
void ofApp::timer(float now) {
    float timer = now - timerLapTime;
    if (timer >= timerSleepTime) {
        timerLapTime = now;
        sceneIndex++;
        sceneIndex %= (int)views.size();
        for (int i = 0; i < views.size(); i++) {
            if (sceneIndex == i) {
                views[sceneIndex]->start();
            }
            else {
                views[i]->stop();
            }
        }
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
