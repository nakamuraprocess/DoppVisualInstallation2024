#pragma once
#include "BaseView.h"

class FaceRectDotView : public BaseView {
private:
    float windowWidth;
    float windowHeight;

    ofFbo fbo;

    ofImage* imageFacesPtr;
    int imageMaxSize;
    int randomIndex = 0;
    int center;

    // ‰ð‘œ“x
    float dotSize = 11;

    vector <ofPixels> imageFacesPixel;

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
        fbo.allocate(imageFacesPtr[0].getWidth(), imageFacesPtr[0].getHeight(), GL_RGB);
        fbo.setAnchorPoint(windowHeight * 0.5, 0);

        for (int i = 0; i < imageMaxSize; i++) {
            ofPixels tpmPixels = imageFacesPtr[i].getPixels();
            imageFacesPixel.push_back(tpmPixels);
        }

        ofSetCircleResolution(60);
    }

    void update(float now) {
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
#ifdef TARGET_LINUX_ARM
        ofTranslate(windowHeight, 0);
        ofRotate(90);
#endif
        fbo.draw(windowWidth * 0.5, 0, windowHeight, windowHeight);
        ofPopMatrix();
    }

    void dispPixel() {
        for (int h = 0; h < imageFacesPtr[randomIndex].getHeight(); h += dotSize) {
            for (int w = 0; w < imageFacesPtr[randomIndex].getWidth(); w += dotSize) {
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

    void start() {}

    void stop() {}

};