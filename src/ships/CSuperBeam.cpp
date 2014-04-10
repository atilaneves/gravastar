#include "CSuperBeam.hpp"
#include "CProjectile.hpp"
#include "CShip.hpp"
#include "CShips.hpp"
#include "CLevel.hpp"
#include "CSpriteObjs.hpp"
#include "CPulseLaser.hpp"
#include "CNose.hpp"
#include "debug.hpp"



CSuperBeam::CSuperBeam(const CSpriteVector &sprites, CLevel &level,
                       CShip &ship, CPulseLaser *pulseLaser):
    CWeaponFollow(sprites, level, ship),
    mPulseLaser(pulseLaser),
    mStartPos(0, 0) {
    DEBUG("superBeam %p\n", this);
    SetDamage(75);
}



void CSuperBeam::Move(float dt) {
    mSpriteIndex = mFollowed.GetSpriteIndex();
    mStartPos = mFollowed.GetPos() +
        CVector2(CNose::NoseIndex2Angle(GetSpriteIndex())) *
        mFollowed.GetHeight() * 0.8;
    CVector2 dPos(CNose::NoseIndex2Angle(GetSpriteIndex()));
    bool updated = false; //no need to have been drawn 1st
    mPos = mStartPos;

    while(mLevel.IsFreeSquare(CScreenPos(mPos), 2) &&
          !CShips::Find(CScreenPos(mPos), updated) &&
          mPos.GetX() >= 0 && mPos.GetY() >= 0 &&
          mPos.GetX() < mLevel.GetWidth() && mPos.GetY() < mLevel.GetHeight()) {
        CSpriteObj *sprObj = CSpriteObjs::HitObj(CScreenPos(mPos), updated);
        CProjectile *proj = dynamic_cast<CProjectile*>(sprObj);
        if(proj) proj->Die();
        mPos += dPos;
    }

    CheckCollision(dt);
}


CLevelSprite CSuperBeam::Draw() {
    std::vector<CScreenPos> positions = GetPositions();
    for(unsigned int i = 0; i < positions.size(); i++)
        GetSprite().Draw(mLevel.GetCanvas(),
                         positions[i].GetX() - GetWidth() / 2,
                         positions[i].GetY() - GetWidth() / 2);
    return {};
}



void CSuperBeam::Erase() {
    std::vector<CScreenPos> positions = GetPositions();
    for(unsigned int i = 0; i < positions.size(); i++)
        GetSprite().Erase(mLevel.GetCanvas(),
                          positions[i].GetX() - GetWidth() / 2,
                          positions[i].GetY() - GetWidth() / 2);
}


std::vector<CScreenPos> CSuperBeam::GetPositions() {
    std::vector<CScreenPos> positions;
    CVector2 dPos = CVector2((mPos - mStartPos).Theta()) * 8;
    float dist = (mPos - mStartPos).Radius();
    for(CVector2 pos = mStartPos; (pos-mStartPos).Radius() < dist; pos += dPos)
        positions.push_back(CScreenPos(pos));
    return positions;
}


int CSuperBeam::GetNose() const {
    return CNose::Angle2NoseIndex((mPos - mStartPos).Theta());
}


bool CSuperBeam::IsActive() {
    return CWeaponFollow::IsActive() &&
        (!mPulseLaser || (CSpriteObjs::HasObj(mPulseLaser) &&
                          mPulseLaser->IsActive()));
}
