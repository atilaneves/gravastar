#ifndef CSHIP_H
#define CSHIP_H


#include "CExplosive.hpp"
#include "CEngine.hpp"
#include "CNose.hpp"
#include "CSound.hpp"
#include "CShipFriction.hpp"
#include "CShipCollider.hpp"
#include "CShipAura.hpp"
#include "CShipEffects.hpp"
#include "CExplosionPause.hpp"
#include "CWeapons.hpp"
#include <memory>
class CPilotInput;
class CBase;
class CShipBluePrint;
class CSpriteVector;
class CFollowBluePrint;


class CShip: public CExplosive {

  friend class CShipCollider;
  friend class CScramble;
  friend class CInvulnerable;
  friend class CEMP;
  friend class CEMB;

public:

  CShip(const CShipBluePrint &bluePrint, CPilot &pilot, CLevel &level);
  virtual ~CShip();

  virtual void     ApplyInput(const CPilotInput &controls);
  virtual void AtDeath() override;
          void     BackTrack(float dt) { mPos -= mVel*dt; mNose.BackTrack();}
          void     BounceOff(float edgeAngle, float dt);
          float    BouncedOff(const CScreenPos& pos, float& edgeAngle) {
           return mCollider.BouncedOff(pos, edgeAngle); }
          virtual CVector2 CalcAcc() override;
  virtual bool     CanMoveSuper() const { return false; }
    virtual CLevelSprite Draw() override { return mHull > 0 ? CExplosive::Draw() : CLevelSprite{}; }
          int      GetNose() const { return mNose.GetNose(); }
          CPilot&  GetPilot() const { return mPilot; }
          virtual int GetSpriteIndex() const override {
            return mNose.GetNose();
          }
   const CWeapons& GetWeapons() const { return mWeapons; }
         CWeapons& GetWeapons() { return mWeapons; }
         virtual void Hit(CSpriteObj &obj, CScreenPos pos, float dt) override {
                       obj.Hit(*this, pos, dt); }
         virtual void Hit(CProjectile &proj, CScreenPos pos, float dt) override;
         virtual void Hit(CShip &ship, CScreenPos pos, float dt) override;
         virtual bool IsActive() override {
           return CExplosive::IsActive() ||
                  mEffects.IsActive(CExplosionPause::GetID());
         }
          bool     IsEffectOn(int i) { return mEffects.IsActive(i); }
          void     LandDamage(float dt) { mCollider.LandDamage(dt); }
  const CShipAura& GetAura() const { return mAura; }
        CLevel&    GetLevel() const { return mLevel; }
  virtual void     LoseHull(float amount, CPilot &pilot);
  virtual void Move(float dt) override;
          void     PullBack(const CSpriteObj& obj, float angle);
          void     Push(const CVector2& speed, CPilot& pilot);
          void     Rebound(float angle, float r = 0.4);
          void     Repair(float dt) { mAura.Repair(dt); }
          void     StartEffect(int e, float d=-1) { mEffects.Start(e,d); }
          virtual void Stop(float t) override {
            CSpriteObj::Stop(t);
            mEffects.Pause(t);
          }
  virtual void     UseSpecial(float dt) = 0;
  virtual void     UseSuper(float dt, bool use = true) = 0;
  virtual void     UseWeapon(float dt)  = 0;


protected:

  CEngine                 mEngine;
  CNose                   mNose;
  CShipFriction           mFriction;
  CShipCollider           mCollider;
  CShipAura               mAura;
  CSound                  mSpawn;
  const CSpriteVector&    mInvSprites;
  const CSpriteVector&    mScrambleSprites;
  const CSpriteVector&    mEMPSprites;
  CShipEffects            mEffects;
  CWeapons                mWeapons;
  const CProjBluePrint&   mExtraProjBluePrint;
  const CFollowBluePrint& mExtraFollowBluePrint;

  virtual void HitTerrain(const CScreenPos &where, float dt) override;
  virtual void OutOfBounds(float angle) override { Rebound(angle, 0.35); }
};


#endif
