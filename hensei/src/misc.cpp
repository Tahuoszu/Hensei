/**
 *
 *  @file    misc.cpp
 *  @brief   Miscellaneous functions for input/output files
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#include "misc.h"

/************************ Getting files name functions ************************/

vector<string> getAudioFilesName(string dir)
{
    DIR *dp;
    struct dirent *dirp;

    string filename;
    string extension[5] = {"aif", "aiff", "mp3", "wav", "wave"};
    vector<string> files;

    if ((dp  = opendir(dir.c_str())) == NULL)
        std::cerr << "Unable to open " << dir << std::endl;

    while ((dirp = readdir(dp)) != NULL) {
    	if (dirp->d_type == DT_REG) {
    		filename = dirp->d_name;
    		for (int i = 0; i < 5; i++) {
                int len = filename.length() - extension[i].length();
    			if (filename.find(extension[i], len) != std::string::npos)
                    files.push_back(filename);
            }
		}
    }

    return files;
}

vector<string> getFilesName(string dir)
{
    DIR *dp;
    struct dirent *dirp;

    string filename;
    vector<string> files;

    if ((dp  = opendir(dir.c_str())) == NULL)
        std::cerr << "Unable to open " << dir << std::endl;

    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_type == DT_REG) {
            filename = dirp->d_name;
            files.push_back(filename);
        }
    }

    return files;
}

vector<string> getToneFilesName(string dir)
{
    DIR *dp;
    struct dirent *dirp;

    string filename;
    string ext = "int";
    vector<string> files;

    if ((dp  = opendir(dir.c_str())) == NULL)
        std::cerr << "Unable to open " << dir << std::endl;

    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_type == DT_REG) {
            filename = dirp->d_name;
            int len = filename.length() - ext.length();
            if (filename.find(ext, len) != std::string::npos)
                files.push_back(filename);
        }
    }

    return files;
}

/********************** Preparing tones files functions ***********************/

int preprocess(string filename)
{
    set<float> symbols;
    // Special Case for Fundamental Frequency descriptor
    if (filename.find("FundamentalFrequency") != std::string::npos) {
        if (rewrite(filename) != 0) {
            std::cerr << "Can not rewrite tones file of " << filename;
            std::cout << std::endl;
            return 1;
        }
        if (extractFrequencyFiles(filename, symbols) != 0) {
            std::cerr << "Can not create symbol file of " << filename;
            std::cout << std::endl;
            return 1;
        }
    }
    // General case for others descriptors
    else {
        if (extractSymbolFiles(filename, symbols) != 0) {
            std::cerr << "Can not create symbol file of " << filename << std::endl;
            return 1;
        }
    }
    if (rewriteTones(filename, symbols) != 0) {
        std::cerr << "Can not rewrite tones file of " << filename << std::endl;
        return 1;
    }
    return 0;
}

int extractSymbolFiles(string filename, set<float>& symbols)
{
    // Read content
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file : " << ifs << std::endl;
        return 1;
    }
    int start, end;
    float symbol;
    vector<float> data;
    char buf[8];
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
    string label = "LABEL";
    string descl;
    string number;
    int counter = 0;
    set<float>::iterator it;
    for (it = values.begin(); it != values.end(); ++it) {
        sprintf(buf, "%d", counter);
        number = buf;
        descl = label + number;
        ofs << counter << "\t" << *it << "\t" << descl << "\n";
        counter++;
    }
    ofs.close();

    return 0;
}

int rewriteTones(string filename, const set<float>& symbols)
{
    // Verify set of symbols
    if (symbols.empty())
        return 0;

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

    // Write data
    file  = fopen(filename.c_str(), "w");
    if (file == NULL) {
        std::cerr << "Unable to open file : " << filename << std::endl;
        fclose(file);
        return 1;
    }
    int symb;
    int freq_size = frequency.size();
    for (int i = 0; i < freq_size; i++) {
        symb = std::distance(symbols.begin(), symbols.find(frequency[i]));
        fprintf(file, "%d\t%d\t%d\n", symb, start[i], end[i]);
    }
    fclose(file);
    return 0;
}
