#ifndef DATAFILE_H
#define DATAFILE_H


#include <allegro.h>
#include <string>


class CDataFile {

public:

 CDataFile(const char *filename);
 CDataFile(const std::string &filename);
 ~CDataFile();

 static bool FileExists(const std::string &fileName);
 static std::string GetFileName(const std::string &wantedFileName);

 //inlines
 void *GetData(int i) const { return mFile[i].dat; }


private:

 DATAFILE *mFile;

 void Constructor(const std::string &fileName);


};

#endif
