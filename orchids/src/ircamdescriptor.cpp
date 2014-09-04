//
//  ircamdescriptor.cpp
//  Orchids
//
//  Created by Antoine Bouchereau on 18/12/13.
//  Copyright (c) 2013 Antoine Bouchereau. All rights reserved.
//

#include "ircamdescriptor.h"


void ircamConfiguration(
                        int writeConfig,
                        vector<ircamDescriptor_param> params)
{
    if (writeConfig == 1)
    {
        FILE *fid = fopen("ircamDescriptor.cfg", "w");
        fprintf(fid, "\n[Parameters]\n\n");
        
        for (int i=0; i<nbParameters; i++)
            if (params[i].name.compare("WindowType")==0)
                fprintf(fid, "%s = %s\n", params[i].name.c_str(), params[i].sVal.c_str());
            else
                fprintf(fid, "%s = %f\n", params[i].name.c_str(), params[i].fVal);
        
        fprintf(fid, "\n[StandardDescriptors]\n\n");
        for (int i=nbParameters; i<nbParameters+nbStandard; i++)
            fprintf(fid, "%s = %f\n", params[i].name.c_str(), params[i].fVal);
        fprintf(fid, "\n");
        
        FILE *fidDesc = fopen("configurationFull.desc", "r");
        char line[1024];
        
        while ( fgets(line, sizeof(line), fidDesc) )
            fputs(line, fid);

        fclose(fidDesc);
        
        fprintf(fid, "\n[EnergyDescriptors]\n\n");
        for (int i=nbParameters+nbStandard ; i<nbParameters+nbStandard+nbEnergy ; i++)
            fprintf(fid, "%s = %f\n", params[i].name.c_str(), params[i].fVal);
        
        fclose(fid);
    }
}


vector< feature<float> > ircamDescriptors(
                                          const char                        *filesRoot,
                                          vector<ircamDescriptor_param>     params)
{
    vector< feature<float> > features;
    
    string          iDescDir    = "./ircamdescriptor";
    DIR*            rep         = NULL;
    struct dirent*  fichierLu   = NULL;
    vector<string>  files;
    cout << "* Preparing configuration file" << endl;
    ircamConfiguration(0, params);
    rep = opendir(filesRoot);

    if (rep != NULL)
    {
        const char      *finalDir = filesRoot;
        string          fname;
        string          extension[4] = {"wav", "wave", "aiff", "aif"};
        closedir(rep);
        rep = opendir(finalDir);
        while ((fichierLu = readdir(rep)) != NULL)
            if (fichierLu->d_type == DT_REG) // if entry is a regular file
            {
                fname = fichierLu->d_name;      // filename
                //if filename's last characters are extension
                for (int i = 0; i < 4; i++)
                    if (fname.find(extension[i], (fname.length() - extension[i].length())) != std::string::npos)
                        files.push_back(fname); // add filename to results vector
            }
    }else
        files.push_back(filesRoot);
    
    for (unsigned int i = 0; i < files.size(); i++)
    {
        cout << "* Processing " << files[i] << endl;
        string iDescCmd = iDescDir + " " + files[i] + " ircamDescriptor.cfg";
        cout << iDescCmd << endl;
        
        if (system(iDescCmd.c_str()) > 0)
        {
            throw "Error while executing ircamDescriptor";
            return features;
        }
        
        string filePath = files[i] + ".descr.sdif";
        SdifFileT *file = open_file(filePath);
        cout << "* Reading SDIF descriptors headers: " << filePath << endl;
        
        //Retrieve descriptors names
        string         fsigstr  = "1DSC";
        SdifSignature  fsig     = SdifStringToSignature(fsigstr.c_str());
        SdifFrameTypeT *ftype   = SdifTestFrameType(file, fsig);
        int            fnumcomp = SdifFrameTypeGetNbComponents(ftype);
        SdifComponentT *fcomp;
        
        for (int j = 1; j <= fnumcomp - 26; j++)
        {
            fcomp = SdifFrameTypeGetNthComponent(ftype, j);
            feature<float> f(SdifFrameTypeGetComponentName(fcomp), SdifSignatureToString(fcomp->MtrxS));
            features.push_back(f);
        }
        
        SdifFClose(file);
        
        //Retrieve datas and times in features
        unsigned long nread;
        nread = SdifReadFile(filePath.c_str(), NULL, MySdifQueryFrameType, NULL, MySdifQueryMatrixData, NULL, &features);

        assert(nread > 0);
        
        //Cleanup
        SdifGenKill();
        
        //Modifying descriptors structure
        cout << "* Modifying descriptors structure" << endl;
        
        for (unsigned int j = 0; j < features.size(); j++)
        {
            switch (features[j].values.cols()) {
                case 9:
                    features[j].values.resizeMatrixByCol(7, 9);
                    break;
                    
                case 6:
                    features[j].values.resizeMatrixByCol(6, 6);
                    break;
                    
                case 3:
                    features[j].values.resizeMatrixByCol(3, 3);
                    break;
                    
                default:
                    break;
            }
        }
        
        for (unsigned int j = 0; j < features.size(); j++)
            if (features[j].name.compare("EnergyEnvelope") == 0)
                if (features[j].values.size() == 0)
                    for (unsigned int k = 0; k < features.size(); k++)
                        if (features[k].name.compare("TotalEnergy") == 0)
                        {
                            features[j].values = features[k].values;
                            break;
                        }

        //string cmd = "rm " + files[i] + ".descr.sdif";
        //system(cmd.c_str());
        string filename = files[i] + ".descr.sdif";
        remove(filename.c_str());
    }
    
    return features;
}
