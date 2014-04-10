#include "CDirectory.hpp"
#include <dirent.h>
#include <stdio.h>
#include <string.h>


CDirectory::CDirectory(const std::string& dirName) {
  Constructor(dirName, nullptr);
}


CDirectory::CDirectory(const std::string& dirName, const std::string& extension) {
  Constructor(dirName, &extension);
}


void CDirectory::Constructor(const std::string& dirName, const std::string *extension) {

 DIR *dir;
 dirent *ent;
 std::string dataDirName = DATAFILE_DIR"/" + dirName;
 std::string devDataDirName = DEV_DATAFILE_DIR"/" + dirName;

 dir = opendir(dirName.c_str());
 if (dir == nullptr) {
   dir = opendir(dataDirName.c_str());
   if (dir == nullptr)
     dir = opendir(devDataDirName.c_str());
 }

 if (dir == nullptr)
   perror("Can't open directory");
 else {
   while ((ent = readdir(dir)) != nullptr)
     if (ent->d_name[0] != '.' && // nth that starts with "."
         (extension == nullptr ||
          strstr(ent->d_name, extension->c_str()) != nullptr))
         mEntries.push_back(std::string(ent->d_name));
 }

 FillNoExt();

 if(closedir(dir) != 0) perror("Unable to close directory");

}


void CDirectory::FillNoExt() {

 char entry[200];
 for(unsigned int i = 0; i< mEntries.size(); i++) {
    strcpy(entry, GetEntry(i).c_str());
    char *dot = strstr(entry, ".");
    *dot = '\0'; //terminate string here
    mEntriesNoExt.push_back(std::string(entry));
 }
}
