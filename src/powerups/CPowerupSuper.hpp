#ifndef CPOWERUP_SUPER_H
#define CPOWERUP_SUPER_H


#include "CPowerup.hpp"


class CPowerupSuper:public CPowerup {

public:

  CPowerupSuper(CPowerups &powerups,
                CLevel &level, const CVector2 &pos, const CGravSprite& sprite);


private:
  virtual void AffectShip(CShip &ship) override;
};

#endif
