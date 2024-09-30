#pragma once

#include "ofMain.h"
#include "FaceSingleGlitchView.h"
#include "FaceGridNormalView.h"
#include "ParticipantsNameView.h"
#include "ProjectNameTransitionView.h"

class ofApp : public ofBaseApp {

	public:
		~ofApp();
		void setup();
		void update();
		void draw();

		void timer(float now);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int sceneIndex = 0;
		int sceneCounter = 1;
		int sceneMaxSize = 0;
		int sceneIntervalMillis = 5000;

		vector <BaseView*> views;

		float windowWidth;
		float windowHeight;
		
		static const int faceDataMaxSize = 159;
		ofImage imageFacesData[faceDataMaxSize];
		
		float timerLapTime = 0.0;
		float timerSleepTime = 5.0;
};
