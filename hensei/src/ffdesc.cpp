/**
 *
 *  @file    ffdesc.h
 *  @brief   Functions for Frequency Fundamental Descriptor
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#include "ffdesc.h"

/********************** Preparing tones files functions ***********************/

int extractFrequencyFiles(string filename, set<float>& symbols)
{
    // Prepare conversion
    notes n = generateMFD();

    // Read content
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file : " << ifs << std::endl;
        return 1;
    }
    int start, end;
    float symbol;
    vector<float> data;
    while (ifs >> symbol >> start >> end)
        data.push_back(symbol);
    ifs.close();

    // Look for all symbols
    set<float> values(data.begin(), data.end());
    symbols = values;

    // Write symbols to file
    string output = filename + ".tskm";
    std::ofstream ofs(output.c_str());
    if (!ofs.is_open()) {
        std::cerr << "Unable to open file : " << ofs << std::endl;
        return 1;
    }
    int midi = 0;
    int counter = 0;
    set<float>::iterator it;
    for (it = values.begin(); it != values.end(); ++it) {
        // C0 = DO = 16.352
        midi = (*it > 16.352) ? freq2midi(*it) : 0;
        ofs << counter << "\t" << *it << "\t" << n.desc[midi] << "\n";
        counter++;
    }
    ofs.close();

    return 0;
}

int rewrite(string filename)
{
	// Prepare conversion
    notes n = generateMFD();

	// Read file
    FILE *file  = fopen(filename.c_str(), "r");
    if (file == NULL) {
        std::cerr << "Unable to open file : " << filename << std::endl;
        fclose(file);
        return 1;
    }
    vector<int> start;
    vector<int> end;
    vector<float> frequency;
    int s, e;
    float f;
    while (fscanf(file, "%f\t%d\t%d", &f, &s, &e) == 3) {
        start.push_back(s);
        end.push_back(e);
        frequency.push_back(f);
    }
    fclose(file);

    // Convert to nearest frequency
    int midi = 0;
    int freq_size = frequency.size();
    vector<float> nearFreq(freq_size, 0);
    for (int i = 0; i < freq_size; i++) {
        if (frequency[i] == 0)
            nearFreq[i] = frequency[i];
        else {
            midi = approxFreq(frequency[i], n);
    	    nearFreq[i] = n.freq[midi];
        }
    }

    // Write data
    file  = fopen(filename.c_str(), "w");
    if (file == NULL) {
        std::cerr << "Unable to open file : " << filename << std::endl;
        fclose(file);
        return 1;
    }
    for (int i = 0; i < freq_size; i++)
    	fprintf(file, "%f\t%d\t%d\n", nearFreq[i], start[i], end[i]);
    fclose(file);
	return 0;
}

/**************************** Conversion functions ****************************/

int approxFreq(float f, const notes& n)
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

int freq2midi(float f)
{
    return 69 + 12 * log2(f / 440);
}

notes generateMFD()
{
    string note[12] = {"C", "Db", "D", "Eb", "E", "F", \
                       "Gb", "G", "Ab", "A", "Bb", "B"};
    string octa[12] = {"x", "y", "1", "2", "3", "4", \
                       "5", "6", "7", "8", "9", "10"};
    notes n;
    for (int i = 0; i < 128; i++) {
        // Generate MIDI
        n.midi[i] = i;
        // Generate Frequency
        n.freq[i] = midi2freq(i);
        // Generate Note
        n.desc[i] = note[i % 12] + octa[i / 12];
    }
    return n;
}

float midi2freq(int m)
{
	return 440 * pow(2, (float)(m - 69) / 12);
}
