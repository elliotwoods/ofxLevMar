#include "testApp.h"

/**
 You must create a class that extends Mode<float or double>
 You then pass an instance of this class to the Fit to find the fit parameters. Your model performs a transform between input and output, e.g:
 
 y = m*x + c
 
 This exponential model has:
		3 parameters A, B, C
		1 input x
		1 output y
 **/

class TrivialModel : public Model<double> {
public:
	TrivialModel() : Model<double>(1, 1, 3) { }

	void evaluate(pfitDataPoint<double>& point, const vector<double> &parameters) const {
		
		double& x (*point.getInput());
		double& y (*point.getOutput());
		
		const double& A (parameters[0]);
		const double& B (parameters[1]);
		const double& C (parameters[1]);
		
		y = A * exp(B * x) + C;
	}
	
	double evaluate(double x, double A, double B, double C) {
		return A * exp(B * x) + C;
	}
};

//--------------------------------------------------------------
void testApp::setup(){
	testTrivial();
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
