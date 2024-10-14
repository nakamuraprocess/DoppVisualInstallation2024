#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"
#include "ofApp.h"
#include <cmath>

class ArtistImg {
private:
	float x;
	float y;
	float z;
	float speed;
	float gravity;
	float imgSize;
	ofImage initImg;
	ofImage img;

public:
	void setup(ofImage tmpImg) {
		initImg = tmpImg;
		gravity = 0.098;
		reset();
	}

	void update() {
		speed += gravity;
		y -= speed;

		// âÊñ äOÇ…èoÇΩèÍçá
		if (y < -300) {
			reset();
		}
	}

	// è„è∏
	void moveImg() {
		ofPushMatrix();
		ofTranslate(x, y, z);
		// ofDrawAxis(200); // é≤Çï`âÊ
		img.draw(0, 0);

		ofPopMatrix();
	}

	void reset() {
		x = ofRandom(-100, ofGetWidth() + 100);
		y = ofGetHeight() + ofRandom(100, 2000);
		z = -1 * ofRandom(100, 400);
		speed = 0;
		imgSize = ofRandom(5, 100);
		img = initImg;
		img.resize(imgSize, imgSize);
	}
};

class FaceSoaringView : public BaseView {
private:
	float windowWidth;
	float windowHeight;

	int TestNameNum = 200;
	vector <ArtistImg> artists;

	ofImage* imageFacesPtr;
	int imageMaxSize;

public:
	void setImgPtr(ofImage* ptr, const int size) {
		if (ptr == nullptr) {
			cout << "FaceSingleGlitchView::setImgPtr(ofImage* ptr) ptr is null" << endl;
		}
		else {
			imageFacesPtr = ptr;
			imageMaxSize = size;
		}
	}

	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		for (int i = 0; i < imageMaxSize * 2; i++) {
			ArtistImg setImg;
			setImg.setup(imageFacesPtr[i % imageMaxSize]);
			artists.push_back(setImg);
		}
	}

	void update() {

	}

	void draw() {
		ofBackground(0);

		for (int i = 0; i < imageMaxSize * 2; i++) {
			artists[i].moveImg();
			artists[i].update();
		}
	}


	void start() {
	}

	void stop() {
		// ofLog() << "RESET";
		// ofSetColor(255);
	}
};