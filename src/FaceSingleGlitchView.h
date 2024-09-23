#pragma once
#include "BaseView.h"

class FaceSingleGlitchView : public BaseView {
private:
	ofImage faces[65];
	int randomIndex = 0;
	float windowWidth;
	float windowHeight;

public:
	void setup() {
		windowWidth = 600;
		windowHeight = 1024;

		for (int i = 0; i < 65; i++) {
			faces[i].load("images/" + ofToString(i) + "-test.png");
			cout << faces[i].getWidth() << " : " << faces[i].getWidth() << endl;
		}
	}

	void update() {
		randomIndex = ofRandom(0, 65);
	}

	void draw() {
		ofPushMatrix();
		ofSetRectMode(OF_RECTMODE_CENTER);
		faces[randomIndex].draw(windowWidth * 0.5, windowHeight * 0.5, 640 * (windowHeight / 640), windowHeight);
		ofPopMatrix();
	}

};