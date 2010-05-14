#include "CTeam.hpp"
#include "CColour.hpp"
#include <stdlib.h>


CTeam CTeam::sBlue("Blue", 190, 270);
CTeam CTeam::sRed("Red", 340, 400);
CTeam CTeam::sGreen("Green", 90, 150);
CTeam CTeam::sYellow("Yellow", 30, 60);
CTeam CTeam::sWhite("White", 0, 0);


int CTeam::TransformColour(int colour) const {
  if(mStart == mEnd) return colour;
  int index = GetBlueIndex(colour);
  if(index >= 0) return mColours[index];
  float h,s,v;
  CColour::RGBtoHSV(colour, h, s, v);
  if(h < sBlue.mStart || h > sBlue.mEnd) return colour;
  float newHue = h;
  newHue = mStart + 
    ((h - (sBlue.mStart)) / (sBlue.mEnd - sBlue.mStart)) * (mEnd - mStart);
  if(newHue >= 360) newHue -= 360;
  return CColour::HSVtoRGB(newHue, s, v);
}


int CTeam::GetBlueIndex(int colour) { //1st blue colour, 2nd, 3rd?
  for(unsigned int i = 0; i < sBlue.mColours.size(); ++i) {
    if(colour == sBlue.mColours[i]) return i;
  }
  return -1;
}


void CTeam::LoadColours() {
  sBlue.LoadMyColours();
  sRed.LoadMyColours();
  sGreen.LoadMyColours(); 
  sYellow.LoadMyColours();
  sWhite.LoadMyColours();
}


void CTeam::LoadMyColours() {

  FILE *fp = OpenFile();

  for(int i = 0; i < kNbColours; ++i) {
    int r, g, b;
    fscanf(fp, "%d %d %d", &r, &g, &b);
    mColours.push_back(makecol(r, g, b));
  }

  fclose(fp);
}


FILE* CTeam::OpenFile() {

  std::string fileName = "cfg/colours/" + mName + ".cfg";
  FILE *fp = fopen(fileName.c_str(), "r");
  
  if(fp == NULL) {
    fprintf(stderr, "Unable to open file %s", fileName.c_str());
    exit(1);
  }

  return(fp);
}


const CTeam& CTeam::FindByName(const std::string& name) {
  if(name == "Blue")        return sBlue;
  else if(name == "Red")    return sRed;
  else if(name == "Green")  return sGreen;
  else if(name == "Yellow") return sYellow;
  else                      return sWhite;
}
