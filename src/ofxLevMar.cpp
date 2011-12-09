//
//  ofxLevMar.cpp
//
//  Created by Elliot Woods on 10/11/2011.
//  Copyright (c) 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxLevMar.h"

namespace ofxLevMar {

	FitData::FitData(const pfitDataSetd& set, const Model& model) :
	set(set), model(model)
	{
	}

	void Fit::correlate(const pfitDataSetd& set, const Model& model, vector<double> parameters, int iterations) {

		double* outputBlank = new double[set.size()];

		FitData fitData(set, model);
		dlevmar_dif(evaluate, &parameters[0], outputBlank, parameters.size(),
			set.size(), iterations, NULL, NULL, NULL, NULL, (void*)&set);

		delete[] outputBlank;
	}

	void evaluate(double *p, double *hx, int m, int n, void *adata) {
		FitData& data(*(FitData*)adata);
		const pfitDataSetd& set(data.set);
		const Model& model(data.model);
		pfitDataPointd point = *(pfitDataPointd*)0;

		vector<double> parameters(&p[0], &p[m]);

		double rms, error;

		for (int i=0; i<n; i++) {
			point = set[i].makeCopy();
			model.evaluate(set[i], parameters);

			rms = 0;
			for (int j=0; j<set.getOutputDimensions(); j++)
			{
				error = set[i].getOutput()[j] - point.getOutput()[j];
				rms += error * error;
			}

			hx[n] = error;
		}
	}
}
