#pragma once
#include "BaseView.h"

class ProjectNameTransitionView : public BaseView {
private:
	float fLineHeight;
	int currentNameTextSize;
	static const int locationSize = 5;
	static const int nameTextRange = 28;
	int locationCounter = 0;
	int participantCounter = 0;
	bool bAfterStarted;

	ofSpherePrimitive sphere;
	float yAxis;
	ofEasyCam cam;
	ofTrueTypeFont font;  // �t�H���g�I�u�W�F�N�g���쐬
	std::string mainText = "Denshi\nOnkyo\nPeople";//\nPeople Project";
	std::string subText = "Live\n2023-2024";// "2023\n2024";

public:
	void setup(float _windowWidth, float _windowHeight) {
		font.load("font/OCRB.TTF", 48);  // �t�H���g�����[�h�A�T�C�Y48
	}

	void update() {
	}

	void draw() {
		// �J�����J�n
		cam.begin();
		ofRotateY(yAxis -= 0.5);

		// ��
		sphere.set(ofGetWidth() * 0.4, 16);
		sphere.setPosition(0, 0, 0);
		sphere.drawWireframe();

		ofTranslate(0, 0, ofGetWidth() * 0.4);  // ���S�Ɉړ�
		float textWidth = font.stringWidth(mainText);
		float textHeight = font.stringHeight(mainText);
		float subTextWidth = font.stringWidth(subText);
		float subTextHeight = font.stringHeight(subText);

		font.drawString(mainText, -textWidth / 2, textHeight / 2);  // ������𒆐S�ɕ`��

		ofTranslate(0, 0, -1 * ofGetWidth() * 0.4 * 2);  // ���S�Ɉړ�
		ofRotateY(180);
		font.drawString(subText, -subTextWidth / 2, subTextHeight / 2);  // ������𒆐S�ɕ`��
		// �J�����I��
		cam.end();
	}


	void start() {
		bAfterStarted = true;
	}

	void stop() {
		if (bAfterStarted) {
		}

	}

};