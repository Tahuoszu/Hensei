/**
 *
 *  @file    main.cpp
 *  @brief   All my intership works are in this f*ck*ng file !
 *           And ça rocks du saucisson !
 *  @version 1
 *  @author  Henri NG
 *  @date    24-06-2014
 *
 */

/*********************************** Notice ************************************
* Ce fichier "Main" va chercher tous les fichiers audio d'un dossier, extraire *
* les descripteurs audio via "Orchids", réduire la dimension des séries par    *
* "Segmentation" et enfin extraire les séquences similaires des séries         *
* temporelles par l'algorithme de "tskm".                                      *
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "config.h"
#include "misc.h"
#include "preproc.h"

int main(int argc, char **argv)
{
/*
    string p = argv[1];
    string f;

    // Retrieve each tones file name
    vector<string> tf = getToneFilesName(p);
    int nb = tf.size();

    // Create associated symbol files for each time series
    for (int i = 0; i < nb; i++) {
        f = p + tf[i];
        std::cout << f << std::endl;
        preprocess(f);
    }

    exit(1);

    set<string> desc_val;
    map<string, float> tskm_val;
    string config_file = argv[1];
    if (readConfigFile(config_file, desc_val, tskm_val)) {
        std::cerr << "Config file can not be read : " << config_file;
        std::cerr << std::endl;
    }
    for (set<string>::iterator it = desc_val.begin(); it != desc_val.end(); ++it)
        std::cout << *it << std::endl;
    for (map<string, float>::iterator it = tskm_val.begin(); it != tskm_val.end(); ++it)
        std::cout << it->first << " = " << it->second << std::endl;
    exit(1);
*/

    const clock_t begin_time = clock();

    /********************************* Usage **********************************/

    if (argc < 2) {
        std::cout << "Usage :" << std::endl;
        std::cout << "./Hensei [input] [output : optional]" << std::endl;
        std::cout << "****************" << std::endl;
        std::cout << "input  : Directory with audio files [wav | aif | mp3]";
        std::cout << std::endl;
        std::cout << "output : Directory with tskm files (Chords and Phrases)";
        std::cout << std::endl;
        std::cout << "****************" << std::endl;
        std::cout << "Example : ";
        std::cout << "./Hensei folder/ results/";
        std::cout << std::endl;
        return EXIT_FAILURE;
    }

    /*************************** Global Variables *****************************/

    std::cout << "Starting process..." << std::endl;

    // Check input directory
    char* input = argv[1];
    struct stat st = {0};
    if (stat(input, &st) == -1) {
        std::cerr << "Input directory doesn't exist !" << std::endl;
        std::cout << "Process aborted..." << std::endl;
        return EXIT_FAILURE;
    }

    // Check output directory
    string output;
    if (argc > 2) {
        output = argv[2];
        if (stat(output.c_str(), &st) == -1) {
            std::cerr << "Output directory doesn't exist !" << std::endl;
            mkdir(output.c_str(), 0700);
            std::cout << "Output directory created..." << std::endl;
        }
    }

    // Repertories name
    string dir  = dirname(input);
    string base = basename(input);
    string rep  = dir + "/" + base;

    // Files name
    string file;
    string space = " ";

    // Number of files in each directory
    int nb_files = 0;

    /***************************** Descriptors ********************************/

    std::cout << "\t" << "* Starting descriptor process..." << std::endl;

    // Retrieve each audio file name
    vector<string> audio_files = getAudioFilesName(rep);
    nb_files = audio_files.size();

    // Create descriptors folder
    string descpath = rep + "_" + "desc/";
    if (stat(descpath.c_str(), &st) == -1)
        mkdir(descpath.c_str(), 0700);

    // Retrieve audio descriptors from all audio files
    for (int i = 0; i < nb_files; i++) {
        file = rep + "/" + audio_files[i];
        std::cout << "file : " << file << std::endl;
        // Call Orchids executable
        string orchids = "./Analysis";
        orchids = orchids + space + file + space + descpath;
        if (system(orchids.c_str()) > 0) {
            std::cerr << "Error while executing ircamDescriptor with ";
            std::cerr << file << std::endl;
        }
    }

    std::cout << "\t" << "* Descriptor process done..." << std::endl;
    std::cout << std::endl;

    /***************************** Segmentation *******************************/

    std::cout << "\t" << "* Starting segmentation process..." << std::endl;

    // Retrieve each descriptor file name
    vector<string> desc_files = getFilesName(descpath);
    nb_files = desc_files.size();

    // Create tones folder
    string tonepath = rep + "_" + "tones/";
    if (stat(tonepath.c_str(), &st) == -1)
        mkdir(tonepath.c_str(), 0700);

    // Segment all descriptors files
    string nb_Seg = "128";
    for (int i = 0; i < nb_files; i++) {
        file = descpath + desc_files[i];
        std::cout << file << std::endl;
        // Call Segmentation executable
        string segment = "./Segmentation";
        segment = segment + space + file + space + nb_Seg + space + tonepath;
        if (system(segment.c_str()) > 0) {
            std::cerr << "Error while executing Segmentation with ";
            std::cerr << file << std::endl;
        }
    }

    std::cout << "\t" << "* Segmentation process done..." << std::endl;
    std::cout << std::endl;

    /********************************* TSKM ***********************************/

    std::cout << "\t" << "* Preparing TSKM process..." << std::endl;

    // Retrieve each tones file name
    vector<string> tones_files = getToneFilesName(tonepath);
    nb_files = tones_files.size();

    // Create associated symbol files for each time series
    for (int i = 0; i < nb_files; i++) {
        file = tonepath + tones_files[i];
        std::cout << file << std::endl;
        preprocess(file);
    }

    std::cout << "\t" << "* TSKM preprocessing done..." << std::endl;

    std::cout << "\t" << "* Starting TSKM process..." << std::endl;

    // Check output directory
    if (output.empty())
        output = rep + "_" + "results/";

    // Call TSKM executable
    string tskm = "./tskm" + space + tonepath + space + output;
    if (system(tskm.c_str()) > 0) {
        std::cerr << "Error while executing TSKM with ";
        std::cerr << tonepath << std::endl;
        std::cout << "Process aborted..." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "\t" << "* TSKM process done..." << std::endl;

    /********************************* End ************************************/

    std::cout << "Process time : ";
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

    // Yeah, that's so cool !!!!
    return EXIT_SUCCESS;

}
