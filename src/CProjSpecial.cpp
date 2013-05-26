#include "CProjSpecial.hpp"
#include "CShipBluePrint.hpp"
#include "CProjBluePrint.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CPilot.hpp"
#include "CProjectileFactory.hpp"


CProjSpecial::CProjSpecial(const CShipBluePrint &shipBluePrint,
                           CShip &ship, CLevel &level):
    CSpecial(shipBluePrint, ship),
    mBluePrint(*shipBluePrint.mProjSpecBluePrint), mLevel(level),
    mStatSprite(mBluePrint.mStatSprite), mSound(mBluePrint.mSound) {


}


void CProjSpecial::PlaySound() {
    mSound.Play(mShip.GetPos());
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


void CProjSpecial::DrawStats(CCanvas &canvas) const {

    mStatSprite.Draw(canvas, 0, 11);

    const int col = mTeam.GetMainColour();
    constexpr int x = 0, y = 11, dx = 10;
    const CFont font;
    font.Print(canvas, x + dx, y , col, -1, "x");
    char line[100];
    sprintf(line, "%d", int(mGauge));
    font.Print(canvas, x + 2*dx, y, col, -1, line);

}
