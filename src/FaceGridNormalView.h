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

	// nフレームごとに行の画像を切替
	int changeRowFrame = 5;
	// 切り替える行
	int activeRow = 0;

	// 各マスで表示する写真のidx
	int imgGridIdx[10][10];

	float w_img;
	float h_img;
	// 読み込む画像数
	int frame = 0;

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

		fbo.allocate(windowWidth, windowHeight, GL_RGB, 24);
	}

	void update() {
		++frame;

		if (frame > 1000) {
			frame = 1;
		}

		if (frame % changeRowFrame == 0) {
			++activeRow;
			activeRow %= 10;
		}

		fbo.begin();
		ofClear(255);
		dispPict();
		fbo.end();
	}

	void draw() {
		fbo.draw(0, 0);
	}

	void dispPict() {
		for (int j = 0; j < h_blocks; j++) {
			for (int i = 0; i < h_blocks; i++) {
				// 画像表示
				imageFacesPtr[imgGridIdx[j][i]].draw(i * w_img, 20 + j * h_img, w_img, w_img);

				if (activeRow == j) {
					imgGridIdx[j][i] = ofRandom(0, imageMaxSize - 1);
				}
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