#pragma once

class BaseView {
public:
	
	virtual void setImgPtr(ofImage* ptr, int size) {}

	virtual void setup(float _windowWidth, float _windowHeight) {}

	virtual void update(float now) {}

	virtual void draw() {}

	virtual void start() {}

	virtual void stop() {}

};