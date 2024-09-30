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
	ofTrueTypeFont font;  // フォントオブジェクトを作成
	std::string mainText = "Denshi\nOnkyo\nPeople";//\nPeople Project";
	std::string subText = "Live\n2023-2024";// "2023\n2024";

public:
	void setup(float _windowWidth, float _windowHeight) {
		font.load("font/OCRB.TTF", 48);  // フォントをロード、サイズ48
	}

	void update() {
	}

	void draw() {
		// カメラ開始
		cam.begin();
		ofRotateY(yAxis -= 0.5);

		// 球
		sphere.set(ofGetWidth() * 0.4, 16);
		sphere.setPosition(0, 0, 0);
		sphere.drawWireframe();

		ofTranslate(0, 0, ofGetWidth() * 0.4);  // 中心に移動
		float textWidth = font.stringWidth(mainText);
		float textHeight = font.stringHeight(mainText);
		float subTextWidth = font.stringWidth(subText);
		float subTextHeight = font.stringHeight(subText);

		font.drawString(mainText, -textWidth / 2, textHeight / 2);  // 文字列を中心に描画

		ofTranslate(0, 0, -1 * ofGetWidth() * 0.4 * 2);  // 中心に移動
		ofRotateY(180);
		font.drawString(subText, -subTextWidth / 2, subTextHeight / 2);  // 文字列を中心に描画
		// カメラ終了
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