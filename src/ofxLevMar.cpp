//
//  ofxLevMar.cpp
//
//  Created by Elliot Woods on 10/11/2011.
//  Copyright (c) 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxLevMar.h"

namespace ofxLevMar {
#pragma mark Model
	template<typename T>
	Model<T>::Model(const int dimensionsIn, const int dimensionsOut, const int parameterCount) : parameterCount(parameterCount), dimensionsIn(dimensionsIn), dimensionsOut(dimensionsOut) {
		
	}
	
#pragma mark Fit
	template<>
	void Fit<double>::correlate(const pfitDataSet<double>& set, const Model<double>& model, vector<double>& parameters, int iterations) {
		if (parameters.size() != model.parameterCount)
			throw ("Fit::correlate : parameters input vector size does not match model's parameter length");
		
		vector<double> outputZeros(set.size(), 0);

		FitData<double> fitData(set, model);
		dlevmar_dif(evaluate, &parameters[0], &outputZeros[0], parameters.size(),
			set.size(), iterations, NULL, NULL, NULL, NULL, (void*)&fitData);
	}

	template<>
	void Fit<float>::correlate(const pfitDataSet<float>& set, const Model<float>& model, vector<float>& parameters, int iterations) {
		if (parameters.size() != model.parameterCount)
			throw ("Fit::correlate : parameters input vector size does not match model's parameter length");

		vector<float> outputZeros(set.size(), 0);

		FitData<float> fitData(set, model);
		slevmar_dif(evaluate, &parameters[0], &outputZeros[0], parameters.size(),
			set.size(), iterations, NULL, NULL, NULL, NULL, (void*)&fitData);
	}
	
	template<typename T>
	vector<T> Fit<T>::correlate(const pfitDataSet<T>& set, const Model<T>& model, int iterations) {
		vector<T> parameters(model.parameterCount, 0);
		correlate(set, model, parameters, iterations);
		return parameters;
	}
	
#pragma mark evaluate
	template<typename T>
	void evaluate(T *p, T *y, int m, int n, void *adata) {
		FitData<T>& data(*(FitData<T>*)adata);
		const pfitDataSet<T>& set(data.set);
		const Model<T>& model(data.model);
		
		register int i;
		T x;
		for(i=0; i<n; ++i){
			x = set.getInput()[i];
			y[i]=p[0]*exp(-p[1]*x) + p[2] - set.getOutput()[i];
		}
		return;

		T rms, error;
		vector<T> parameters(&p[0], &p[m]);
		
		for (int i=0; i<n; i++) {
			pfitDataPoint<T> point = set[i].makeCopy();
			model.evaluate(point, parameters);

			rms = 0;
			for (int j=0; j<set.getOutputDimensions(); j++)
			{
				error = set[i].getOutput()[j] - point.getOutput()[j];
				rms += error * error;
			}

			y[n] = sqrt(rms);
			
			cout << "[";
			for (int i=0; i<m; i++)
				cout << p[i] << ", ";
			cout << "] ";
			cout << "rms = " << y[n] << endl;
		}
	}

#pragma mark template
	template class Model<float>;
	template class Model<double>;
	template class Fit<float>;
	template class Fit<double>;
}
