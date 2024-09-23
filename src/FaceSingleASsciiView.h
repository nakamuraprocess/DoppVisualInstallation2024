#pragma once
#include "BaseView.h"

class FaceSingleASsciiView : public BaseView {
private:
	ofImage* imageFacesPtr;

public:
	void setImgPtr(ofImage* ptr) {
		if (ptr == nullptr) {
			cout << "FaceSingleASsciiView::setImgPtr(ofImage* ptr) ptr is null" << endl;
		}
		else {
			imageFacesPtr = ptr;
		}
	}

	void setup(float _windowWidth, float _windowHeight) {

	}

	void update() {

	}

	void draw() {

	}

};