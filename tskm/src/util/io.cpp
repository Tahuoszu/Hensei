/**
 *
 * @file    io.h
 * @brief
 * @author  Henri NG
 * @version 1.0
 * @date    25/05/2014
 *
 */

#include "io.h"

data_symb* loadfiles(string path, string prefix)
{
    DIR *dir;
    struct dirent *ent;

    string file;
    string extx;
    string pref;
    data file_data;
    symb file_symb;
    map<string, data> files_data;
    map<string, symb> files_symb;
    data_symb *ds = NULL;

    if ((dir = opendir (path.c_str())) == NULL)
        perror ("No such directory !");

    else {
        int nb_files = 0;
        while ((ent = readdir(dir)) != NULL) {
            file = ent->d_name;
            if (file.size() < 5)
                continue;
            extx = file.substr(file.size() - 4, 4);
            pref = file.substr(0, prefix.size());
            if ((extx.compare(".int") == 0) && (pref.compare(prefix) == 0)) {
                file_data = readData(path, file);
                files_data.insert(pair<string, data>
                                  (file.substr(0, file.size() - 4), file_data));
                nb_files++;
            }
            if ((extx.compare("tskm") == 0) && (pref.compare(prefix) == 0)) {
                file_symb = readSymb(path, file);
                files_symb.insert(pair<string, symb>
                                  (file.substr(0, file.size() - 5), file_symb));
            }
        }
        if (nb_files == 0) {
            std::cerr << "No files found !" << std::endl;
            exit(EXIT_FAILURE);
        }

        ds = new data_symb[nb_files];
        map<string, data>::iterator dataIt = files_data.begin();
        map<string, symb>::iterator symbIt = files_symb.begin();
        for (int i = 0; i < nb_files; i++) {
            ds[i].filename = dataIt->first;
            ds[i].datas    = dataIt->second;
            ds[i].symbs    = symbIt->second;
            ds[i].lastfile = false;
            ++dataIt;
            ++symbIt;
        }
        ds[nb_files - 1].lastfile = true;
    }
    closedir (dir);
    return ds;
}

data readData(string pathname, string filename)
{
    string path = pathname + filename;
    FILE *file  = fopen(path.c_str(), "r");
    data file_data;
    if (file == NULL)
        std::cerr << "Unable to open file : " << filename << std::endl;
    else {
        int i = 0;
        vector<int> start;
        vector<int> end;
        vector<int> symbol;
        int s, e, sym;
        while (fscanf(file, "%d\t%d\t%d", &sym, &s, &e) == 3) {
            start.push_back(s);
            end.push_back(e);
            symbol.push_back(sym);
            i++;
        }
        file_data.data_size = i;
        file_data.start  = start;
        file_data.end    = end;
        file_data.symbol = symbol;
    }
    fclose(file);
    return file_data;
}

symb readSymb(string pathname, string filename)
{
    string path = pathname + filename;
    std::ifstream file(path.c_str());
    symb file_symb;
    if (!file.is_open())
        std::cerr << "Unable to open file : " << filename << std::endl;
    else {
        int i = 0;
        vector<int> symbol;
        vector<string> label;
        vector<string> descp;
        string line;
        vector<string> tokens;
        while (getline(file, line)) {
            std::istringstream iss(line);
            string token;
            while(std::getline(iss, token, '\t'))
                tokens.push_back(token);
            symbol.push_back(atoi(tokens[0].c_str()));
            label.push_back(tokens[1]);
            descp.push_back(tokens[2]);
            tokens.clear();
            i++;
        }
        file_symb.symb_size = i;
        file_symb.symbol = symbol;
        file_symb.label  = label;
        file_symb.descp  = descp;
    }
    file.close();
    return file_symb;
}

void saveFile(string pathname, string filename, const stringstream& ss)
{
    string filepath = pathname + filename;
    std::ofstream file(filepath.c_str());
    if (!file.is_open())
        std::cerr << "Unable to open file : " << filename << std::endl;
    else
        file << ss.str();
    file.close();
}
