#pragma once
#include "BaseView.h"

class NodeAndEdgeView : public BaseView {
private:
	float windowWidth;
	float windowHeight;

	ofFbo fbo;
	
	static const int pointMaxSize = 800;
	float radius = 400;
	float radiusLargeCircle = 240;
	float velocity = 0.1;
	float distance = 80;
	glm::vec3 posInitial[pointMaxSize];
	ofPoint point[pointMaxSize];
	float timeRecently = 0.0;

	ofImage imageTitle;


public:
	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;
		fbo.allocate(windowWidth, windowHeight, GL_RGB);
		for (int i = 0; i < pointMaxSize; i++) {
			posInitial[i] = glm::vec3(ofRandom(0, radius * 2), ofRandom(0, radius * 2), ofRandom(0, radius * 2));
		}

		imageTitle.load("logo/title.png");
	}


	void update(float now) {
		float timeDestination = now - timeRecently;
		timeDestination = ofClamp(timeDestination, 0.0, 0.1);
		timeRecently = now;

		for (int i = 0; i < pointMaxSize; i++) {
			posInitial[i] += velocity * timeDestination;
			point[i].x = ofSignedNoise(posInitial[i].x) * radius;
			point[i].y = ofSignedNoise(posInitial[i].y) * radius;
			point[i].z = ofSignedNoise(posInitial[i].z) * radius;
		}

		fbo.begin();
		ofClear(255);
		ofPushMatrix();
		ofTranslate(windowWidth * 0.5, windowHeight * 0.5);
		ofPushStyle();
		ofFill();
		ofSetColor(0, 155, 214, 25);
		ofDrawCircle(0, 0, radiusLargeCircle);
		
		for (int j = 0; j < pointMaxSize; j++) {
			float r = 0;
			float g = 155;
			float b = 214;
			float a = ofClamp(point[j].z, 5, 200);
			ofSetColor(r, g, b, a);
			for (int k = j + 1; k < pointMaxSize; k++) {
				if (ofDist(point[j].x, point[j].y, point[j].z, point[k].x, point[k].y, point[k].z) < distance) {
					ofDrawLine(point[j], point[k]);
				}
			}
			ofDrawCircle(point[j], 2);
		}
		ofNoFill();
		ofSetColor(0, 155, 214, 135);
		ofDrawCircle(0, 0, radiusLargeCircle);

		ofPopStyle();
		ofPopMatrix();
		imageTitle.draw(0, windowHeight - (imageTitle.getHeight() * 0.5), imageTitle.getWidth() * 0.5, imageTitle.getHeight() * 0.5);
		fbo.end();
	}


	void draw() {
		ofPushMatrix();
#ifdef TARGET_LINUX_ARM
		ofTranslate(windowHeight, 0);
		ofRotate(90);
#endif
		fbo.draw(0, 0);
		ofPopMatrix();
	}


	void start() {}

	void stop() {}

};