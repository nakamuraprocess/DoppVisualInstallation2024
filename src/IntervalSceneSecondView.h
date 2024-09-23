#pragma once
#include "BaseView.h"

class IntervalSceneSecondView : public BaseView {

public:
	void setup(float _windowWidth, float _windowHeight) {

	}

	void update() {

	}

	void draw() {
		ofPushMatrix();

		ofPushStyle();
		ofSetColor(0, 255, 255);
		ofDrawRectangle(300, 100, 100, 100);

		ofPopStyle();
		ofPopMatrix();
	}

};