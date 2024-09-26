#pragma once
#include "BaseView.h"

class FaceGridNormalView : public BaseView {
private:
	bool bAfterStarted;
	ofImage* imageFacesPtr;

public:
	void setImgPtr(ofImage* ptr) {
		if (ptr == nullptr) {
			cout << "FaceGridNormalView::setImgPtr(ofImage* ptr) ptr is null" << endl;
		}
		else {
			imageFacesPtr = ptr;
		}
	}

	void setup(float _windowWidth, float _windowHeight) {

	}

	void update() {

	}

	void draw() {
		ofPushMatrix();

		ofPushStyle();
		ofSetColor(0, 0, 255);
		ofDrawRectangle(200, 100, 100, 100);

		ofPopStyle();
		ofPopMatrix();
	}

	void start() {
		// Do something

		bAfterStarted = true;
	}

	void stop() {
		if (bAfterStarted) {
			bAfterStarted = false;
		}
		// Do something

	}
};