#include "CFollower.hpp"
#include "CSound.hpp"


CFollower::CFollower(const CSpriteVector &sprites, CLevel &level,
                     CMoverObj &mover, CSound *sound, const CVector2& offset):
    CMoverObj(sprites, level, mover.GetPos(), CVector2(0, 0)),
    mActive(true), mSpriteIndex(mover.GetSpriteIndex()), mFollowed(mover),
    mSound(sound), mOffset(offset) {

    const int kVolume = 1;
    const bool kLoop = true;
    if(mSound) mSound->Play(mPos, kVolume, kLoop);
}


CFollower::~CFollower() {

}


void CFollower::Move(float dt) {
    CVector2 offset = CVector2(mFollowed.GetVel().Theta() + mOffset.Theta()) *
        mOffset.Radius();
    mPos = mFollowed.GetPos() + offset;
    mSpriteIndex = mFollowed.GetSpriteIndex();
    if(mSound) mSound->Adjust(mPos);
}
