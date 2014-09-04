/**
 *
 *  @file    main.cpp
 *  @brief   Segmentation
 *  @version 1
 *  @author  Henri NG
 *	@date    25-05-2014
 *
 */

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "segmentation.h"

int main (int argc, char **argv) {

    const clock_t begin_time = clock();

	/********************************* Usage **********************************/

	if (argc < 3) {
		std::cout << "Usage :" << std::endl;
        std::cout << "./Segmentation [input] [nb_seg] [output : optional] ";
        std::cout << "[version : optional]" << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "input   : Time Series File" << std::endl;;
        std::cout << "nb_seg  : Number of segments" << std::endl;
		std::cout << "output  : Output directory" << std::endl;
        std::cout << "version : 1.Linear / 2.Regression" << std::endl;
        std::cout << "          (by default, version 2 set)" << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "Example : ";
		std::cout << "./Segmentation datafile 16 folder/ 2";
		std::cout << std::endl;
		return 1;
	}

	/*************************** Global Variables *****************************/

    int iofile = 0;
    char *input = argv[1];

    // Get number of segments
    string str = argv[2];
    int nb_seg = atoi(str.c_str());

    // Get input pathname and filename
    string pathname = dirname(input);
    pathname += "/";
    string filename = basename(input);

    // Check output directory
    string output = pathname;
    struct stat st = {0};
    if (argc > 3) {
        output = argv[3];
        if (output.find_last_of("/\\") == string::npos)
            output += "/";
        if (stat(output.c_str(), &st) == -1) {
            std::cerr << "Output directory doesn't exist !" << std::endl;
            mkdir(output.c_str(), 0700);
            std::cout << "Output directory created..." << std::endl;
        }
    }

    // Get version
    int v = 2;
    if (argc > 4) {
        str = argv[4];
        v = atoi(str.c_str());
    }

	/********************************* Main ***********************************/

    std::cout << "Starting segmentation..." << std::endl;

    // Read data from file
    vector<float> data;
    iofile = readFromFile<float>(pathname, filename, data);
    if (iofile)
        return EXIT_FAILURE;
    std::cout << "File read..." << std::endl;

    // Compute multi-resolution segmentation
    vector<int> durations;
    vector<int> tmpOn;
	vector<vector<float> > matrix;
    std::cout << "Computing segmentation..." << std::endl;
    if (v == 1)
        matrix = multiSimpleSegment(data, nb_seg, &tmpOn, &durations);
    else
        matrix = tsMultiLevelSegment(data, nb_seg, &tmpOn, &durations);

    // Prepare segmented time series to write
    vector<float> results;
    parseSegments(matrix, tmpOn, durations, results);

    // Write data to file
    std::cout << "Writing data..." << std::endl;
    filename += ".int";
    iofile = writeToFile(output, filename, results);
    if (iofile)
        return EXIT_FAILURE;
    
    // int i = 0;
    // vector<vector<float> >::iterator it;
    // for (it = matrix.begin(); it != matrix.end(); ++it) {
    //     std::cout << "Segment L" << i + 1 << " : " << it->size() << "\t";
    //     std::cout << "Duration : " << durations[i] << "\t";
    //     std::cout << "tmpOn : " << tmpOn[i] << std::endl;
    //     print_vector(*it);
    //     std::cout << std::endl;
    //     i++;
    // }

    std::cout << "Segmentation done..." << std::endl;

	std::cout << "Process time : ";
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

    return EXIT_SUCCESS;

}
