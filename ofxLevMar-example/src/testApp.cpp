#include "testApp.h"

#include "TrivialModel.h"
#include "TraRotModel.h"

void testApp::setup(){
	
	pfitDataPointd point1(3,3);
	
	for (int i=0; i<3; i++)
	{
		point1.getInput()[i] = i;
		point1.getOutput()[i] = i + 10;
	}
	pfitDataPointd point2 = point1.makeCopy();
	
	testTrivial();
	testTraRot();
	std::exit(0);
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
	Fit<double> fit;
	TrivialModel model;
	
	pfitDataSetd set;
	set.init(1, 1, 10);
	
	float range = 10.0;
	
	float x;
	float xStep = range / double(set.size());
	for (int i=0; i<set.size(); i++) {
		x = double(i) * xStep;
		set.getInput()[i] = x;
		set.getOutput()[i] = model.evaluate(x, 5, -0.1, 1);
	}
	
	vector<double> parameters = fit.correlate(set, model);
	
	cout << "Results: ";
	for (int i=0; i<3; i++) {
		if (i!=0)
			cout << ", ";
		cout << parameters[i];
	}
	cout << endl;
}

//--------------------------------------------------------------
void testApp::testTraRot() {
	const int n = 100;
	
	ofVec3f R(30, 10, 50);
	ofVec3f T(0.4, -1, 2.3);
	
	Fit<float> fit;
	TraRotModel model;
	pfitDataSetf set;
	set.init(3, 3, n);
	
	input.resize(n);
	transformed.resize(n);
	
	for (int i=0; i<n; i++) {
		input[i] = ofVec3f(ofRandom(-5, 5),ofRandom(-5, 5),ofRandom(-5, 5));
		transformed[i] = model.evaluate(input[i], R, T);
	}
	
	set.setInput((float*)&input[0]);
	set.setOutput((float*)&transformed[0]);
	
	vector<float> parameters = fit.correlate(set, model);
	
	cout << "Results: ";
	for (int i=0; i<6; i++) {
		if (i!=0)
			cout << ", ";
		cout << parameters[i];
	}
	cout << endl;
}
