#ifndef CFLICKER_H
#define CFLICKER_H

//decorator pattern to make objects flicker
#include "CSpriteObj.hpp"
#include <memory>


class CFlicker: public CSpriteObj {

public:

  CFlicker(float frequency, CLevel &level, CSpriteObj *spriteObj);

    virtual CLevelSprite Draw() override { return mDraw ? mDecorated->Draw() : CLevelSprite{}; }
            void         Die() { mActive = false; }
            virtual void Erase() override { mDecorated->Erase(); }
            virtual const CGravSprite &GetSprite() const override {
              return mDecorated->GetSprite();
            }
            virtual bool IsActive() override {
              return mActive && mDecorated->IsActive();
            }
            virtual void Update(float dt) override;

private:

    std::unique_ptr<CSpriteObj> mDecorated;
    float                       mFrequency;
    float                       mFlicker;
    bool                        mDraw;
    bool                        mActive;


};


#endif
