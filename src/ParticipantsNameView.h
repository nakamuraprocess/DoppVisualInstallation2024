#pragma once
#include "BaseView.h"
#include "ofxShuffleText.h"

class ParticipantsNameView : public BaseView {
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

public:
	void setup(float _windowWidth, float _windowHeight) {
		windowWidth = _windowWidth;
		windowHeight = _windowHeight;

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
			ofBuffer buffer = ofBufferFromFile("text/"+ textFiles[i] + ".txt");
			if (buffer.size()) {
				for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
					string line = *it;
					if (line.empty() == false) {
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

	void update(float now) {
		shuffleLocation.update();
		for (int i = 0; i < nameTextRange; i++) {
			shuffleParticipants[i].update();
		}

		fbo.begin();
		ofClear(0);
		ofPushMatrix();
		ofPushStyle();

		ofSetColor(255);
		shuffleLocation.draw(20, 34);;
		for (int i = 0; i < nameTextRange; i++) {
			float height = fLineHeight * (i + 1);
			shuffleParticipants[i].draw(20, height + 34);
		}

		ofPopStyle();
		ofPopMatrix();
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


	void start() {
		int currentNameTextTotal = nameTextRange + (participantCounter * nameTextRange);
		if (currentNameTextTotal > participants[locationCounter].size()) {
			currentNameTextSize = (int)participants[locationCounter].size() - (participantCounter * nameTextRange);
		}
		else if (participants[locationCounter].size() >= nameTextRange) {
			currentNameTextSize = nameTextRange;
		}
		else {
			currentNameTextSize = participants[locationCounter].size();
		}

		shuffleLocation.setText(locations[locationCounter]);

		for (int i = 0; i < nameTextRange; i++) {
			if (i < currentNameTextSize) {
				int index = i + (participantCounter * nameTextRange);
				shuffleParticipants[i].setText(participants[locationCounter][index]);
			}
			else {
				shuffleParticipants[i].setText("");
			}
		}

		shuffleLocation.start(2.0, 0.0, false, 10);
		for (int i = 0; i < nameTextRange; i++) {
			float delay = 50.0 * (i + 1);
			shuffleParticipants[i].start(1.0, delay, false, 10);
		}

		bAfterStarted = true;
	}

	void stop() {
		if (bAfterStarted) {
			bAfterStarted = false;
			participantCounter++;

			if ((int)participants[locationCounter].size() <= participantCounter * nameTextRange) {
				participantCounter = 0;
				locationCounter++;
				if (locationCounter >= locationSize) {
					locationCounter = 0;
				}
			}
		}
		
	}

};