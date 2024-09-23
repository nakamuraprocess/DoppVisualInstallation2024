#pragma once
#include "BaseView.h"
#include "ofApp.h"

class FaceSingleGlitchView : public BaseView {
private:
	std::vector<ofImage> faces;
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
    int press_key;
    // �G�t�F�N�g�e�X�g�쓮
    int testFlag = 0;

public:
	void setup() {
		windowWidth = 600;
		windowHeight = 1024;
        // pixelSize = ofGetWidth() / pixelResolution;
        pixelSize = 5;

		for (int i = 0; i < imgCount; i++) {
			ofImage tmpImg;
			bool load = tmpImg.load("images/" + ofToString(i + 1) + "-test.png");
			tmpImg.resize(windowHeight, windowHeight);
            tmpImg.setImageType(OF_IMAGE_COLOR);
			faces.push_back(tmpImg);

            if (!load) {
                ofLog() << "Failed to load image: " << "images/" + ofToString(i + 1) + "-test.png";
                continue;
            }

			cout << faces[i].getWidth() << " : " << faces[i].getHeight() << " : " << tmpImg.getPixels().getNumChannels() << endl;

			// �摜�f�[�^�̃r�b�g�}�b�v����z��Ɋi�[
			pixels.push_back(tmpImg.getPixels());
		}

        center = (windowWidth / 2) - (faces[0].getWidth() / 2);
	}

	void update() {
		randomIndex = ofRandom(0, imgCount - 1);
	}

	void draw() {
        /*
		ofPushMatrix();
		ofSetRectMode(OF_RECTMODE_CENTER);
		faces[randomIndex].draw(windowWidth * 0.5, windowHeight * 0.5, 640 * (windowHeight / 640), windowHeight);
        ofPopMatrix();
        */
        dispPixel();
	}

	void dispPixel() {
        // �s�N�Z���\���T�C�Y�ŉ摜�̖��邳�̃����_����
        ofSetLineWidth((rand() % 50) * 0.1);
        for (int i = 0; i < windowHeight; i += pixelSize) {
            int rnd_size = 0;
            // ofSetLineWidth(rand() % 5);
            // �J�����Ŏ���Ȃ���Ƃ���y���W�ł���₷���Ȃ�Ƃ�
            if (press_key || testFlag) {
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

    void mousePressed(int x, int y, int button) {
        // ���N���b�N
        ofLog() << button;
        if (button == 0) {
            press_key = true;
        }
    }

    void mouseReleased(int x, int y, int button) {
        if (button == 0) {
            press_key = false;
        }
    }
};