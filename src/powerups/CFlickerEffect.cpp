#include "CFlickerEffect.hpp"
#include "CFollower.hpp"
#include "CFlicker.hpp"
#include "CShip.hpp"
#include "CSpriteObjs.hpp"

CFlickerEffect::CFlickerEffect(const CTeam &team, CShip &ship, CLevel &level,
                               float duration, const CSpriteVector &sprites)
    : CShipEffect(level, ship, duration), mSprites(sprites), mFlicker(nullptr) {
}

void CFlickerEffect::AtStart() {
  const double invHz = 50;
  if(!mFlicker)
    mFlicker = new CFlicker(invHz, mLevel,
                            new CFollower(mSprites, mLevel, mShip));
}


void CFlickerEffect::AtJustFinished() {
  if(CSpriteObjs::HasFlicker(mFlicker)) mFlicker->Die();
  mFlicker = nullptr; // gets deleted automatically
}
