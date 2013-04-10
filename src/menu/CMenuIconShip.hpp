#ifndef CMENUICONSHIP_H
#define CMENUICONSHIP_H


#include "CMenuIconSprite.hpp"
#include "CSprite.hpp"
#include <memory>
class CDataFile;


class CMenuIconShip: public CMenuIconSprite {

public:

  CMenuIconShip(const CDataFile *dataFile, int index);
  virtual ~CMenuIconShip() { }

  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight) const override;

private:

  std::unique_ptr<CSprite> mSpritePtr;

};


#endif
