/**
 *
 * @file	multiSimpleSegment.cpp
 * @brief   Multi-level of segmentation
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "functions.h"
#include "segmentation.h"

vector<vector<float> > multiSimpleSegment(vector<float> tmpSeries,
                                          int nb_seg,
                                          vector<int>* tmpOn,
                                          vector<int>* durations)
{
    // Global variables
    int ts_size   = tmpSeries.size();
    int tq_size   = 0;
    int left      = 0;
    int right     = 0;
    int vind      = 0;
    float entropy = 0;
    float vmax    = 0;

    // Perform piecewise linear approximation on the series
    Segment seg  = simpleSegment(tmpSeries, nb_seg);

    // Compute entropy for each base segment
    vector<float> seg_val;
    int seg_size = seg.size();
    for (int i = 0; i < seg_size; i++) {
        left  = seg.leftx[i];
        right = seg.rightx[i];
        seg_val.assign(tmpSeries.begin() + left, tmpSeries.begin() + right + 1);
        entropy = approx_entropy(seg_val, 1,
                                 0.2 * standard_deviation(tmpSeries));
        seg.entrp[i] = entropy;
    }

    vector<float> delta_entropy;
    Segment tmp_queue = seg;
    Segment hiera_seg = seg;
    Segment cur_seg(seg, 0);

    while (!((cur_seg.leftx[0]  == 0) &&
             (cur_seg.rightx[0] == (ts_size - 1)))) {

        tq_size = tmp_queue.size();
        delta_entropy.resize(tq_size - 1, 0);
        for (int i = 0; i < tq_size - 1; i++) {
            left  = tmp_queue.leftx[i];
            right = tmp_queue.rightx[i + 1];
            seg_val.assign(tmpSeries.begin() + left,
                           tmpSeries.begin() + right + 1);
            entropy = approx_entropy(seg_val, 1,
                                     0.2 * standard_deviation(tmpSeries));
            delta_entropy[i] = entropy - \
                               (tmp_queue.entrp[i] + tmp_queue.entrp[i + 1]);
        }

        max_vector(delta_entropy, &vmax, &vind);
        cur_seg.setSegment(tmp_queue, vind);
        left  = tmp_queue.leftx[vind];
        right = tmp_queue.rightx[vind + 1];
        seg_val.assign(tmpSeries.begin() + left,
                       tmpSeries.begin() + right + 1);
        cur_seg.entrp[0] = approx_entropy(seg_val, 2,
                                          0.2 * standard_deviation(tmpSeries));
        hiera_seg.push_front(cur_seg);

        Segment new_queue;
        if (vind > 0) {
            left  = 0;
            right = vind - 1;
            new_queue = tmp_queue.subSegment(left, right);

        }
        new_queue.push_back(cur_seg);
        if (vind < tq_size - 2) {
            left  = vind + 2;
            right = tq_size - 1;
            new_queue.push_back(tmp_queue.subSegment(left, right));
        }

        tmp_queue = new_queue;
        new_queue.clear();

    }

    //hiera_seg.printSegment();

    int hs_size = hiera_seg.size() - 1;
    vector<int> &tmpOn_ref = *tmpOn;
    vector<int> &durat_ref = *durations;
    vector<vector<float> > segmentSeries(hs_size);
    tmpOn_ref.resize(hs_size, 0);
    durat_ref.resize(hs_size, 0);
    for (int i = 1; i <= hs_size; i++) {
        Segment cur_seg(hiera_seg, i);
        left  = cur_seg.leftx[0];
        right = cur_seg.rightx[0];
        segmentSeries[i - 1].assign(tmpSeries.begin() + left,
                                    tmpSeries.begin() + right + 1);
        tmpOn_ref[i - 1] = left;
        durat_ref[i - 1] = right - left + 1;
    }

    return segmentSeries;

}

void parseSegments(const vector<vector<float> >& matrix,
                   const vector<int>& tmpOn,
                   const vector<int>& durations,
                   vector<float>& results)
{
    int length = tmpOn.size();
    int index  = length - 1;
    while ((tmpOn[index] != 0) && (index != 0))
        index--;
    for (int i = index; i < length; i++) {
        // Symbol
        results.push_back(matrix[i][0]);
        // Start
        results.push_back(tmpOn[i]);
        // End
        results.push_back(tmpOn[i] + durations[i]);
    }
}
