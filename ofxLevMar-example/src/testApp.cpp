#include "testApp.h"

/**
 You must create a class that extends Mode<float or double>
 You then pass an instance of this class to the Fit to find the fit parameters. Your model performs a transform between input and output, e.g:
 
 y = m*x + c
 
 This linear fit has:
		2 parameters m, c
		1 input x
		1 output y
 **/

class TrivialModel : public Model<float> {
public:
	TrivialModel() :	Model<float>(1, 1, 2) { }
	void evaluate(pfitDataPoint<float>& point, const vector<float> &parameters) const {
		
		float& x (*point.getInput());
		float& y (*point.getOutput());
		
		const float& m (parameters[0]);
		const float& c (parameters[1]);
		
		y = m * x + c;
	}
};

class TraRotModel : public Model<float> {
public:
	TraRotModel() :	Model<float>(3, 3, 3) { }
	void evaluate(pfitDataPoint<float>& point, const vector<float> &parameters) const {
		
		ofVec3f &in(*(ofVec3f*)point.getInput());
		ofVec3f &out(*(ofVec3f*)point.getOutput());
		
		ofVec3f &tra(*(ofVec3f*)&parameters[0]);
		//ofVec3f &rot(*(ofVec3f*)&parameters[1]);
		
		//rotate then translate
		out = in + tra;
	}
};

//--------------------------------------------------------------
void testApp::setup(){
	testTrivial();
	std::exit(0);
	testTransform();
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	camera.begin();
	camera.end();
	ofDrawBitmapString(ofToString(translation), 10, 10);
	ofDrawBitmapString(ofToString(translationFitted), 10, 20);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::testTrivial() {
	Fit<float> fit;
	pfitDataSetf set;
	set.init(1, 1, 10);
	
	float x;
	for (int i=0; i<10; i++) {
		x = float(i) / 10.0f;
		set.getInput()[i] = x;
		set.getOutput()[i] = 3.0f*x + -5.0f;
	}
	
	vector<float> parameters = fit.correlate(set, TrivialModel());
	
	cout << "Results: m=" << parameters[0] << " c=" << parameters[1] << endl;
	cout << endl;
}

//--------------------------------------------------------------
void testApp::testTransform() {
	
	input.resize(COUNT);
	transformed.resize(COUNT);
	
	for (int i=0; i<COUNT; i++)
		input[i] = ofVec3f(ofRandom(-5, 5),
						   ofRandom(-5, 5),
						   ofRandom(-5, 5));
	
	translation = ofVec3f(ofRandom(-10, 10),
						  ofRandom(-10, 10),
						  ofRandom(-10, 10));
	
	//	rotation.makeRotate(ofRandom(360), 0.2, 0.1, 0.3);
	
	transformed.resize(COUNT);
	ofVec3f t;
	for (int i=0; i<COUNT; i++) {
		//		t = input[i] * rotation + translation;
		t = input[i] + translation;
		transformed[i] = t;
	}
	
	pfitDataSetf dataSet = ofxPolyfit::makeDataSet(input, transformed);
	parameters = vector<float>(3, 0);
	
	fit.correlate(dataSet, TraRotModel(), parameters, 100);
	
	translationFitted = *(ofVec3f*)&parameters[0];
	
	cout << translation << endl;
	cout << translationFitted << endl;
}
