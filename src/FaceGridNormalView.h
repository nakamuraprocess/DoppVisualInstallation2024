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

	// 各マスのカウントタイミング
	// nが1-100,nの倍数の時にそのマスの写真を切り替える
	int cnt[10][10];

	// 切替速度
	int cnt_speed[10][10];
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

		for (int j = 0; j < h_blocks; j++) {
			for (int i = 0; i < w_blocks; i++) {
				cnt_speed[j][i] = 1;
			}
		}

		fbo.allocate(windowWidth, windowHeight, GL_RGB, 24);
	}

	void update() {
		++frame;

		if (frame > 1000) {
			frame = 1;
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
				imageFacesPtr[cnt[j][i]].draw(i * w_img, 20 + j * h_img, w_img, w_img);

				if (frame % cnt_speed[j][i] == 0 || true) {
					cnt[j][i] = ofRandom(0, imageMaxSize - 1);
					cnt_speed[j][i] = ofRandom(1, 10) * 10;
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