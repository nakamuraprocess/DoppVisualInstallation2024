#pragma once
#include "BaseView.h"
#include "ofApp.h"

class FaceSingleGlitchView : public BaseView {
private:
    ofImage* imageFacesPtr;
	int randomIndex = 0;
	float windowWidth;
	float windowHeight;
    // 表示ピクセル格納
	std::vector<ofPixels> pixels;
    // 読み込む画像数
	int imgCount = 10;
    int center;
    // 解像度
    int pixelResolution = 20;
    // 解像度より算出または任意指定
    int pixelSize;
    bool bEffectOn;
    // エフェクトテスト作動
    int testFlag = 0;

public:
    void setImgPtr(ofImage* ptr) {
        if (ptr == nullptr) {
            cout << "FaceSingleGlitchView::setImgPtr(ofImage* ptr) ptr is null" << endl;
        }
        else {
            imageFacesPtr = ptr;
        }
    }

	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

        // pixelSize = ofGetWidth() / pixelResolution;
        pixelSize = 5;


        // 画像データのビットマップ情報を配列に格納
        for (int i = 0; i < imgCount; i++) {
            pixels.push_back(imageFacesPtr[i].getPixels());
        }

        center = (windowWidth / 2) - (imageFacesPtr[0].getWidth() / 2);
	}

	void update() {
		randomIndex = ofRandom(0, imgCount - 1);

        if (ofRandomf() > 0.3) {
            bEffectOn = true;
        }
        else {
            bEffectOn = false;
        }
	}

	void draw() {
        dispPixel();
	}

	void dispPixel() {
        // ピクセル表示サイズで画像の明るさのランダム性
        ofSetLineWidth((rand() % 50) * 0.1);
        for (int i = 0; i < windowHeight; i += pixelSize) {
            int rnd_size = 0;
            // ofSetLineWidth(rand() % 5);
            // カメラで手をなぞるとそのy座標でずれやすくなるとか
            if (bEffectOn || testFlag) {
                // 乱れる行数
                // int rnd_row = rand() % 50;

                // 乱れる向き
                // 0か1
                int rnd_dir = rand() % 2;
                int dir = 1;

                // 乱れる大きさ
                rnd_size = rand() % 50 + 10;

                // 左
                if (!rnd_dir) {
                    dir *= -1;
                }

                rnd_size *= dir;
            }

            for (int j = 0; j < windowHeight; j += pixelSize) {
                ofColor col = pixels[randomIndex].getColor(j, i);

                /*
                int r = rand() % 255;
                int g = rand() % 255;
                int b = rand() % 255;
                */

                ofSetColor(col);
                ofDrawRectangle(center + j + rnd_size, i, pixelSize, pixelSize);

                // タイル風
                // 原因不明
                // ofRect(center + j + rnd_size, i, 8, 8);
            }
        }
	}
};