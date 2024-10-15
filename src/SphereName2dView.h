#pragma once
#include "BaseView.h"

class ArtistName {

public:
	string name;
	float angle;
	float radiusX;
	float radiusY;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float speed;
	float moveAngle;
	float moveRangeX;
	float moveRangeY;
	int alpha;
	int plusMinus;

	void setName(string artistName) {
		name = artistName;
	}
	
	void setup(int counter, int size) {
		angle = ofMap(counter, 0.0, (float)size, 0.0, TWO_PI);
		radiusX = ofRandom(50, 240);
		radiusY = ofMap(radiusX, 50, 240, 120, 500);
		posX = cos(angle) * radiusX;
		posY = sin(angle) * radiusY;
		moveX = posX;
		moveY = posY;
		moveAngle = ofRandom(0, 360);
		moveRangeX = 16;
		moveRangeY = 7;
		alpha = ofRandom(220, 255);
		speed = ofRandom(0.01, 0.04);
		plusMinus = (ofRandom(0, 1) < 0.5) ? -1 : 1;
	}
};

class SphereName2dView : public BaseView {
private:
	float windowWidth;
	float windowHeight;

	ofFbo fbo;

	ofTrueTypeFont font;
	static const int locationSize = 7;

	string textFiles[locationSize];
	vector <ArtistName> artistNames;

public:
	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;
		fbo.allocate(windowWidth, windowHeight, GL_RGB);

		font.load("font/OCRB.TTF", 10);

		textFiles[0] = "Tokyo College of Music";
		textFiles[1] = "Tokyo Denki University";
		textFiles[2] = "BankART Station";
		textFiles[3] = "Goethe-Institut Tokyo";
		textFiles[4] = "Festival Futura";
		textFiles[5] = "Scenkonst Museet";
		textFiles[6] = "ZKM";

		for (int i = 0; i < locationSize; i++) {
			ofBuffer buffer = ofBufferFromFile("text/" + textFiles[i] + ".txt");
			if (buffer.size()) {
				for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
					string line = *it;
					if (line.empty() == false) {
						ArtistName setName;
						setName.setName(line);
						artistNames.push_back(setName);
					}
				}
			}
		}

		for (int i = 0; i < artistNames.size(); i++) {
			artistNames[i].setup(i, (int)artistNames.size());
		}
	}


	void update(float now) {
		for (int i = 0; i < artistNames.size(); i++) {
			artistNames[i].moveX = sin(artistNames[i].moveAngle) * artistNames[i].moveRangeX;
			artistNames[i].moveY = cos(artistNames[i].moveAngle) * artistNames[i].moveRangeY;
			artistNames[i].moveAngle += artistNames[i].speed * artistNames[i].plusMinus;
		}

		fbo.begin();
		ofClear(255);
		for (int i = 0; i < artistNames.size(); i++) {
			ofPushMatrix();
			ofTranslate(windowWidth * 0.5 + artistNames[i].posX, windowHeight * 0.5 + artistNames[i].posY);
			ofTranslate(artistNames[i].moveX, artistNames[i].moveY);
			ofPushStyle();
			float r = 0;
			float g = 155;
			float b = 214;
			ofSetColor(r, g, b, artistNames[i].alpha);
			font.drawString(artistNames[i].name, -font.stringWidth(artistNames[i].name) * 0.5, 0);
			ofPopStyle();
			ofPopMatrix();
		}
		fbo.end();
	}


	void draw() {
		ofPushMatrix();
#ifdef TARGET_LINUX_ARM
		ofTranslate(windowHeight, 0);
		ofRotate(90);
#endif
		fbo.draw(0, 0);
		ofPopMatrix();
	}


	void start() {}

	void stop() {}
};