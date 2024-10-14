#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"
#include "ofApp.h"
#include <cmath>

// ãÖëÃîºåa ñßèWìx
static float GLOBALRADIUS = 250;

class ArtistName {
private:
	float angle;
	float r;
	float x;
	float y;
	float z;
	float moveX;
	float moveY;
	float speed;
	float moveAngle;
	float moveRange;
	int col;
	int isMoveX;
	int plusMinus;
	float rotateZ;
	string name;
	ofTrueTypeFont font;

public:
	void setup(string artistName) {
		font.load("font/OCRB.TTF", 10);
		angle = ofRandom(0, 2 * PI);
		r = ofRandom(5, GLOBALRADIUS);
		x = cos(angle) * r;
		moveX = x;
		y = sin(angle) * r;
		moveY = y;
		z = -1 * ofRandom(100, 400);
		col = ofMap(z, -100, -400, 255, 50);
		speed = ofRandom(0.05, 0.1);
		name = artistName;
		moveAngle = ofRandom(0, 360);
		// íÜêSÇ…ãﬂÇ¢ÇŸÇ«ëÂÇ´Ç≠â^ìÆÇ∑ÇÈ
		moveRange = ofRandom(5, ofMap(r, 5, GLOBALRADIUS, 40, 10));
		isMoveX = (ofRandom(0, 1) < 0.5) ? 0 : 1;
		plusMinus = (ofRandom(0, 1) < 0.5) ? -1 : 1;
		rotateZ = ofRandom(-15, 15);
	}

	void update() {
		/*
		if (isMoveX) {
			moveX = sin(moveAngle) * moveRange * plusMinus;
		}
		else {
			moveY = cos(moveAngle) * moveRange* plusMinus;
		}
		*/
		moveX = sin(moveAngle) * moveRange;
		moveY = cos(moveAngle) * moveRange;

		moveAngle += speed * plusMinus;
	}

	// é¸ä˙â^ìÆ
	void dispName() {
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 + x, ofGetHeight() / 2 + y, z);
		// ofDrawAxis(200); // é≤Çï`âÊ

		// âÒì]
		ofRotateZ(rotateZ);
		// âÒì]ÇµÇΩé≤ÇäÓèÄÇ…â^ìÆ
		ofTranslate(moveX, moveY);
		// ofDrawAxis(200);

		// ï∂éöÇï`âÊ
		int shrink = GLOBALRADIUS;

		ofSetColor(col);
		font.drawString(name, -font.stringWidth(name) / 2, 0); // ï∂éöÇï`âÊ
		// ofRect(0, 0, 100, 100);
		ofPopMatrix();
	}
};

class SphereName2dView : public BaseView {
private:
	float windowWidth;
	float windowHeight;

	float fLineHeight;
	int currentNameTextSize;
	static const int locationSize = 5;

	string textFiles[locationSize];
	vector <string> participants[locationSize];

	float zAxis = 0;
	float xAxis = 60;
	float moveAxis = 0;
	float TestZ = 0;
	float k = 1;

	vector <ArtistName> names;

	int TestNameNum = 200;

public:
	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

		textFiles[0] = "Tokyo College of Music";
		textFiles[1] = "Tokyo Denki University";
		textFiles[2] = "BankART Station";
		textFiles[3] = "Goethe-Institut Tokyo";
		textFiles[4] = "ZKM";

		// txtÉtÉ@ÉCÉãÇ©ÇÁñºëOì«Ç›çûÇ›
		for (int i = 0; i < locationSize; i++) {
			ofBuffer buffer = ofBufferFromFile("text/" + textFiles[i] + ".txt");
			if (buffer.size()) {
				for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
					string line = *it;
					if (line.empty() == false) {
						// äeâÔèÍÇÃéQâ¡é“Çäiî[ [âÔèÍidx][éQâ¡é“idx]
						participants[i].push_back(line);
					}
				}
			}
		}

		// èâä˙âª
		for (int i = 0; i < locationSize; i++) {
			int locationArtistSize = participants[i].size();
			for (int j = 0; j < locationArtistSize; j++) {
				ArtistName setName;
				setName.setup(participants[i][j]);

				names.push_back(setName);
			}
		}

		ofLog() << "ARTIST NUMBERS " << names.size();
	}

	void update() {
		
	}

	void draw() {
		ofBackground(0);

		for (int i = 0; i < TestNameNum; i++) {
			names[i].dispName();
			names[i].update();
		}
	}


	void start() {
	}

	void stop() {
		// ofLog() << "RESET";
		ofSetColor(255);
	}
};