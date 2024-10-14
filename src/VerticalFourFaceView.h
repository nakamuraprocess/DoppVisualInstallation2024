#pragma once
#include "BaseView.h"

class VerticalFourFaceView : public BaseView {
private:
	float windowWidth;
	float windowHeight;

	ofFbo fbo;

	ofImage* imageFacesPtr;
	int imageMaxSize;

	int center;

	float imgHeight;
	
	// 1列に表示する写真の行数
	float imgRow;


public:
	void setImgPtr(ofImage* ptr, int size) {
		if (ptr == nullptr) {
			cout << "FaceGridNormalView::setImgPtr(ofImage* ptr) ptr is null" << endl;
		}
		else {
			imageFacesPtr = ptr;
			imageMaxSize = size;
		}
	}

	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		imgRow = 5;
		// 不明: 最後に2で割る
		imgHeight = windowHeight / imgRow / 2;
		ofLog() << imgHeight;

		center = (windowWidth / 2) - (imageFacesPtr[0].getWidth() / 2);
		fbo.allocate(imageFacesPtr[0].getWidth(), imageFacesPtr[0].getHeight(), GL_RGB);
		fbo.setAnchorPoint(windowHeight * 0.5, 0);
	}

	void update(float now) {
		fbo.begin();
		ofClear(0);
		ofPushMatrix();
		dispPict();
		// ofTranslate(-center, 0);
		ofPopMatrix();
		fbo.end();
	}

	void draw() {
		ofPushMatrix();
#ifdef TARGET_LINUX_ARM
		ofTranslate(windowHeight, 0);
		ofRotate(90);
#endif
		fbo.draw(windowWidth * 0.5, 0, windowHeight, windowHeight);
		ofPopMatrix();
	}

	void dispPict() {
		for (int i = 0; i < imgRow; i++) {
			int rndImgIdx = (int)ofRandom(0, imageMaxSize);
			float h = imgHeight * i;
			ofImage tmpImg = imageFacesPtr[rndImgIdx];

			tmpImg.crop(0, 150, tmpImg.getWidth(), tmpImg.getHeight() / 2);
			// 切り抜いた部分を描画
			tmpImg.draw(0, h);
			
			/*
			ofSetColor(ofRandom(0, 255));
			ofRect(0, h, ofGetWidth(), imgHeight);
			*/
		}
	}

	void start() {}

	void stop() {}

};