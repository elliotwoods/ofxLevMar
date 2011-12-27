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

#include "ofMain.h"

namespace ofxLevMar {
	///Extend this class with your own model
	template<typename T>
	class Model {
	public:
		Model(const int dimensionsIn, const int dimensionsOut, const int parameterCount);
		virtual void evaluate(pfitDataPoint<T>& p, const vector<T> &parameters) const = 0;
		
		const int parameterCount, dimensionsIn, dimensionsOut;
	};

	template<typename T>
	class FitData {
	public:
		FitData(const pfitDataSet<T>& set, const Model<T>& model) :
		set(set), model(model)
		{
		}

		const pfitDataSet<T>& set;
		const Model<T>& model;
	};

	template<typename T>
	class Fit {
	public:
		void correlate(const pfitDataSetd& set, const Model<double>& model, vector<double>& parameters, int iterations=1000);
		void correlate(const pfitDataSetf& set, const Model<float>& model, vector<float>& parameters, int iterations=1000);
		
		///Correlate and return parameters (initialised as 0's) 
		vector<T> correlate(const pfitDataSet<T> &set, const Model<T>& model, int iterations=1000);
	};

	template<typename T>
	void evaluate(T *p, T *hx, int m, int n, void *adata);
}