#ifndef CEXPLOSIVEBLUEPRINT_H
#define CEXPLOSIVEBLUEPRINT_H


#include "CMoverBluePrint.hpp"
#include "CSound.hpp"
#include <string>
#include <memory>
class CTeam;
class CDataFile;
class CShipYard;


class CExplosiveBluePrint {

  friend class CExplosive;

public:

  enum { kNbExpFrames = 4 };

  CExplosiveBluePrint(int startPos, const std::string &name,
                      const CDataFile &dataFile, const CTeam &team);

  const CSpriteVector& GetSprites() const {
    return mMoverBluePrint.GetSprites(); }

  const CSpriteVector& GetExplosionSprites() const {
    return mExplosionSprites; }


private:

  CMoverBluePrint mMoverBluePrint;
  CSpriteVector   mExplosionSprites;
  std::unique_ptr<CSound> mSound;

};


#endif
