/**
 *
 * @file	approx_entropy.cpp
 * @brief	Approximate the entropy of time series,
 *          based on Kijoon Lee's matlab implementation
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "functions.h"
#include "segmentation.h"

float approx_entropy(const vector<float>& data,int dim, float r)
{

    float entropy;
	int data_size;
	int	m;
	int l;
	int truebool;
	float result[2];
	vector<bool> boolvect;
	vector<float> phi;
	vector<vector<float> > matrix;
	vector<vector<float> > tmpmat;

    // Data length
    data_size = data.size();

	for	(int i = 0; i < 2; i++) {

		// Initializing variables
		m = dim + i;
		l = data_size - m + 1;
		boolvect.resize(l, false);
		phi.resize(l);
		matrix.resize(m, vector<float>(l, 0));
		tmpmat.resize(m, vector<float>(l, 0));

		// Setting up data matrix
		for	(int j = 0; j < m; j++)
			for (int k = 0; k < l; k++)
			    matrix[j][k] = data[j + k];

		// Counting similar patterns using distance calculation
		for (int k = 0; k < l; k++) {
			// Calculating tmpmat
			for (int p = 0; p < m; p++) {
				for (int q = 0; q < l; q++) {
					tmpmat[p][q] = std::abs(matrix[p][q] - matrix[p][k]);
					if ((!boolvect[q]) && (tmpmat[p][q] > r))
					    boolvect[q] = true;
				}
			}
            boolvect.flip();
            truebool = std::count(boolvect.begin(), boolvect.end(), true);
			phi[k] = (float)truebool / l;
			boolvect.assign(l, false);
		}

		// Summing over the counts
        result[i] = (float)sum_vector(phi) / l;

        boolvect.clear();
        phi.clear();
        matrix.clear();
        tmpmat.clear();

	}

	entropy = log(result[0] / result[1]);

	return entropy;

}
