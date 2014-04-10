#ifndef CPOWERUP_THRUST_H
#define CPOWERUP_THRUST_H


#include "CPowerup.hpp"


class CPowerupThrust: public CPowerup {

public:

 CPowerupThrust(CPowerups &powerups,
		CLevel &level, const CVector2 &pos, const CGravSprite& sprite);


private:
  virtual void AffectShip(CShip &ship) override;
};

#endif
