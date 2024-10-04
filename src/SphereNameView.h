#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"
#include "ofApp.h"

class ArtistName {
private:
	string name;
	float x;
	float y;
	float z;
	float radius;
	ofTrueTypeFont font;

public:
	void setup(string artistName) {
		font.load("font/OCRB.TTF", 18);
		x = ofRandom(50, 100);
		y = ofRandom(50, 100);
		radius = ofRandom(50, 200);
		name = artistName;
	}

	void update() {

	}

	void dispName() {
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0); // �����̈ʒu����ʂ̒����ɐݒ肵�AZ=100�Ɉړ�
		ofRotateY(ofGetElapsedTimef() * y); // Y���𒆐S�ɉ�]�i���b50�x��]�j
		ofRotateX(ofGetElapsedTimef() * x);
		// ofDrawAxis(200); // ���̃T�C�Y��ݒ�

		// ������`��
		ofTranslate(0, 0,radius); // �����̈ʒu����ʂ̒����ɐݒ肵�AZ=100�Ɉړ�
		// ofDrawAxis(200); // ���̃T�C�Y��ݒ�

		ofSetColor(255); // �����̐F�𔒂ɐݒ�
		font.drawString(name, 0, 0); // ������`��
		// ofRect(0, 0, 100, 100);
		ofPopMatrix();
	}
};

class SphereNameView : public BaseView {
private:
	bool bAfterStarted;
	float windowWidth;
	float windowHeight;

	ofFbo fbo;

	float fLineHeight;
	int currentNameTextSize;
	static const int locationSize = 5;
	static const int nameTextRange = 28;
	int locationCounter = 0;
	int participantCounter = 0;

	ofTrueTypeFont font;
	string textFiles[locationSize];
	string locations[locationSize];
	vector <string> participants[locationSize];
	ofxShuffleText shuffleParticipants[nameTextRange];
	ofxShuffleText shuffleLocation;

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

		for (int i = 0; i < TestNameNum; i++) {
			ArtistName setName;
			setName.setup("SHIBAYAMA TAKURO");

			names.push_back(setName);
		}

		textFiles[0] = "Tokyo College of Music";
		locations[0] = "- Tokyo College of Music";
		textFiles[1] = "Tokyo Denki University";
		locations[1] = "- Tokyo Denki University";
		textFiles[2] = "BankART Station";
		locations[2] = "- BankART Station";
		textFiles[3] = "Goethe-Institut Tokyo";
		locations[3] = "- Goethe-Institut Tokyo";
		textFiles[4] = "ZKM";
		locations[4] = "- ZKM [Germany}";

		for (int i = 0; i < locationSize; i++) {
			ofBuffer buffer = ofBufferFromFile("text/" + textFiles[i] + ".txt");
			if (buffer.size()) {
				for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
					string line = *it;
					if (line.empty() == false) {
						// �e���̎Q���҂��i�[ [���idx][�Q����idx]
						participants[i].push_back(line);
					}
				}
			}
		}

		font.load("font/OCRB.TTF", 18);
		fLineHeight = font.getLineHeight();

		shuffleLocation.setup(font, locations[locationCounter]);
		shuffleLocation.setRandomChars(OFX_SHUFFLE_TEXT_NUMBERS | OFX_SHUFFLE_TEXT_UPPER_LETTERS | OFX_SHUFFLE_TEXT_LOWER_LETTERS | OFX_SHUFFLE_TEXT_SYMBOLS);

		for (int i = 0; i < nameTextRange; i++) {
			shuffleParticipants[i].setup(font, "");
			shuffleParticipants[i].setRandomChars(OFX_SHUFFLE_TEXT_NUMBERS | OFX_SHUFFLE_TEXT_UPPER_LETTERS | OFX_SHUFFLE_TEXT_LOWER_LETTERS | OFX_SHUFFLE_TEXT_SYMBOLS);
		}

		fbo.allocate(windowWidth, windowHeight, GL_RGB);
	}

	void update() {
		moveAxis += 1;

		if (moveAxis > 360) {
			moveAxis = 0;
		}

		TestZ = TestZ + 10 * k;

		if (TestZ > 1000 || TestZ < -1000) {
			k *= -1;
		}
	}

	void draw() {
		/*
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0); // �����̈ʒu����ʂ̒����ɐݒ肵�AZ=100�Ɉړ�
		ofRotateY(ofGetElapsedTimef() * 50); // Y���𒆐S�ɉ�]�i���b50�x��]�j
		ofRotateX(ofGetElapsedTimef() * 50);
		ofDrawAxis(200); // ���̃T�C�Y��ݒ�

		// ������`��
		ofPushMatrix();
		ofTranslate(0, 0, 300); // �����̈ʒu����ʂ̒����ɐݒ肵�AZ=100�Ɉړ�
		ofDrawAxis(200); // ���̃T�C�Y��ݒ�

		ofSetColor(255); // �����̐F�𔒂ɐݒ�
		font.drawString("Hello", 0, 0); // ������`��
		ofPopMatrix();
		*/

		for (int i = 0; i < TestNameNum; i++) {
			names[i].dispName();
		}
	}


	void start() {
	}

	void stop() {
	}
};