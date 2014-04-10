#ifndef CFOLLOWER_H
#define CFOLLOWER_H


#include "CMoverObj.hpp"
#include "CSound.hpp"
#include <memory>


class CFollower: public CMoverObj {

public:

    CFollower(const CSpriteVector &sprites, CLevel &level, CMoverObj &mover,
              CSound *sound = nullptr, const CVector2& offset = CVector2(0, 0));
    virtual ~CFollower();

    virtual CVector2 CalcAcc() override { return CVector2(0, 0); }
    virtual void     Die() override { mActive = false; }
    virtual int      GetSpriteIndex() const override { return mSpriteIndex; }
    virtual bool     IsActive() override { return mActive && mFollowed.IsAlive(); }
    virtual void     Move(float dt) override;
    virtual void     OutOfBounds(float dt) override { (void)dt;}


protected:

    bool                    mActive;
    int                     mSpriteIndex;
    CMoverObj&              mFollowed;
    std::unique_ptr<CSound> mSound;
    CVector2                mOffset;

};


#endif
