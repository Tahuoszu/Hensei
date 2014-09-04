/**
 *
 *  @file    preproc.cpp
 *  @brief   Preprocessing for descriptors labels
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

 #include "preproc.h"

/******************************* Main function ********************************/

int label(string desc, string pathname, string filename, string outpath)
{
    // Read file's content
    string input = pathname + "/" + filename;
    std::ifstream ifs(input.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file : " << input << std::endl;
        return 1;
    }
    float value;
    vector<float> data;
    while (ifs >> value)
        data.push_back(value);
    ifs.close();

    // Convert values by descriptors
    vector<string> data_label;
    if (desc == "FundamentalFrequency")
        data_label = convert_notes(data);
    else if (desc == "Inharmonicity")
        data_label = convert_harmo(data);
    else if (desc == "Loudness")
        data_label = convert_loudn(data);
    else if (desc == "Noisiness")
        data_label = convert_noisi(data);
    else if (desc == "SpectralCentroid")
        data_label = convert_spcen(data);
    else {
        std::cerr << "Unable to find descriptor : " << desc << std::endl;
        return 1;
    }

    // Write vector's content
    string output = outpath + "/" + filename;
    std::ofstream ofs(output.c_str());
    if (!ofs.is_open()) {
        std::cerr << "Unable to open file : " << output << std::endl;
        return 1;
    }
    vector<string>::iterator it;
    for (it = data_label.begin(); it != data_label.end(); ++it)
        ofs << *it << "\n";
    ofs.close();

    return 0;
}

/*************************** Create bins functions ****************************/

ffreq FundamentalFrequency_bins() {
    string note[12] = {"C", "Db", "D", "Eb", "E", "F", \
                       "Gb", "G", "Ab", "A", "Bb", "B"};
    string octa[12] = {"x", "y", "1", "2", "3", "4", \
                       "5", "6", "7", "8", "9", "10"};
    ffreq n;
    n.nb = 128;
    for (int i = 0; i < 128; i++) {
        // Generate Frequency
        n.freq[i] = midi2freq(i);
        // Generate Note
        n.desc[i] = note[i % 12] + octa[i / 12];
    }
    return n;
}

harmo Inharmonicity_bins() {
    float min[6] = {0, 0.1, 0.25, 0.5, 0.75, 0.9};
    float max[6] = {0.1, 0.25, 0.5, 0.75, 0.9, 1};
    string desc[6] = {"pure", "purs", "purm", "inharm", "inhars", "inhar"};
    harmo h;
    h.nb   = 6;
    h.min  = min;
    h.max  = max;
    h.desc = desc;
    return h;
}

loudn Loudness_bins() {
    float min[9] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
    float max[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    string desc[9] = {"sil", "ppp", "pp", "p", "mp", "mf", "f", "ff", "fff"};
    loudn l;
    l.nb   = 9;
    l.min  = min;
    l.max  = max;
    l.desc = desc;
    return l;
}

noisi Noisiness_bins() {
    float min[6] = {0, 0.1, 0.25, 0.5, 0.75, 0.9};
    float max[6] = {0.1, 0.25, 0.5, 0.75, 0.9, 1};
    string desc[6] = {"harp", "hars", "harm", "noism", "noiss", "noisp"};
    noisi n;
    n.nb   = 6;
    n.min  = min;
    n.max  = max;
    n.desc = desc;
    return n;
}

spcen SpectralCentroid_bins() {
    float min[7] = {0, 0, 1.5, 1.6, 1.7, 1.8, 1.9};
    float max[7] = {0, 1.5, 1.6, 1.7, 1.8, 1.9, 2};
    string desc[7] = {"nil", "very_low", "low", "med_low", "med_high", "high", \
                      "very_high"};
    spcen s;
    s.nb   = 7;
    s.min  = min;
    s.max  = max;
    s.desc = desc;
    return s;
}

/**************************** Conversion functions ****************************/

vector<string> convert_notes(const vector<float>& data)
{
    int data_size = data.size();
    vector<string> data_label(data_size);
    ffreq n = FundamentalFrequency_bins();
    int j = 0;
    float f = 0;
    for (int i = 0; i < data_size; i++) {
        f = roundf2d(data[i]);
        if (f < 16.352) // C0 = Do1
            data_label[i] = n.desc[0];
        else {
            j = approxFreq(f, n);
            data_label[i] = n.desc[j];
        }
    }
    return data_label;
}

vector<string> convert_harmo(const vector<float>& data)
{
    int data_size = data.size();
    vector<string> data_label(data_size);
    harmo h = Inharmonicity_bins();
    float f = 0;
    for (int i = 0; i < data_size; i++) {
        f = roundf2d(data[i]);
        for (int j = 0; (j < h.nb) && !(h.min[j] <= f < h.max[j]); j++)
            data_label[i] = h.desc[j];
    }
    return data_label;
}

vector<string> convert_loudn(const vector<float>& data)
{
    int data_size = data.size();
    vector<string> data_label(data_size);
    loudn l = Loudness_bins();
    float f = 0;
    for (int i = 0; i < data_size; i++) {
        f = roundf2d(data[i]);
        if (f == 0.0)
            data_label[i] = l.desc[0];
        else
            for (int j = 0; (j < l.nb) && !(l.min[j] <= f < l.max[j]); j++)
                data_label[i] = l.desc[j];
    }
    return data_label;
}

vector<string> convert_noisi(const vector<float>& data)
{
    int data_size = data.size();
    vector<string> data_label(data_size);
    noisi n = Noisiness_bins();
    float f = 0;
    for (int i = 0; i < data_size; i++) {
        f = roundf2d(data[i]);
        for (int j = 0; (j < n.nb) && !(n.min[j] <= f < n.max[j]); j++)
            data_label[i] = n.desc[j];
    }
    return data_label;
}

vector<string> convert_spcen(const vector<float>& data)
{
    int data_size = data.size();
    vector<string> data_label(data_size);
    spcen s = SpectralCentroid_bins();
    float f = 0;
    for (int i = 0; i < data_size; i++) {
        f = roundf2d(data[i]);
        if (f == 0.0)
            data_label[i] = s.desc[0];
        else
            for (int j = 0; (j < s.nb) && !(s.min[j] <= f < s.max[j]); j++)
                data_label[i] = s.desc[j];
    }
    return data_label;
}

float roundf2d(float f)
{
    return roundf(f * 100) / 100;
}

int approxFreq(float f, const ffreq& n)
{
    int midi = freq2midi(f);
    vector<int> nearest;
    nearest.push_back(midi - 1);
    nearest.push_back(midi);
    nearest.push_back(midi + 1);
    int min = 0;
    for (int i = 0; i < 3; i++)
        if (fabs(n.freq[nearest[min]] - f) > fabs(n.freq[nearest[i]] - f))
            min = i;
    return nearest[min];
}
