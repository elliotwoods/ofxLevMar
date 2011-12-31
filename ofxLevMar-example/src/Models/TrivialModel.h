#pragma once
//
//  TrivialModel.h
//  ofxLevMar-example
//

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
	
	void evaluate(pfitDataPoint<double>& point, const double *parameters) const {
		
		double& x (*point.getInput());
		double& y (*point.getOutput());
		
		const double& A (parameters[0]);
		const double& B (parameters[1]);
		const double& C (parameters[2]);
		
		y = A * exp(B * x) + C;
	}
	
	double evaluate(double x, double A, double B, double C) const {
		return A * exp(B * x) + C;
	}
};
