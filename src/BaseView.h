#pragma once

class BaseView {
public:
	
	virtual void setImgPtr(ofImage* ptr) {}

	virtual void setup(float _windowWidth, float _windowHeight) {}

	virtual void update() {}

	virtual void draw() {}

	virtual void start() {}

	virtual void stop() {}

};