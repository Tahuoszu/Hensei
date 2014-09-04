/**
 *
 *  @file			ircamDescriptor.h
 *  @brief			Launch the IRCAM descriptor analysis
 *  @version        0.04
 *  @author			Antoine Bouchereau
 *	@date			16-12-2013
 *
 */

#ifndef __Orchids__ircamdescriptor__
#define __Orchids__ircamdescriptor__

#include "sdif.h"
#include "Orchids.h"

#define nbParameters 26
#define nbStandard 4
#define nbEnergy 11

/**
 *  @brief Write the ircam descriptor config file
 *
 *  Retrieve the default parameters for the ircam descriptor analysis.
 *  Write them in 'ircamDescriptor.cfg'
 *
 *  @param writeConfig Choose to write or not the config file
 *  @param params Parameters structure for IRCAM Descriptor analysis
 */
void                       ircamConfiguration(
                                              int writeConfig,
                                              vector<ircamDescriptor_param> params);

/**
 *  @brief Launch the IRCAM descriptor analysis
 *
 *  Send the analysis file (.wav) to IRCAMDescriptor.
 *  Read and parse the SDIF file to retrieve the descriptors we want.
 *  Fill the vector of feature structure.
 *
 *  @param filesRoot Directory where the analysis sound is stored
 *  @param params Parameters structure for IRCAM Descriptor analysis
 */
vector< feature<float> >   ircamDescriptors(
                                            const char                      *filesRoot,
                                            vector<ircamDescriptor_param>   params);


#endif /* defined(__Orchids__ircamdescriptor__) */
