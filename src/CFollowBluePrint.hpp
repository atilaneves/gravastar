#ifndef CFOLLOWBLUEPRINT_H
#define CFOLLOWBLUEPRINT_H


#include "CMoverBluePrint.hpp"
#include "CSound.hpp"
#include "CShipStatSprite.hpp"
class CTeam;
class CDataFile;


class CFollowBluePrint {

  friend class CFollowSpecial;

public:

  CFollowBluePrint(const std::string &name, const CTeam &team);

  const CSound& GetSound() const { return mSound; }

  const CSpriteVector& GetSprites() const {
    return mMoverBluePrint.GetSprites(); }


private:

  CDataFile *mDataFile;
  const CTeam& mTeam;
  CMoverBluePrint mMoverBluePrint;
  CShipStatSprite mStatSprite;
  CSound mSound;

};


#endif
