#ifndef CPOWERUP_HULL_H
#define CPOWERUP_HULL_H

class CSound;
#include "CPowerup.hpp"


class CPowerupHull: public CPowerup {

public:

 CPowerupHull(CPowerups &powerups, CLevel &level,
	      const CVector2 &pos, const CGravSprite& sprite);


private:

 CSound *mSound;

 virtual void AffectShip(CShip &ship) override;
};

#endif
