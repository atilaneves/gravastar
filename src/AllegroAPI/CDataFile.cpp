#include "CDataFile.hpp"
#include <stdio.h>
#include <stdlib.h>


CDataFile::CDataFile(const char *filename) {
 Constructor(filename);
}


CDataFile::CDataFile(const std::string &filename) {
 Constructor(filename.c_str());
}


void CDataFile::Constructor(const std::string &filename) {

 if(FileExists(filename))
    mFile = load_datafile(filename.c_str());
 else {
    fprintf(stderr,"*** Error: Unable to open file %s ***\n",filename.c_str());
    exit(1);
 }
}


CDataFile::~CDataFile() {
 unload_datafile(mFile);
}


bool CDataFile::FileExists(const std::string &filename) {

 FILE *file;

 file = fopen(filename.c_str(), "r");

 if(file==NULL)
    return false;
 else {
    fclose(file);
    return true;
 }
}
