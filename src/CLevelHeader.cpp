#include "CLevelHeader.hpp"
#include "CCanvas.hpp"
#include "CDataFile.hpp"
#include "CUnderscoreRemover.hpp"
#include "leveldat.h" //datafile defs
#include <stdio.h>


CLevelHeader::CLevelHeader(unsigned int levelNb):
  mFileName(GetFileName(levelNb) + ".dat"),
  mCfgName(GetFileName(levelNb) + ".cfg") {

 CDataFile datafile(mFileName); //load the data file
 mCanvas.reset(new CCanvas(datafile.GetData(kLEVEL))); //level bmp
 char *attribPtr = (char *)datafile.GetData(kATTRIBUTES);
 char title[200];
 sscanf(attribPtr,"%*s %*s %*s %*s %f %f %f %d %s",
	&mGravity, &mAirFriction, &mLandFriction, &mNbInds, title);
 mTitle = CUnderscoreRemover::Remove(title);
}


int CLevelHeader::GetWidth() const { 
 return mCanvas->GetWidth(); 
}


int CLevelHeader::GetHeight() const { 
 return mCanvas->GetHeight(); 
}


const std::string CLevelHeader::GetFileName(unsigned int levelNb) {
  char nb[100];
  sprintf(nb, "%02d", levelNb);
  return "Levels/level" + std::string(nb);
}

