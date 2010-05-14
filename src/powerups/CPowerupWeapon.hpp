#ifndef CPOWERUP_WEAPON_H
#define CPOWERUP_WEAPON_H


#include "CPowerup.hpp"


class CPowerupWeapon: public CPowerup {

public:

 CPowerupWeapon(CPowerups &powerups, 
		CLevel &level, const CVector2 &pos, const CGravSprite& sprite);


private:


 virtual void AffectShip(CShip &ship);

};

#endif
