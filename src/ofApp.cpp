#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {

}

//--------------------------------------------------------------
void ofApp::setup(){
    windowWidth = 600;
    windowHeight = 1024;

    // Load images
    for (int i = 0; i < faceDataMaxSize; i++) {
        string faceDataPath = "images/face_" + ofToString(i) + ".jpg";
        if (imageFacesData[i].load(faceDataPath)) {
            imageFacesData[i].setImageType(OF_IMAGE_COLOR);
        }
        else {
            cout << "Failed to load image: " << faceDataPath;
        }
    }

    // Init Scenes
    views[0] = new ParticipantsNameView();
    views[1] = new FaceSingleGlitchView();
    views[2] = new FaceGridNormalView();
    views[3] = new NodeAndEdgeView();
    views[4] = new SphereName2dView();
 
    for (int i = 0; i < viewMaxSize; i++) {
        views[i]->setImgPtr(imageFacesData, faceDataMaxSize);
        views[i]->setup(windowWidth, windowHeight);
    }

    // Init Scene Index
    sceneIndexList.push_back(1);
    sceneIndexList.push_back(2);
    sceneIndexList.push_back(3);
    sceneIndexList.push_back(4);

    random_device seed_gen;
    mt19937 engine(seed_gen());
    std::shuffle(sceneIndexList.begin(), sceneIndexList.end(), engine);

    for (int i = 1; i < viewMaxSize + (viewMaxSize - 2); i += 2) {
        sceneIndexList.insert(sceneIndexList.begin() + i, 0);
    }
    sceneIndex = sceneIndexList[sceneIndexCounter];


    // Display settings
    ofBackground(255);
    ofHideCursor();
    ofSetVerticalSync(true);
    ofSetFrameRate(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    float now = ofGetElapsedTimef();
    timer(now);
    views[sceneIndex]->update(now);
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
        int sceneIndexPrev = sceneIndexList[sceneIndexCounter];
        views[sceneIndexPrev]->stop();
        sceneIndexCounter++;
        sceneIndexCounter %= sceneIndexList.size();
        sceneIndex = sceneIndexList[sceneIndexCounter];
        views[sceneIndex]->start();
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
