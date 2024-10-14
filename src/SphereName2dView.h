#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"
#include "ofApp.h"
#include <cmath>

// ãÖëÃîºåa ñßèWìx
static float GLOBALRADIUS = 100;

class ArtistName {
private:
	float angle;
	float r;
	float x;
	float y;
	float z;
	float radius;
	float speed;
	int col = 0;
	int plusMinus = 1;
	string name;
	ofTrueTypeFont font;

public:
	void setup(string artistName) {
		font.load("font/OCRB.TTF", 10);
		angle = ofRandom(0, 2 * PI);
		r = ofRandom(0, GLOBALRADIUS);
		x = cos(angle) * r;
		y = sin(angle) * r;
		z = 0; //-1 * ofRandom(0, 100);
		col = ofRandom(0, 255);
		radius = ofRandom(50, 1000);
		speed = ofRandom(0.1, 1);
		name = artistName;
	}

	void update() {
		col += plusMinus;

		if (plusMinus > 255 || plusMinus < 0) {
			plusMinus *= -1;
		}
	}

	// é¸ä˙â^ìÆ
	void dispName() {
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 + x, ofGetHeight() / 2 + y, z);
		// ofRotateY(ofGetElapsedTimef() * y * speed * -1); // Yé≤ÇíÜêSÇ…âÒì]Åiñàïb50ìxâÒì]Åj
		// ofRotateX(ofGetElapsedTimef() * x * speed * -1);
		// ofDrawAxis(200); // é≤Çï`âÊ

		// ï∂éöÇï`âÊ
		int shrink = GLOBALRADIUS;
		/*
		if (shrink > radius) {
			shrink = radius;
		}
		if (shrink < 0) {
			shrink = 0;
		}
		*/
		ofTranslate(0, 0, GLOBALRADIUS); //radius - GLOBALRADIUS); // ï∂éöÇÃà íuÇâÊñ ÇÃíÜâõÇ…ê›íË, zé≤Çà⁄ìÆ
		// ofDrawAxis(200); // é≤Çï`âÊ

		// ofSetColor(255); // ï∂éöÇÃêFÇîíÇ…ê›íË
		ofSetColor(col);
		font.drawString(name, 0, 0); // ï∂éöÇï`âÊ
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
		for (int i = 0; i < TestNameNum; i++) {
			names[i].dispName();
		}
	}


	void start() {
	}

	void stop() {
	}
};