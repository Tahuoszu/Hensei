/**
 *
 * @file	bottomUpSegmentation.cpp
 * @brief   Bottom-UP segmentation approach,
 *          based on a Non Linear Regression Approximation algorithm
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "polyfit.hpp"
#include "segmentation.h"

Segment bottomUpSegmentation(const vector<float>& data, int nb_seg)
{

    // Initialize variables
	int data_size = data.size();
	Segment seg(data_size);

    // Harmonize data
	vector<float> datah = harmonize(data);
	float stdev = standard_deviation(datah);
    for (int i = 0; i < data_size; i++)
        datah[i] /= stdev;
	vector<float> curReconstruct = datah;

	// Initialize the merge cost of the segments
	// in the "fine segmented representation"
	for (int i = 0; i < seg.nbSeg - 1; i++) {
		seg.best[i] = compute_best(datah, seg, i, 1);
		seg.mc[i]   = compute_mc(datah, seg, i, 1);
	}	

	// Keep merging the lowest cost segments until only 'nb_seg' remain.
	int vind;
	float vmin;
	float err_recons = 0;

	while ((err_recons < 0.006) || (seg.size() > nb_seg)) {

        // Find the location "vind", of the cheapest merge.
		min_vector(seg.mc, &vmin, &vind);

		// The typical case, neither of the two segments
		// to be merged are end segments
		if ((vind > 0) && (vind < seg.nbSeg - 2)) {
			//std::cout << "Case 1 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			compute_recons(curReconstruct, seg, vind);
			seg.best[vind]   = compute_best(datah, seg, vind, 2);
			seg.mc[vind]     = compute_mc(datah, seg, vind, 2);
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.removePoint(vind + 1);
			vind--;
			seg.best[vind]   = compute_best(datah, seg, vind, 1);
			seg.mc[vind]     = compute_mc(datah, seg, vind, 1);
		}

		// Special case: The leftmost segment must be merged.
		else if (vind == 0) {
			//std::cout << "Case 2 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			compute_recons(curReconstruct, seg, vind);
			seg.best[vind]   = compute_best(datah, seg, vind, 2);
			seg.mc[vind]     = compute_mc(datah, seg, vind, 2);
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.removePoint(vind + 1);
		}

		// Special case: The rightmost segment must be merged.
		else {
			//std::cout << "Case 3 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			compute_recons(curReconstruct, seg, vind);
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.mc[vind]     = FLT_MAX;
			seg.removePoint(vind + 1);
			vind--;
			seg.best[vind]   = compute_best(datah, seg, vind, 1);
			seg.mc[vind]     = compute_mc(datah, seg, vind, 1);
		}

	err_recons = compute_error(datah, curReconstruct);
	//std::cout << "err_recons = " << err_recons << std::endl;

	}

    vector<float> best;
	for (int i = 0; i < seg.nbSeg; i++) {
        seg.best[i] = compute_best(datah, seg, i, 0);
        best = seg.best[i];
        seg.lefty[i]  = best[0];
        seg.righty[i] = best[best.size() - 1];
        seg.mc[i] = compute_mc(datah, seg, i, 0);
	}

    seg.resize();

	return seg;

}

float compute_mc(const vector<float>& data,
                 const Segment& seg,
                 int ind, int delay)
{
    int left  = seg.leftx[ind];
	int right = seg.rightx[ind + delay];
	float tmp   = 0;
	float accum = 0;
	vector<float> best = seg.best[ind];
	//std::cout << "best = ";
    //print_vector(best);
	for (int k = left; k < right; k++) {
		//std::cout << data[k] << "\t" << best[k - left] << std::endl;
		tmp = data[k] - best[k - left];
		accum += (tmp * tmp);
	}
	return accum;
}

vector<float> compute_best(const vector<float>& data,
						   const Segment& seg,
						   int ind, int delay)
{
	float left  = seg.leftx[ind];
	float right = seg.rightx[ind + delay];
	float gap   = right - left + 1;
	float deg   = 1;
	vector<float> best(gap, 0);
	vector<float> x = step_vector(left, right, deg);
	vector<float> y(data.begin() + left, data.begin() + right + 1);
	vector<float> coef = mathalgo::polyfit(x, y, 1);
	//std::cout << "x = ";
	//print_vector(x);
	//std::cout << "y = ";
	//print_vector(y);
	std::reverse(coef.begin(), coef.end());
	//std::cout << "c = ";
	//print_vector(coef);
	for (int i = 0; i < gap; i++)
		best[i] = coef[0] * x[i] + coef[1];
	//std::cout << "b = ";
	//print_vector(best);
	return best;
}

void compute_recons(vector<float>& data, const Segment& seg, int ind)
{
	int left  = seg.leftx[ind];
	int right = seg.rightx[ind + 1];
	vector<float> best = seg.best[ind];
	for (int k = left; k <= right; k++)
		data[k] = best[k - left];
}

float compute_error(const vector<float>& data, const vector<float>& recd)
{
	int data_size = data.size();
	float err_recons = 0;
	float accum = 0;
	float tmp   = 0;
	for (int k = 0; k < data_size; k++) {
		//std::cout << data[k] << "\t" << recd[k] << std::endl;
		tmp = data[k] - recd[k];
		//std::cout <<  tmp << std::endl;
		accum += (tmp * tmp);
	}
	err_recons = sqrtf(accum) / data_size;
	return err_recons;
}
