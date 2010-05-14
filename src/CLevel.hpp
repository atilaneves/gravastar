#ifndef CLEVEL_H
#define CLEVEL_H

#include "CLevelHeader.hpp"
#include "CBase.hpp"
#include "CIndestructible.hpp"
#include "CIndLoader.hpp"
#include "CSound.hpp"
#include "CLevelGfx.hpp"
#include <vector>
class CDataFile;
class CGravSprite;


typedef std::vector<CIndestructible*> Inds_t;
typedef std::vector<CBase*>           Bases_t;


class CLevel: public CLevelHeader {

public:

  CLevel(unsigned int levelNb);

  const Bases_t& GetBases() const { return mBases; }
        CVector2 GetFreePos(const CGravSprite &sprite) const;


  bool  BlackPixel(int x,int y) const { return mGfx.BlackPixel(x, y); }
  bool  BlackPixel(const CScreenPos& p) const {
    return mGfx.BlackPixel(p.GetX(), p.GetY()); }
  float FindEdge(CScreenPos pos) const { return mGfx.FindEdge(pos); }
  bool  IsClearLine(float x1,float y1,float x2,float y2,int step=5) const {
    return mGfx.IsClearLine(x1, y1, x2, y2, step); }
  bool  IsClearLine(const CVector2& p1, const CVector2& p2, int step=5) const {
    return mGfx.IsClearLine(p1, p2, step); }
  bool  IsFreeSquare(int xc,int yc,int side = 5) const {
    return mGfx.IsFreeSquare(xc, yc, side);
  }
  bool  IsFreeSquare(const CScreenPos& p,int side = 5) const {
    return mGfx.IsFreeSquare(p.GetX(), p.GetY(), side);
  }


private:

  CSound    mKlang;
  Inds_t    mInds;
  Bases_t   mBases;
  CLevelGfx mGfx;

  //prevent creation of the object
  CLevel(const CLevel &level);
  CLevel& operator=(const CLevel &level);

  IndsBmp_t GetIndBmps(const CDataFile &dataFile);

};

#endif
