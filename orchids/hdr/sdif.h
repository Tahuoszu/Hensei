/**
 *
 *  @file			sdif.h
 *  @brief			Operations on SDIF files
 *  @version        0.05
 *  @author			Antoine Bouchereau
 *	@date			16-12-2013
 *
 */

#ifndef Orchids_Fsdif_h
#define Orchids_Fsdif_h

#include "Orchids.h"

/**
 *  @brief Open a SDIF file, read general header and ASCII chunks.
 *
 *  @param infile Path of the SDIF file to open
 */
SdifFileT*      open_file (string infile);

/**
 *  @brief Check that the current frame is a type '1DSC'
 *
 *  @param in Pointer to the SDIF file
 *  @param userdata User data structure
 */
int             MySdifQueryFrameType (
                                      SdifFileT *in,
                                      void      *userdata);

/**
 *  @brief Matrix data callback for IRCAM descriptor analysis
 *
 *  @param in Pointer to the SDIF file
 *  @param m Matrix number
 *  @param userdata User data structure
 */
int             MySdifQueryMatrixData (
                                       SdifFileT    *in,
                                       int          m,
                                       void         *userdata);

/**
 *  @brief Matrix data callback for PM2 analysis
 *
 *  @param in Pointer to the SDIF file
 *  @param m Matrix number
 *  @param userdata User data structure
 */
/*
int             MySdifQueryMatrixDataPM2 (
                                          SdifFileT *in,
                                          int       m,
                                          void      *userdata);
*/

/**
 *  @brief Matrix data callback for PM2 analysis
 *
 *  @param in Pointer to the SDIF file
 *  @param m Matrix number
 *  @param userdata User data structure
 */
int MySdifQueryMatrixDataPM2Optimized (
                                       SdifFileT    *in,
                                       int          m,
                                       void         *userdata);

/**
 *  @brief Retrieve maximum frame value
 *
 *  @param in Pointer to the SDIF file
 *  @param m Matrix number
 *  @param userdata User data structure
 */
int MySdifGetMaxLength (
                        SdifFileT   *in,
                        int         m,
                        void        *userdata);

/**
 *  @brief Count number of frames in a SDIF file
 *
 *  @param in Pointer to the SDIF file
 *  @param m Matrix number
 *  @param userdata User data structure
 */
int MySdifCountFrames (
                       SdifFileT    *in,
                       void         *userdata);

/**
 *  @brief Optimized version of the SdifReadFile function
 *
 *  This version uses the frame_reader structure to keep in memory the last access position in the SDIF file.
 *  This allowed to gain huge amount of time and to skip the SdifFSkipFrameData function.
 *
 *  @param filename Input file
 *  @param openfilefunc Open file callback
 *  @param framefunc Read frame callback
 *  @param matrixfunc Read matrix callback
 *  @param matrixdatafunc Read matrix data callback
 *  @param closefilefunc Close file callback
 *  @param userdata User data structure (struct frame_reader)
 */
size_t mySdifReadFile (const char              *filename,
                       SdifOpenFileCallbackT   openfilefunc,
                       SdifFrameCallbackT      framefunc,
                       SdifMatrixCallbackT     matrixfunc,
                       SdifMatrixDataCallbackT matrixdatafunc,
                       SdifCloseFileCallbackT  closefilefunc,
                       void                    *userdata);

#endif
