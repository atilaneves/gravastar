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
    virtual void         Erase() { mDecorated->Erase(); }
    virtual const CGravSprite& GetSprite() const { return mDecorated->GetSprite(); }
    virtual bool         IsActive()  { return mActive && mDecorated->IsActive(); }
    virtual void         Update(float dt);


private:

    std::unique_ptr<CSpriteObj> mDecorated;
    float                       mFrequency;
    float                       mFlicker;
    bool                        mDraw;
    bool                        mActive;


};


#endif
