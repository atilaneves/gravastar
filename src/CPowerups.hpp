#ifndef CPOWERUPS_H
#define CPOWERUPS_H


class CPowerup;
class CLevel;
class CGravSprite;
#include "CVector2.hpp"
#include <vector>
#include <map>
#include <string>


class CPowerups {

public:

 CPowerups(CLevel& level, float rate);
 ~CPowerups();

        void      Generate(float dt); //chk and make a powerup show up
        float     NearestDistance(const CVector2& shipPos) const;
  const CPowerup* NearestPowerup(const CVector2& shipPos) const;
        void      Remove(CPowerup *powerup);


private:

  typedef std::map<std::string, CGravSprite*>::iterator spritePlace_t;

  CLevel& mLevel;
  float mRate; //how often powerups show up
  std::vector<CPowerup*>    mPowerups;
  std::vector<std::string>  mNames;
  std::map<std::string, CGravSprite*> mSpritesMap;

};


#endif
