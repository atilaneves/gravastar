#include "CProjSpecial.hpp"
#include "CShipBluePrint.hpp"
#include "CProjBluePrint.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"
#include "CPilot.hpp"
#include "CProjectileFactory.hpp"
#include <string>


CProjSpecial::CProjSpecial(const CShipBluePrint &shipBluePrint,
                           CShip &ship, CLevel &level):
    CSpecial(shipBluePrint, ship, level,
             shipBluePrint.mProjSpecBluePrint->mSound,
             shipBluePrint.mProjSpecBluePrint->mStatSprite),
    mBluePrint(*shipBluePrint.mProjSpecBluePrint) {


}

const CGravSprite& CProjSpecial::GetSprite() const {
    return *((mBluePrint.GetSprites())[0]);
}


CMoverObj* CProjSpecial::UseAt(const CVector2& pos, const CVector2& vel,
                               const std::string& name, bool shadow) {
    mSound.Play(pos);
    return CProjectileFactory::Instance().CreateObject(name, mBluePrint, mShip,
                                                       pos, vel, shadow);
}
