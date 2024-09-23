#pragma once
#include "BaseView.h"

class FaceGridNormalView : public BaseView {

public:
	void setup() {

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

};