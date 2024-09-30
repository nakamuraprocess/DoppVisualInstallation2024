#pragma once
#include "BaseView.h"
#include "ofApp.h"

class FaceDotView : public BaseView {
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

    // ‰ð‘œ“x
    float dotRadius = 3;

    int wPixels;
    int hPixels;

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
        fbo.setAnchorPoint(windowHeight * 0.5, 0);

        wPixels = imageFacesPtr[0].getWidth();
        hPixels = imageFacesPtr[0].getHeight();

        ofSetCircleResolution(60);
    }

    void update() {
        randomIndex = ofRandom(0, imageMaxSize - 1);

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
        ofSetColor(255);
        // imageFacesPtr[randomIndex].draw(center, 0);
        for (int h = 0; h < hPixels; h++) {
            for (int w = 0; w < wPixels; w++) {
                // ‚»‚ÌÀ•W‚Ì–¾‚é‚³‚ðŽæ“¾
                ofColor col = imageFacesPtr[randomIndex].getColor(h, w);
                float rawLight = col.getBrightness();
                float mappedLight = ofMap(rawLight, 0, 255, 0, dotRadius);
                ofSetColor(col);

                ofDrawCircle(w * dotRadius * 2, h * dotRadius * 2, dotRadius);
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