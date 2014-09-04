/**
 *
 *  @file			outils.h
 *  @brief			Write descriptors data to files
 *  @version        1
 *  @author			Henri NG
 *	@date			20-06-2014
 *
 */

#include "Orchids.h"

#ifndef OUTILS_H
#define OUTILS_H

template <class T>
void writeDescriptors(string pathname, string filename,
					  const vector<feature<T> >& descriptors)
{
	typename vector<feature<T> >::const_iterator d;
	for (d = descriptors.begin(); d != descriptors.end(); ++d) {
		feature<T> desc = *d;
		if (desc.values.size() == 0)
			continue;
		if (desc.name == "EnergyEnvelope")
			continue; 
		string desc_name = desc.name;
		string file = pathname + filename + "_" + desc_name;
		ofstream ofs(file.c_str());
		if (!ofs.is_open())
			std::cerr << "Unable to open file " << filename << std::endl;
		else {
			TArray2<T> values = desc.values;
			typename TArray2<T>::iterator it;
			for (it = values.begin(); it != values.end(); ++it)
				ofs << *it << endl;
			ofs.close();
		}
	}
	return;
}

#endif
