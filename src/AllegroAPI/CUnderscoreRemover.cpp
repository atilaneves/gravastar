#include "CUnderscoreRemover.hpp"
#include <string.h>


std::string CUnderscoreRemover::Remove(const std::string &toRemove) {

  char str[200];
  strcpy(str, toRemove.c_str());
  
  int i = 0;
  
  while(str[i] != '\0') {
    if(str[i]=='_')
      str[i]=' ';
    i++;
  }
  
  return std::string(str);
}
