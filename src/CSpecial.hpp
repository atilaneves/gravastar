#ifndef CSPECIAL_H
#define CSPECIAL_H


#include "CSound.hpp"
#include "CVector2.hpp"
#include <stdint.h>
class CShip;
class CShipBluePrint;
class CPilotInput;
class CShipStatSprite;
class CCanvas;
class CPilot;
class CGravSprite;
class CMoverObj;
class CTeam;
class CLevel;


class CSpecial { //special weapon

public:

    CSpecial(const CShipBluePrint &bluePrint, CShip& ship,
             CLevel& level, CSound sound,
             const CShipStatSprite& statSprite);
    virtual ~CSpecial() { }

    virtual const CGravSprite& GetSprite() const = 0;

            void       ApplyInput(const CPilotInput& input);
            bool       CanUse()  const;
            float      GetDepletion() const { return mDepletion; }
            float      GetGauge()    const { return mGauge;    }
            float      GetMaxGauge() const { return mMaxGauge; }
            size_t     GetStatSpriteHash() const;
    virtual bool       IsActive() const = 0;
            bool       IsAtMax()     const { return mGauge >= mMaxGauge; }
            void       LoseGauge(float amount);
    virtual void       NotUsing() = 0;
    virtual void       PlaySound();
            void       Update(float dt);
    virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
                             const std::string &name, bool shadow = false)=0;
    virtual uint8_t GetSpecialHash() const = 0;

protected:

    CShip& mShip;
    CLevel& mLevel;
    CSound mSound;

    uint8_t GetTeamHash() const;

private:

    const CTeam& mTeam;
    const CShipStatSprite& mStatSprite;

    bool   mUsing;
    CSound mRepairSound;
    int    mRate;
    float  mMaxGauge, mGauge, mDepletion, mRecovery;

    virtual float GetDepletionScale(float dt) const = 0;

};


#endif
