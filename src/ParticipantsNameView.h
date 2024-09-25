#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"

class ParticipantsNameView : public BaseView {
private:
	ofTrueTypeFont font;
	vector <string> participantsname;
	vector <ofxShuffleText> shuffleText;
	float fLineHeight;

public:
	void setup(float _windowWidth, float _windowHeight) {
		ofBuffer buffer = ofBufferFromFile("text/list.txt");
		if (buffer.size()) {
			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				string line = *it;
				if (line.empty() == false) {
					participantsname.push_back(line);
				}
			}
		}

		font.load("font/OCRB.TTF", 20);
		fLineHeight = font.getLineHeight() + 2;

		for (int i = 0; i < participantsname.size(); i++) {
			ofxShuffleText tmp;
			tmp.setup(font, participantsname[i]);
			tmp.setRandomChars(OFX_SHUFFLE_TEXT_NUMBERS | OFX_SHUFFLE_TEXT_UPPER_LETTERS | OFX_SHUFFLE_TEXT_LOWER_LETTERS | OFX_SHUFFLE_TEXT_SYMBOLS);
			shuffleText.push_back(tmp);
		}
	}

	void update() {
		for (int i = 0; i < participantsname.size(); i++) {
			shuffleText[i].update();
		}
	}

	void draw() {
		ofPushMatrix();
		ofPushStyle();

		ofSetColor(255);
		for (int i = 0; i < participantsname.size(); i++) {
			float height = fLineHeight * (i + 1);
			shuffleText[i].draw(20, height);
		}

		ofPopStyle();
		ofPopMatrix();
	}


	void start() {
		for (int i = 0; i < participantsname.size(); i++) {
			float delay = 100.0 * i;
			shuffleText[i].start(1.0, delay, false, 10);
		}
	}

	void stop() {

	}

};