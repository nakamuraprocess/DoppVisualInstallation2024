#pragma once
#include "BaseView.h"

class IntervalSceneFirstView : public BaseView {

public:
	void setup() {

	}

	void update() {

	}

	void draw() {
		ofPushMatrix();

		ofPushStyle();
		ofSetColor(255, 255, 0);
		ofDrawRectangle(100, 100, 100, 100);

		ofPopStyle();
		ofPopMatrix();
	}

};