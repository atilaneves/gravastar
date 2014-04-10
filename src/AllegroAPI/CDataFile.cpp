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

  std::string realFileName = GetFileName(filename);

  if(FileExists(filename))
    mFile = load_datafile(filename.c_str());
#ifdef DATAFILE_DIR
  else if(FileExists(DATAFILE_DIR"/" + filename)) {
    std::string dataFilename = DATAFILE_DIR"/" + filename;
    mFile = load_datafile(dataFilename.c_str());
  }
#endif
#ifdef DEV_DATAFILE_DIR
  else if(FileExists(DEV_DATAFILE_DIR"/" + filename)) {
    std::string dataFilename = DEV_DATAFILE_DIR"/" + filename;
    mFile = load_datafile(dataFilename.c_str());
  }
#endif
  else {
    fprintf(stderr,"*** Error: Unable to open file %s ***\n", filename.c_str());
    exit(1);
  }
}


CDataFile::~CDataFile() {
 unload_datafile(mFile);
}


bool CDataFile::FileExists(const std::string &filename) {

 FILE *file;

 file = fopen(filename.c_str(), "r");

 if (file == nullptr)
    return false;
 else {
    fclose(file);
    return true;
 }
}

std::string CDataFile::GetFileName(const std::string &wantedFileName) {

  std::string fileName = wantedFileName;
  if(!CDataFile::FileExists(fileName)) {
#ifdef DATAFILE_DIR
    if(CDataFile::FileExists(DATAFILE_DIR"/" + fileName))
      fileName = DATAFILE_DIR"/" + fileName;
#endif
#ifdef DEV_DATAFILE_DIR
    if(CDataFile::FileExists(DEV_DATAFILE_DIR"/" + fileName))
      fileName = DEV_DATAFILE_DIR"/" + fileName;
#endif
  }

  return fileName;
}
