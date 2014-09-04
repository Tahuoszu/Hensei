/**
 *
 * @file	functions.hpp
 * @brief	Various fonctions for the segmentation of time series
 * @author  Henri NG
 * @version 1.0
 * @date	20/05/2014
 *
 */

#include "functions.h"

/*************************** Elementary functions *****************************/

template <class T>
vector<T> harmonize(const vector<T>& v)
{
    int data_size = v.size();
    vector<T> data(data_size);
    T mean = sum_vector(v) / data_size;
    for (int i = 0; i < data_size; i++)
        data[i] = v[i] - mean;
    return data;
}

template <class T>
void max_vector(const vector<T>& vect, T* vmax, int* vind)
{
	int v_size = vect.size();
	int ind    = 0;
	T tmp      = vect[0];
	for (int i = 1; i < v_size; i++) {
		if (vect[i] > tmp) {
			tmp = vect[i];
			ind = i;
		}
	}
	*vmax = tmp;
	*vind = ind;
}

template <class T>
void min_vector(const vector<T>& vect, T* vmin, int* vind)
{
	int v_size = vect.size();
	int ind    = 0;
	T tmp      = vect[0];
	for (int i = 1; i < v_size; i++) {
		if (vect[i] < tmp) {
			tmp = vect[i];
			ind = i;
		}
	}
	*vmin = tmp;
	*vind = ind;
}

template <class T>
vector<T> resample(vector<T>& input, int upRate, int downRate)
{
    // Special case (no resample)
    if (upRate == downRate)
        return input;

    // Parameters
    double src_ratio  = upRate / downRate;
    float *data_in    = (float *)calloc(BUFFER_LEN, sizeof(float));
    float *data_out   = (float *)calloc(BUFFER_LEN, sizeof(float));
    int input_frames  = input.size() + 1;
    int output_frames = BUFFER_LEN;

    // Ratio out of range
    src_ratio = (src_ratio > 256) ? 256 : src_ratio;

    // Initialize SRC_DATA struct
    SRC_DATA src_data;
    memset (&src_data, 0, sizeof(src_data)) ;
    src_data.data_in       = data_in; 
    src_data.input_frames  = input_frames;
    src_data.data_out      = data_out;
    src_data.output_frames = output_frames;
    src_data.src_ratio     = src_ratio;

    // Convert input data
    std::copy(input.begin(), input.end(), data_in);

    // Resample (from Secret Rabbit Code aka libsamplerate)
    // src_data = resample data
    // 1 = SRC_SINC_MEDIUM_QUALITY
    // 1 = channel
    int err = src_simple (&src_data, 0, 1);

    // Check errors
    if (err != 0) {
        std::cerr << "Line " << __LINE__ << " : " <<  src_strerror(err);
        std::cerr << std::endl;
        exit(1);
    }

    int terminate = (int)ceil((src_ratio >= 1.0) ? src_ratio : 1.0 / src_ratio);
    float outsize = fabs(src_data.output_frames_gen - src_ratio * input_frames);
    if (outsize > 2 * terminate) {
        std::cerr << "Line " << __LINE__ << " : bad output data length ";
        std::cerr << src_data.output_frames_gen << " should be ";
        std::cerr << (int)floor(src_ratio * input_frames) << "." << std::endl;
        std::cerr << "src_ratio  : " << src_ratio << std::endl;
        std::cerr << "input_len  : " << input_frames << std::endl;
        std::cerr << "output_len : " << output_frames << std::endl;
        exit(1);
    };

    // Convert output data
    vector<float> output(data_out, data_out + upRate);

    return output;
}

template <class T>
float standard_deviation(const vector<T>& v)
{
    int v_size   = v.size();
    vector<T> vh = harmonize(v);
    float var    = sum_sqr(vh) / (v_size - 1);
    return sqrtf(var);
}

template <class T>
vector<T> step_vector(T start, T end, T step)
{
    vector<T> v;
    T tmp;
    if (step == 0 || start == end) {
        v.push_back(start);
        v.push_back(end);
    }
    else if ((start < end) && (step > 0)) {
        tmp = start;
        while (tmp <= end) {
            v.push_back(tmp);
            tmp += step;
        }
    }
    else if ((start > end) && (step < 0)) {
        tmp = start;
        while (tmp >= end) {
            v.push_back(tmp);
            tmp += step;
        }
    }
    else {
        std::cerr << "In step_vector function : bad input values ! ";
        std::cout << std::endl;
        std::cerr << "start = " << start << std::endl;
        std::cerr << "end   = " << end << std::endl;
        std::cerr << "step  = " << step << std::endl;
        std::cerr << std::endl;
    }
    return v;
}

template <class T>
T sum_sqr(const vector<T>& v)
{
    T sum = 0;
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it)
        sum += (*it * *it);
    return sum;
}

template <class T>
T sum_vector(const vector<T>& v)
{
    T sum = 0;
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it)
        sum = sum + *it;
    return sum;
//    return std::accumulate(v.begin(), v.end(), 0);
}

/***************************** Display functions ******************************/

template <class T>
void print_vector(const vector<T>& v)
{
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it)
        std::cout << *it << "\t";
    std::cout << std::endl;
    return;
}

template <class T>
void print_matrix(const vector<vector<T> >& m)
{
    vector<T> v;
    typename vector<vector <T> >::const_iterator it;
    for	(it = m.begin(); it != m.end(); ++it)
        print_vector(*it);
    return;
}

/*************************** Input/Output functions ***************************/

template <class T>
int writeToFile(string pathname, string filename, const vector<T>& data)
{
    string path = pathname + filename;
    std::ofstream file(path.c_str());
    if (!file.is_open()) {
        std::cout << "Unable to open file : " << filename << std::endl;
        return 1;
    }
    int data_size = data.size();
    for (int i = 1; i <= data_size; i++) {
        file << data[i - 1];
        if ((i % 3) != 0)
            file << "\t";
        else
            file << std::endl;
    }
    file.close();
    return 0;
}

template <class T>
int readFromFile(string pathname, string filename, vector<T>& data)
{
    float value;
    string abs_path = pathname + filename;
    std::ifstream file(abs_path.c_str());
    if (!file.is_open()) {
        std::cout << "Unable to open file !" << std::endl;
        return 1;
    }
    while (file >> value)
        data.push_back(value);
    file.close();
    return 0;
}
