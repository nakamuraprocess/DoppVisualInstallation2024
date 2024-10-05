#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef TARGET_LINUX_ARM
	ofSetupOpenGL(1024, 600, OF_FULLSCREEN);
#else
	ofSetupOpenGL(600, 1024, OF_WINDOW);
#endif
	ofRunApp(new ofApp());
}