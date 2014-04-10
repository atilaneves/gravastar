#ifndef CPOWERUP_TURN_H
#define CPOWERUP_TURN_H


#include "CPowerup.hpp"


class CPowerupTurn: public CPowerup {

public:

 CPowerupTurn(CPowerups &powerups,
	      CLevel &level, const CVector2 &pos, const CGravSprite& sprite);


private:
  virtual void AffectShip(CShip &ship) override;
};

#endif
