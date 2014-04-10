#ifndef CPOWERUP_INVULNERABLE_H
#define CPOWERUP_INVULNERABLE_H


#include "CPowerup.hpp"


class CPowerupInvulnerable:public CPowerup {

public:

 CPowerupInvulnerable(CPowerups &powerups, CLevel &level, const CVector2 &pos,
                      const CGravSprite& sprite);


private:
  virtual void AffectShip(CShip &ship) override;
};

#endif
