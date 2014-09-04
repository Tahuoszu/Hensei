/**
 *
 * @file	simpleSegment.cpp
 * @brief   Bottom-UP segmentation approach,
 *          based on Keoghs's Piecewise Linear Approximation algorithm
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "segmentation.h"

Segment simpleSegment(const vector<float>& data, int nb_seg)
{

    // Initialize variables
	int data_size = data.size();
	Segment seg(data_size);

    // Harmonize data
	vector<float> datah = harmonize(data);
	float stdev = standard_deviation(datah);
    for (int i = 0; i < data_size; i++)
        datah[i] /= stdev;

	// Initialize the merge cost of the segments
	// in the "fine segmented representation"
	for (int i = 0; i < seg.nbSeg - 1; i++)
		seg.mc[i] = calculate_mc(datah, seg, i, 1);

	// Keep merging the lowest cost segments until only 'nb_seg' remain.
	int vind;
	float vmin;
	float err_recons = 0;

	while (err_recons < 0.05) {

        // Find the location "vind", of the cheapest merge.
		min_vector(seg.mc, &vmin, &vind);

		// The typical case, neither of the two segments
		// to be merged are end segments
		if ((vind > 0) && (vind < seg.nbSeg - 2)) {
			//std::cout << "Case 1 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			seg.mc[vind]     = calculate_mc(datah, seg, vind, 2);
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.removePoint(vind + 1);
			vind--;
			seg.mc[vind] = calculate_mc(datah, seg, vind, 1);
			//seg.printSegment();
		}

		// Special case: The leftmost segment must be merged.
		else if (vind == 0) {
			//std::cout << "Case 2 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			seg.mc[vind]     = calculate_mc(datah, seg, vind, 2);
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.removePoint(vind + 1);
			//seg.printSegment();
		}

		// Special case: The rightmost segment must be merged.
		else {
			//std::cout << "Case 3 : " << vind << std::endl;
			//std::cout << "nb_seg : " << seg.nbSeg << std::endl;
			seg.rightx[vind] = seg.rightx[vind + 1];
			seg.mc[vind]     = FLT_MAX;
			seg.removePoint(vind + 1);
			vind--;
			seg.mc[vind] = calculate_mc(datah, seg, vind, 1);
			//seg.printSegment();
		}

	err_recons = reconstruct_error(seg, datah);
	//std::cout << "err_recons = " << err_recons << std::endl;

	}

    vector<float> best;
	for (int i = 0; i < seg.nbSeg; i++) {
        best = calculate_best(datah, seg, i, 0);
        seg.lefty[i]  = best[0];
        seg.righty[i] = best[best.size() - 1];
        seg.mc[i] = calculate_mc(datah, seg, i, 0);
	}

    seg.resize();

	return seg;

}

float calculate_mc(const vector<float>& data,
                   const Segment& seg,
                   int ind, int delay)
{
    int left  = seg.leftx[ind];
	int right = seg.rightx[ind + delay];
	float tmp   = 0;
	float accum = 0;
	float step  = 0;
	vector<float> bestx;
	step = (data[right] - data[left]) / float(right - left);
	if (step != 0 && data[right] != data[left]) 
        bestx = step_vector(data[left], data[right], step);
    else {
    	int nb_point = right - left + 1;
    	for (int i = 0; i < nb_point; i++)
    		bestx.push_back(data[left]);
    }
	for (int k = left; k < right; k++) {
		tmp = data[k] - bestx[k - left];
		accum += (tmp * tmp);
	}
	return accum;
}

vector<float> calculate_best(const vector<float>& data,
                             const Segment& seg,
                             int ind, int delay)
{
    int left  = seg.leftx[ind];
	int right = seg.rightx[ind + delay];
	float step  = 0;
	vector<float> bestx;
	step  = (data[right] - data[left]) / (right - left);
	bestx = step_vector(data[left], data[right], step);
	return bestx;
}

float reconstruct_error(const Segment& seg, const vector<float>& data)
{
    vector<int> leftx  = seg.leftx;
    vector<int> rightx = seg.rightx;
    int uprate    = 2;
    int downrate  = 2;
	int data_size = data.size();
	float tmp     = 0;
    float sum     = 0;
	float error   = 0;
	vector<float> tmp_segm;
	vector<float> cur_segm(2, 0);
	vector<float> segm_reconst(data_size, 0);
	for (int i = 0 ; i < seg.nbSeg; i++) {
        uprate      = rightx[i] - leftx[i] + 1;
        cur_segm[0] = data[leftx[i]];
        cur_segm[1] = data[rightx[i]];
        //print_vector(cur_segm);
        //std::cout << "uprate   = " << uprate << std::endl;
        //std::cout << "downrate = " << downrate << std::endl;
        tmp_segm = resample(cur_segm, uprate, downrate);
        //std::cout << "tmp_segm" << std::endl;
        //print_vector(tmp_segm);
        for (int j = leftx[i]; j <= rightx[i]; j++)
            segm_reconst[j] = tmp_segm[j - leftx[i]];
	}
	//std::cout << "segm_reconst" << std::endl;
	//print_vector(segm_reconst);
	for (int k = 0; k < data_size; k++) {
	    tmp = data[k] - segm_reconst[k];
        sum += tmp * tmp;
	}
    error = sqrtf(sum) / data_size;
    return error;
}
