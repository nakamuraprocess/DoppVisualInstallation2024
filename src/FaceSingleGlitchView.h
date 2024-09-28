#pragma once
#include "BaseView.h"
#include "ofApp.h"

class FaceSingleGlitchView : public BaseView {
private:
    bool bAfterStarted;
    float windowWidth;
    float windowHeight;

    ofFbo fbo;

    ofImage* imageFacesPtr;
    int imageMaxSize;
    int randomIndex = 0;
    float rowHeight = 2.0;
    int center;

    // エフェクトテスト作動
    int testFlag = 0;
    int noiseFlag = 0;
    int cnt[2];
    int cnt_idx = 1;

public:
    void setImgPtr(ofImage* ptr, const int size) {
        if (ptr == nullptr) {
            cout << "FaceSingleGlitchView::setImgPtr(ofImage* ptr) ptr is null" << endl;
        }
        else {
            imageFacesPtr = ptr;
            imageMaxSize = size;
        }
    }

    void setup(float _windowWidth, float _windowHeight) {
        windowWidth = _windowWidth;
        windowHeight = _windowHeight;
        center = (windowWidth / 2) - (imageFacesPtr[0].getWidth() / 2);
        fbo.allocate(imageFacesPtr[0].getWidth(), imageFacesPtr[0].getHeight(), GL_RGB, 24);
        fbo.setAnchorPoint(windowHeight* 0.5, 0);
    }

    void update() {
        randomIndex = ofRandom(0, imageMaxSize - 1);
        
        // インターバルの時
        if (cnt_idx) {
            cnt[cnt_idx]--;

            if (cnt[cnt_idx] < 0) {
                // ofLog() << "NOISE";
                cnt[cnt_idx] = ofRandom(1, 20);
                noiseFlag = 1;
                cnt_idx = 0;
            }
        }
        // ノイズ発生中
        else {
            cnt[cnt_idx]--;

            if (cnt[cnt_idx] < 0) {
                // ofLog() << "INTERVAL";
                cnt[cnt_idx] = ofRandom(1, 10);
                noiseFlag = 0;
                cnt_idx = 1;
            }
        }

        fbo.begin();
        ofClear(0);
        ofPushMatrix();
        ofTranslate(-center, 0);
        dispPixel();
        ofPopMatrix();
        fbo.end();
    }

    void draw() {
        ofPushMatrix();
        fbo.draw(windowWidth * 0.5, 0, windowHeight, windowHeight);
        ofPopMatrix();
    }

    void dispPixel() {
        for (int i = 0; i < imageFacesPtr[randomIndex].getHeight() / rowHeight; i++) {
            int rnd_size = 0;
            // ofSetLineWidth(rand() % 5);
            // カメラで手をなぞるとそのy座標でずれやすくなるとか
            if (testFlag || noiseFlag) {
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

            imageFacesPtr[randomIndex].drawSubsection(center + rnd_size, i * rowHeight, fbo.getWidth(), 1 * rowHeight, 0, i * rowHeight, fbo.getWidth(), rowHeight);
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