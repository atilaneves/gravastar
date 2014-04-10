#include "CLevel.hpp"
#include "CSound.hpp"
#include "CDataFile.hpp"
#include "CPoint2D.hpp"
#include "leveldat.h" //datafile defs
#include <stdlib.h>
#include <assert.h>


extern bool gDebug;


CLevel::CLevel(unsigned int levelNb):
  CLevelHeader(levelNb),
  mKlang("klang"), mGfx(*mCanvas) {

  CSound::SetMaxX(GetWidth());
  CPoint2D::SetLevel(*this);

  CDataFile dataFile(mFileName);
  IndsBmp_t indBmps = GetIndBmps(dataFile);
  void*     baseBmp = dataFile.GetData(kBASE);
  CIndLoader indLoader(mCfgName, GetCanvas(), indBmps, baseBmp);

  for(int i = 0; i < indLoader.GetNbBases(); ++i) {
    auto sprite = new CGravSprite(baseBmp);
    mBases.push_back(new CBase(*this, indLoader.GetBasePos(i),
                               sprite, mKlang));
  }

  for(unsigned int i = 0; i < indBmps.size(); ++i) {
    auto sprite = new CGravSprite(indBmps[i]);
    mInds.push_back(new CIndestructible(*this, indLoader.GetIndPos(i),
                                        sprite, mKlang));
  }
}


IndsBmp_t CLevel::GetIndBmps(const CDataFile &dataFile) {

  IndsBmp_t indBmps;
  for(int i = kZIND1; i < kZIND1 + mNbInds; i++)
    indBmps.push_back(dataFile.GetData(i));

  return indBmps;
}


CVector2 CLevel::GetFreePos(const CGravSprite &sprite) const {
   std::vector<int> indices(mBases.size());

   for(unsigned int i = 0; i < mBases.size(); i++)
     indices[i]=i;

   unsigned int index; //declared here to survive the "do" scope
   CVector2 pos(-1, -1);
   do {
     int vecIndex = rand() % indices.size();
     index = indices[vecIndex]; //random base
     auto where = indices.begin() + vecIndex; // location
     indices.erase(where); //not considering this one anymore
     pos = mBases[index]->GetFreePos(sprite);
   } while(pos.GetX() < 0 && indices.size() > 0); //til empty spot's found

   assert(pos.GetX() > 0);
   return pos;
}
