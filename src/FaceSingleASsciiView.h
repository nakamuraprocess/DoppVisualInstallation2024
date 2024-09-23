#pragma once
#include "BaseView.h"

class FaceSingleASsciiView : public BaseView {

public:
	void setup() {

	}

	void update() {

	}

	void draw() {
		ofPushMatrix();

		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofDrawRectangle(400, 100, 100, 100);

		ofPopStyle();
		ofPopMatrix();
	}

};