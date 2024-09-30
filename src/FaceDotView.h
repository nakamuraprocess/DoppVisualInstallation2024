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
    float dotSize = 25;

    int imageWidth;
    int imageHeight;

    static const int maxImageSize = 159;

    ofPixels imageFacesPixel[maxImageSize];

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

        imageWidth = imageFacesPtr[0].getWidth();
        imageHeight = imageFacesPtr[0].getHeight();

        for (int i = 0; i < maxImageSize; i++) {
            imageFacesPixel[i] = imageFacesPtr[i].getPixels();
        }

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
        for (int h = 0; h < imageHeight; h += dotSize) {
            for (int w = 0; w < imageWidth; w += dotSize) {
                // ‚»‚ÌÀ•W‚Ì–¾‚é‚³‚ðŽæ“¾
                ofColor col = imageFacesPixel[randomIndex].getColor(w, h);
                float monoColor = col.getBrightness();
                float mappedLightSize = ofMap(monoColor, 0, 255, 0, dotSize);
                ofSetColor(col);
                // ofSetColor(monoColor);

                // ofDrawCircle(center + w, h, mappedLightSize);
                ofDrawRectangle(center + w, h, mappedLightSize, mappedLightSize);
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