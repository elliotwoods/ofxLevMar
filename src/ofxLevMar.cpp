//
//  ofxLevMar.cpp
//
//  Created by Elliot Woods on 10/11/2011.
//  Copyright (c) 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxLevMar.h"

namespace ofxLevMar {

	template<>
	void Fit<double>::correlate(const pfitDataSet<double>& set, const Model<double>& model, vector<double> parameters, int iterations) {

		double* outputBlank = new double[set.size()];

		FitData<double> fitData(set, model);
		dlevmar_dif(evaluate, &parameters[0], outputBlank, parameters.size(),
			set.size(), iterations, NULL, NULL, NULL, NULL, (void*)&set);

		delete[] outputBlank;
	}

	template<>
	void Fit<float>::correlate(const pfitDataSet<float>& set, const Model<float>& model, vector<float> parameters, int iterations) {

		float* outputBlank = new float[set.size()];

		FitData<float> fitData(set, model);
		slevmar_dif(evaluate, &parameters[0], outputBlank, parameters.size(),
			set.size(), iterations, NULL, NULL, NULL, NULL, (void*)&set);

		delete[] outputBlank;
	}

	template<typename T>
	void evaluate(T *p, T *hx, int m, int n, void *adata) {
		FitData<T>& data(*(FitData<T>*)adata);
		const pfitDataSet<T>& set(data.set);
		const Model<T>& model(data.model);
		pfitDataPoint<T> point = *(pfitDataPoint<T>*)0;

		vector<T> parameters(&p[0], &p[m]);

		T rms, error;

		for (int i=0; i<n; i++) {
			point = set[i].makeCopy();
			model.evaluate(point, parameters);

			rms = 0;
			for (int j=0; j<set.getOutputDimensions(); j++)
			{
				error = set[i].getOutput()[j] - point.getOutput()[j];
				rms += error * error;
			}

			hx[n] = error;
		}
	}

	template class Fit<float>;
	template class Fit<double>;
}
