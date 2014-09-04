/**
 *
 *  @file    config.cpp
 *  @brief   Parser for the configuration file
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

#include "config.h"

bool checkValue(string str, const set<string>& sets)
{
	return sets.find(str) != sets.end();
}

bool commentLine(string str)
{
	return str[0] == ';';
}

set<string> descList()
{
	set<string> descriptors;
	descriptors.insert("FundamentalFrequency");
	descriptors.insert("Inharmonicity");
	descriptors.insert("Loudness");
	descriptors.insert("MFCC");
	descriptors.insert("Noisiness");
	descriptors.insert("SpectralCentroid");
	// Add more descriptors here
	return descriptors;
}

set<string> paramList()
{
	set<string> parameters;
	// Chord Mining Parameters
	parameters.insert("MarginalGapFilterAlpha");
	parameters.insert("MarginalGapMaxDuration");
	parameters.insert("MinimalToneDuration");
	parameters.insert("MinimalChordDuration");
	parameters.insert("MinimalSupport");
	parameters.insert("MarginAlpha");
	parameters.insert("MinimalChordSize");
	parameters.insert("MaximalChordSize");
	//Phrase Mining Parameters
	parameters.insert("SequenceWindowSize");
	parameters.insert("AlphaForClosedPhrases");
	parameters.insert("MinimalClosedPhraseSupport");
	parameters.insert("MinimalClosedSequenceSupport");
	return parameters;
}

int readValue(string line, string& param, float& value)
{
	if (line.empty())
		return 0;
	string tmp;
	std::size_t found = line.find("=");
	// Descriptor value
	if (found == std::string::npos) {
		param = line;
		value = 0;
		return 1;
	}
	// TSKM value
	else {
		param = line.substr(0, found - 1);
		removeSpace(param);
		tmp = line.substr(found + 1);
		removeSpace(tmp);
		if (tmp.empty() || !isdigit(tmp[0]))
			return 0;
		value = atof(tmp.c_str());
		return 2;
	}
}

int readConfigFile(string filename,
				   set<string>& desc_val,
				   map<string, float>& tskm_val)
{
	// Check Config File
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Can not open config file " << filename << std::endl;
		return 1;
	}

	// Generate list of audio descriptors and mining parameters
	set<string> descriptors = descList();
	set<string> parameters = paramList();
	
	// Read file
	float value;
	string param;
	string line;
	while (getline(file, line)) {
		// Skip comment or empty line
		if (commentLine(line) || line.empty())
			continue;
		// Read list of descriptors
		if (readValue(line, param, value) == 1) {
			if (checkValue(param, descriptors))
				desc_val.insert(param);
		}
		// Read list of TSKM parameters
		else if (readValue(line, param, value) == 2) {
			if (checkValue(param, parameters))
				tskm_val[param] = value;
		}
		else {
			std::cerr << "Config File contains bad entries !" << std::endl;
			std::cerr << line << std::endl;
		}
	}

	file.close();

	return 0;
}

void removeSpace(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}
