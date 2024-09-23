#pragma once
#include "BaseView.h"

class IntervalSceneThirdView : public BaseView {

public:
	void setup(float _windowWidth, float _windowHeight) {

	}

	void update() {

	}

	void draw() {
		ofPushMatrix();

		ofPushStyle();
		ofSetColor(255, 0, 255);
		ofDrawRectangle(500, 100, 100, 100);

		ofPopStyle();
		ofPopMatrix();
	}

};