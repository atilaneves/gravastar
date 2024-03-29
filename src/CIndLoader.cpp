#include "CIndLoader.hpp"
#include "CCanvas.hpp"
#include "CSpriteFinder.hpp"
#include "CDataFile.hpp"
#include <assert.h>
#include <stdio.h>
#include <iostream>


extern bool gDebug;


CIndLoader::CIndLoader(std::string &fileName, const CCanvas &canvas,
                       IndsBmp_t indBmps, void *baseBmp):
  mFileName(CDataFile::GetFileName(fileName)), mCanvas(canvas) {

  bool loaded = LoadCoords();

  if(!loaded) {
    mIndsPos  = FindIndsPos(indBmps);
    mBasesPos = FindIndsPos(IndsBmp_t(1, baseBmp)); //make vector out of 1 bmp
    if(gDebug) printf("inds: %zu %zu\n", indBmps.size(), mIndsPos.size());
    if(gDebug) printf("bases: %zu\n", mBasesPos.size());
    assert(indBmps.size() == mIndsPos.size());
    //assert(mBasesPos.size() <= 4);
    SaveCoords();
  }
}


IndsPos_t CIndLoader::FindIndsPos(IndsBmp_t bmps) {

  IndsPos_t indsPos;

  for (auto &bmp : bmps) {

    CCanvas ind(bmp);
    CScreenPos centre(ind.GetWidth()/2, ind.GetHeight()/2);
    Positions_t poss = CSpriteFinder::FindSprites(mCanvas, ind);

    for (auto &pos : poss)
      indsPos.push_back(pos + centre);
  }

  return indsPos;
}


bool CIndLoader::LoadCoords() {

  FILE *fp = fopen(mFileName.c_str(), "r");

  if(fp) {
    int nbBases = 0, nbInds = 0;
    fscanf(fp, "%*s %d %*s %d", &nbBases, &nbInds);
    for(int i = 0; i < nbBases; i++) mBasesPos.push_back(LoadPos(fp));
    for(int i = 0; i < nbInds; i++)  mIndsPos.push_back(LoadPos(fp));
    fclose(fp);
    return true;
  }

  return false;
}


CScreenPos CIndLoader::LoadPos(FILE *fp) {
  int x, y;
  fscanf(fp, "%d %d", &x, &y);
  return CScreenPos(x, y);
}


void CIndLoader::SaveCoords() {

  FILE *fp = fopen(mFileName.c_str(), "w");

  if(fp) {
    fprintf(fp, "nbBases: %zu nbInds: %zu\n", mBasesPos.size(), mIndsPos.size());
    for (auto &elem : mBasesPos)
      fprintf(fp, "%d %d\n", elem.GetX(), elem.GetY());
    for (auto &elem : mIndsPos)
      fprintf(fp, "%d %d\n", elem.GetX(), elem.GetY());
    fclose(fp);
  }
  else
    std::cerr << "*** Error: could not open " << mFileName <<
      " to write ***\n";
}
