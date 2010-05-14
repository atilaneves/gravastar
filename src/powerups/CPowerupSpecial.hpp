#ifndef CPOWERUP_SPECIAL_H
#define CPOWERUP_SPECIAL_H

#include "CPowerup.hpp"


class CPowerupSpecial:public CPowerup {

public:

 CPowerupSpecial(CPowerups &powerups, CLevel &level, const CVector2 &pos,
		 const CGravSprite& sprite);


private:

 virtual void AffectShip(CShip &ship);

};

#endif
