#pragma once

#include "ofMain.h"

#include "ofxGrabCam.h"
#include "ofxLevMar.h"
#include "ofxPolyFit.h"

#define COUNT 100

using namespace ofxLevMar;

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);

	ofxGrabCam camera;
	
	Fit<float> fit;
	vector<float> parameters;
	
	vector<ofVec3f> input;
	vector<ofVec3f> transformed;
	
	ofVec3f translation;
	ofQuaternion rotation;
	
	ofVec3f translationFitted;
	
protected:
	void testTrivial();
	void testTransform();
};
