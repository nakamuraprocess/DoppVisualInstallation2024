#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
    waitForThread();
    stopThread();
}

//--------------------------------------------------------------
void ofApp::setup(){
    windoWidth = ofGetWidth();
    windowHeight = ofGetHeight();


    // Load images
    for (int i = 0; i < faceDataMaxSize; i++) {
        bool load = imageFacesData[i].load("images/" + ofToString(i + 1) + "-test.png");
        imageFacesData[i].resize(windowHeight, windowHeight);
        imageFacesData[i].setImageType(OF_IMAGE_COLOR);

        if (!load) {
            ofLog() << "Failed to load image: " << "images/" + ofToString(i + 1) + "-test.png";
            continue;
        }

        cout << imageFacesData[i].getWidth() << " : " << imageFacesData[i].getHeight() << " : " << imageFacesData[i].getPixels().getNumChannels() << endl;
    }

    
    // Init Scenes
    views.push_back(new FaceSingleGlitchView());
    views.push_back(new IntervalSceneFirstView());
    views.push_back(new FaceGridNormalView());
    views.push_back(new IntervalSceneSecondView());
    views.push_back(new FaceSingleASsciiView());
    views.push_back(new IntervalSceneThirdView());
    sceneMaxSize = (int)views.size();

    views[0]->setImgPtr(imageFacesData);
    views[2]->setImgPtr(imageFacesData);
    views[4]->setImgPtr(imageFacesData);
    
    for (int i = 0; i < views.size(); i++) {
        views[i]->setup(windoWidth, windowHeight);
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
