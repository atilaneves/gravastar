#include "CPulseLaser.hpp"
#include "CShip.hpp"
#include "CProjBluePrint.hpp"
#include "CSpriteObjs.hpp"
#include "debug.hpp"


CPulseLaser::CPulseLaser(const CProjBluePrint &bluePrint, CShip& ship,
                         const CVector2& pos, const CVector2& vel,
                         bool shadow):
    CProjectile(bluePrint, ship, pos, vel, shadow),
    mBeam(new CSuperBeam(bluePrint.GetSprites(), mLevel, ship, this)) {
    DEBUG("pulse beam %p\n", mBeam);
    mCounter.Start(0.075);
}


void CPulseLaser::Move(float dt) {
    if(!CSpriteObjs::HasObj(mBeam)) { //oops
        Die();
        return;
    }
    mBeam->Move(dt);
    mNose = mBeam->GetNose();
    mVel = CVector2(0, 0);
    mPos = mBeam->GetPos();
    if(!mCounter.IsActive()) {
        CheckCollision(dt);
        Die();
    }
}


void CPulseLaser::AtDeath() {
    DEBUG("PulseLaser AtDeath    ");
    if(!mCounter.IsActive() && CSpriteObjs::HasObj(mBeam) &&
       mBeam->IsActive()) {
        DEBUG("Killed superBeam");
        mBeam->Die();
    }
    DEBUG("\n");
}


CLevelSprite CPulseLaser::Draw() {
    return {};
}


void CPulseLaser::Erase() {
}


void CPulseLaser::HitShipEffect(CShip& ship, CScreenPos pos, float dt) {
    //big ships get less damage
    mDamage *= exp(0.03 * (ship.GetHeight() - 20));
}


void CPulseLaser::Hit(CShip& ship, CScreenPos pos, float dt) {
    CProjectile::Hit(ship, pos, dt);
    mHull = mMaxHull; //we don't die til the counter runs out
}
