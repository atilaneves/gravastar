#ifndef CDIRECTORY_H
#define CDIRECTORY_H


#include <vector>
#include <string>
#include <stdlib.h>


class CDirectory {

public:

 CDirectory(const std::string& dirName);
 CDirectory(const std::string& dirName, const std::string& extension);

       int          GetNbEntries() const      { return (int)mEntries.size(); }
 const std::string& GetEntry(int i) const       { return mEntries[i]; }
 const std::string& GetEntryNoExt(int i) const  { return mEntriesNoExt[i]; }
 const std::string& GetRandomNoExt() const  { 
   return mEntriesNoExt[rand() % GetNbEntries()]; }


private:

 std::vector<std::string> mEntries;
 std::vector<std::string> mEntriesNoExt;

 void FillNoExt();
 void Constructor(const std::string& dirName, const std::string* extension);


};

#endif
