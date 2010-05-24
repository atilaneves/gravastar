#include "CLevelCounter.hpp"
#include "CDataFile.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


CLevelCounter::CLevelCounter():
  mNbLevels(FindNbLevels()) {

    assert(mNbLevels > 0);
}


int CLevelCounter::FindNbLevels() {

  int nbLevels = 0;
  char fileName[100];
  do { //find out how many levels there are
    sprintf(fileName, "Levels/level%02d.dat", ++nbLevels);
  } while(CDataFile::FileExists(CDataFile::GetFileName(fileName)));

  return nbLevels - 1; //ends up at 1 too many
}


int CLevelCounter::GetRandomLevel() const {
  return rand() % mNbLevels + 1; //1 to nbLevels
}
