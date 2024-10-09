#pragma once
#include "BaseView.h"

class FaceGridNormalView : public BaseView {
private:
	bool bAfterStarted;
	float windowWidth;
	float windowHeight;

	ofFbo fbo;

	ofImage* imageFacesPtr;
	int imageMaxSize;

	// w_blocksマス * h_blocksマスの格子
	float w_blocks = 10;
	float h_blocks = 10;

	// 各マスで表示する写真のidx
	int imgGridIdx[10][10];

	float w_img;
	float h_img;


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

		// 1マスの画像サイズ算出
		w_img = windowWidth / w_blocks;
		h_img = windowHeight / h_blocks;

		fbo.allocate(windowWidth, windowHeight, GL_RGB);

		for (int j = 0; j < h_blocks; j++) {
			for (int i = 0; i < w_blocks; i++) {
				imgGridIdx[j][i] = ofRandom(0, imageMaxSize - 1);
			}
		}
	}

	void update(float now) {
		for (int j = 0; j < h_blocks; j++) {
			for (int i = 0; i < w_blocks; i++) {
				imgGridIdx[j][i] = ofRandom(0, imageMaxSize - 1);
			}
		}
		
		fbo.begin();
		ofClear(255);
		dispPict();
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

	void dispPict() {
		for (int j = 0; j < h_blocks; j++) {
			for (int i = 0; i < w_blocks; i++) {
				imageFacesPtr[imgGridIdx[j][i]].draw(i * w_img, 20 + j * h_img, w_img, w_img);
			}
		}
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