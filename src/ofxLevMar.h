#pragma once
//
//  ofxLevMar.h
//
//  Created by Elliot Woods on 10/11/2011.
//  Copyright (c) 2011 Kimchi and Chips. All rights reserved.
//

#include "levmar.h"

///We require ofxPolyFit here
#include "pfitDataSet.h"

namespace ofxLevMar {
	///Extend this class with your own model
	class Model {
	public:
		virtual void evaluate(pfitDataPointd& p, const vector<double> &parameters) const;
	};

	class FitData {
	public:
		FitData(const pfitDataSetd& set, const Model& model); 
		const pfitDataSetd& set;
		const Model& model;
	};

	class Fit {
	public:
		void correlate(const pfitDataSetd& set, const Model& model, vector<double> parameters, int iterations);
	};

	void evaluate(double *p, double *hx, int m, int n, void *adata);
}