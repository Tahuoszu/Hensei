/**
 *
 *  @file    main.cpp
 *  @brief   Retrieve audio descriptors for further process of data mining,
 *			 from IrcamDescriptor (G. Peeters) and Orchids (A. Bouchereau)  
 *  @version 1
 *  @author  Henri NG
 *	@date    20-06-2014
 *
 */

#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "defaultAnalysisParams.h"
#include "ircamdescriptor.h"
#include "outils.h"
#include "Orchids.h"

int main(int argc, char **argv)
{

	const clock_t begin_time = clock();

	/********************************* Usage **********************************/

	if (argc < 1) {
		std::cout << "Usage :" << std::endl;
        std::cout << "./Analysis [input] [output : optional] ";
        std::cout << "[config : optional]";
        std::cout << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "input  : Audio Files [aif|wav|mp3]" << std::endl;
		std::cout << "output : Directory with descriptor files" << std::endl;
		std::cout << "config : IrcamDescriptor configuration file" << std::endl;
		std::cout << "****************" << std::endl;
		std::cout << "Example : ";
		std::cout << "./Analysis music.wav folder/ ircamDescriptors.config ";
		std::cout << std::endl;	
		return 1;
	}

	/********************************* Main ***********************************/

	char* input = argv[1];
	string dir  = dirname(input);
	string base = basename(input);
	string filename = base.substr(0, base.find_last_of("."));
	string pathname = dir + "/" + filename + "/";

	// Check descriptors folder
    string output;
    struct stat st = {0};
    if (argc > 2) {
        output   = argv[2];
        pathname = output;
        if (pathname.rfind("/") != pathname.size() - 1)
        	pathname = pathname + "/";
    }
	if (stat(pathname.c_str(), &st) == -1) {
        std::cerr << "Output directory doesn't exist !" << std::endl;
        mkdir(pathname.c_str(), 0700);
        std::cout << "Output directory created..." << std::endl;
    }

	// Start IrcamDescriptors process
	analysis_params params = defaultAnalysisParams();
	vector<feature<float> > descriptors = \
	ircamDescriptors(input, params.irc_desc_params);

	// Write to each file an audio descriptor of each sound.
	writeDescriptors<float>(pathname, filename, descriptors);

	std::cout << "Process time : ";
	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

	return 0;

}
