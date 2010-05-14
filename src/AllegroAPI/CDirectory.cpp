#include "CDirectory.hpp"
#include <dirent.h>
#include <stdio.h>
#include <string.h>


CDirectory::CDirectory(const std::string& dirName) {

 DIR *dir;
 dirent *ent;

 if((dir = opendir(dirName.c_str())) == NULL) {
    perror("Can't open directory");
 }
 else {
    while ((ent = readdir(dir)) != NULL)
       if(ent->d_name[0] != '.') //nth that starts with "."
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
