//
//  Fsdif.cpp
//  Orchids
//
//  Created by Antoine Bouchereau on 18/12/13.
//  Copyright (c) 2013 Antoine Bouchereau. All rights reserved.
//
#include "sdif.h"

// Open file and read header
SdifFileT *open_file (string infile)
{
    SdifFileT *file;
    
    SdifGenInit(NULL);
    if (!(file = SdifFOpen (infile.c_str(), eReadFile)))
    {
        fprintf (SdifStdErr, "Can't open input file '%s'.\n", infile.c_str());
        SdifGenKill();
        exit(1);
    }
    
    // Read header
    if (SdifFReadGeneralHeader(file) == 0  ||
        SdifFReadAllASCIIChunks(file) == 0)
    {
        fprintf (SdifStdErr, "Can't read header of input file '%s'.\n", infile.c_str());
        SdifFClose(file);
        SdifGenKill();
        exit(1);
    }
    
    return file;
}

//If frame "1DSC" then read matrices
int MySdifQueryFrameType (SdifFileT *in, void *userdata)
{
    return SdifFCurrFrameSignature(in) == SdifStringToSignature("1DSC");
}


//Query the matrice for retrieving datas and times
int MySdifQueryMatrixData (SdifFileT *in, int m, void *userdata)
{
    vector< feature<float> >    *features   = (vector< feature<float> > *) userdata;
    SdifMatrixHeaderT           *mtxh       = in->CurrMtrxH;
    SdifMatrixDataT             *mData      = SdifFCurrMatrixData(in);
    SdifSignature               mSig        = mtxh->Signature;
    SdifFloat8                  *data       = mData->Data.Float8;
    TArray2<float>              toMerge(mtxh->NbRow, mtxh->NbCol);
    
    //Check the feature index in the feature list corresponding to the current matrice
    int pos         = -1;
    const char *sig = SdifSignatureToString(mSig);
    for (unsigned int i = 0; i < features->size(); i++)
        if (strcmp(features->at(i).sig.c_str(), sig) == 0)
            pos = i;
    
    if (pos >= 0)
    {
        //Retrieve data
        for (unsigned int i = 0; i<mtxh->NbRow; i++)
            for (unsigned int j = 0; j<mtxh->NbCol; j++, data++)
                toMerge(i, j) = *data;
        //Merge the retrieve data
        features->at(pos).values.merge2(toMerge);
        
        //Retrieve time
        features->at(pos).times.push_back(SdifFCurrTime(in));
    }
    
    return 1;
}

int MySdifQueryMatrixDataPM2Optimized (SdifFileT *in, int m, void *userdata)
{
    frame_reader                *reader     = (frame_reader *) userdata;
    SdifMatrixHeaderT           *mtxh       = in->CurrMtrxH;
    SdifMatrixDataT             *mData      = SdifFCurrMatrixData(in);
    SdifFloat4                  *data       = mData->Data.Float4;
    
    TArray2<float> values(mtxh->NbRow, mtxh->NbCol);
    
    for (unsigned int i=0; i<mtxh->NbRow; i++)
        for (unsigned int j=0; j<mtxh->NbCol; j++, data++)
            values(i, j) = *data;
    
    reader->frames.push_back(values);
    return 1;
}

int MySdifCountFrames (SdifFileT *in, void *userdata)
{
    int* count = (int *) userdata;
    *count += 1;
    return 0;
}


int MySdifGetMaxLength (SdifFileT *in, int m, void *userdata)
{
    int                         *maxLength  = (int *) userdata;
    SdifMatrixHeaderT           *mtxh       = in->CurrMtrxH;
    SdifMatrixDataT             *mData      = SdifFCurrMatrixData(in);
    SdifFloat4                  *data       = mData->Data.Float4;
    
    for (unsigned int i = 0; i < mtxh->NbRow; i++)
        for (unsigned int j = 0; j < mtxh->NbCol; j++, data++)
            if (j == 0)
                *maxLength = _max(*data, *maxLength);
    
    return 1;
}

size_t mySdifReadFile (const char             *filename,
                     SdifOpenFileCallbackT   openfilefunc,
                     SdifFrameCallbackT      framefunc,
                     SdifMatrixCallbackT     matrixfunc,
                     SdifMatrixDataCallbackT matrixdatafunc,
                     SdifCloseFileCallbackT  closefilefunc,
                     void		    *userdata)
{
    SdifFileT *file = NULL;
    int	       eof  = 0, go_on = 1, count = 0;
    size_t     bytesread = 0, newread, currPos = 0;
    SdifUInt4  m, wantit;
    frame_reader *reader = (frame_reader *) userdata;
    
    /* open input file (parses selection from filename into file->Selection) */
    file = SdifFOpen (filename, eReadFile);
    if (!file)
        return 0;
    
    bytesread  = SdifFReadGeneralHeader(file);
    if (!bytesread  ||  SdifFLastError(file))
        return 0;	/* something's wrong, maybe no SDIF file */
    
    bytesread += SdifFReadAllASCIIChunks(file);
    if (SdifFLastError(file))
    {   /* error has already been printed by the library, just clean
         up and exit */
        return 0;
    }
    
    /* call begin file handler, return false stops reading */
    if (openfilefunc)
        go_on = openfilefunc(file, userdata);
    
    /* main read loop:
     Read next selected frame header.  Current signature has
     already been read by SdifFReadAllASCIIChunks or the last loop. */
    while (go_on  &&  !eof  &&
           (newread = SdifFReadNextSelectedFrameHeader(file)) > 0)
    {
        currPos = bytesread; //Keep position before reading the frame data
        bytesread += newread;
        //cout << "currpos: " << currPos << endl;
        // We are after the last frame we needed, kill process
        if (count > reader->last_frame)
        {
            SdifFClose(file);
            return bytesread;
        }
        
        // We found the first frame we're interested in, keep current postion
        if (count == reader->first_frame)
        {
            reader->previous_pos = currPos;
            reader->previous_index = count;
        }
        
        // We are reading in the interval frame we're interested in
        if (count >= reader->first_frame && count <= reader->last_frame)
            wantit = 1;
        else
        {
            if (currPos > reader->previous_pos)
                // Current position is after our last position, keep skipping frame data until we find our first frame
                wantit = 0;
            else if (currPos < reader->previous_pos)
            {
                // Current position is before our last position, move the cursor to the last position
                SdiffPosT pos = reader->previous_pos;
                SdifFSetPos(file, &pos);
                //cout << "previouspos: " << reader->previous_pos << endl;
                count += reader->previous_index;
                bytesread = pos;
                newread = SdifFReadNextSelectedFrameHeader(file);
                bytesread += newread;
                wantit = 0;
            }
        }
                
        /* call frame header handler that decides if we are interested */
        //wantit = framefunc  ?  framefunc(file, userdata)  :  1;

        if (wantit)
        {
            /* for matrices loop */
            for (m = 0; go_on  &&  m < SdifFCurrNbMatrix(file); m++)
            {
                /* Read matrix header */
                newread = SdifFReadMatrixHeader(file);
                
                if (newread == 0)
                {   /* read problem (also with 0 since we want a full header)  */
                    go_on = 0;
                }
                else
                {
                    bytesread += newread;
                    
                    /* Check if matrix type is in selection */
                    if (SdifFCurrMatrixIsSelected(file))
                    {   /* call matrix header handler */
                        wantit = matrixfunc  ?  matrixfunc(file, m, userdata)  :  1;
                    }
                    else
                        wantit = 0;

                    if (wantit)
                    {   /* read matrix data */
                        newread = SdifFReadMatrixData(file);
                        
                        if (newread == 0  &&  (SdifFCurrNbRow(file) != 0  &&
                                               SdifFCurrNbCol(file) != 0))
                        {   /* read problem (0 is ok, can be (0, n) matrix) */
                            go_on = 0;
                        }
                        else
                        {   /* read ok */
                            bytesread += newread;
                            
                            /* call matrix data handler */
                            if (matrixdatafunc)
                                go_on = matrixdatafunc(file, m, userdata);
                        }
                    }
                    else
                    {   /* a matrix type we're not interested in, so we skip it */
                        bytesread += SdifFSkipMatrixData(file);
                    }
                }
            }   /* end for matrices */
        }
        else
        {   /* we didn't want this frame */
            bytesread += SdifFSkipFrameData(file);
        }
        
        // Increment the number of read frame
        count++;
        
        eof = SdifFGetSignature(file, &bytesread) == eEof;
    }   /* end while frames */ 
    
    if (closefilefunc)
        closefilefunc(file, userdata);
    
    /* cleanup */
    SdifFClose(file);
    
    return bytesread;
}
