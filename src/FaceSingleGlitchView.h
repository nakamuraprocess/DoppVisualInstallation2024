#pragma once
#include "BaseView.h"
#include "ofApp.h"

class FaceSingleGlitchView : public BaseView {
private:
    ofImage* imageFacesPtr;
	int randomIndex = 0;
	float windowWidth;
	float windowHeight;
    // �\���s�N�Z���i�[
	std::vector<ofPixels> pixels;
    // �ǂݍ��މ摜��
	int imgCount = 10;
    int center;
    // �𑜓x
    int pixelResolution = 20;
    // �𑜓x���Z�o�܂��͔C�ӎw��
    int pixelSize;
    bool bEffectOn;
    // �G�t�F�N�g�e�X�g�쓮
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


        // �摜�f�[�^�̃r�b�g�}�b�v����z��Ɋi�[
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
        // �s�N�Z���\���T�C�Y�ŉ摜�̖��邳�̃����_����
        ofSetLineWidth((rand() % 50) * 0.1);
        for (int i = 0; i < windowHeight; i += pixelSize) {
            int rnd_size = 0;
            // ofSetLineWidth(rand() % 5);
            // �J�����Ŏ���Ȃ���Ƃ���y���W�ł���₷���Ȃ�Ƃ�
            if (bEffectOn || testFlag) {
                // �����s��
                // int rnd_row = rand() % 50;

                // ��������
                // 0��1
                int rnd_dir = rand() % 2;
                int dir = 1;

                // �����傫��
                rnd_size = rand() % 50 + 10;

                // ��
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

                // �^�C����
                // �����s��
                // ofRect(center + j + rnd_size, i, 8, 8);
            }
        }
	}
};