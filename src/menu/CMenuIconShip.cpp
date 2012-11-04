#include "CMenuIconShip.hpp"
#include "CDataFile.hpp"
#include "deltadat.h"
#include "pi.hpp"


static CSprite* gSprite;
static const float gAngle = M_PI_2;


CMenuIconShip::CMenuIconShip(const CDataFile *dataFile, int index):
  CMenuIconSprite(*(gSprite = new CSprite(dataFile->GetData(index), gAngle))),
  mSpritePtr(gSprite) {

}


void CMenuIconShip::Draw(CCanvas &canvas, int x, int y, bool highlight) {
  mSprite.Draw(canvas, x - GetWidth() / 2, y - GetHeight() / 2);
}
