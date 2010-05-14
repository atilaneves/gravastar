#ifndef CFLICKER_H
#define CFLICKER_H

//decorator pattern to make objects flicker
#include "CSpriteObj.hpp"
#include <memory>


class CFlicker: public CSpriteObj {

public:

  CFlicker(float frequency, CLevel &level, CSpriteObj *spriteObj);

  virtual void Draw()  { if(mDraw) mDecorated->Draw();  }
          void Die() { mActive = false; }
  virtual void Erase() { mDecorated->Erase(); }
  virtual const CGravSprite& GetSprite() const {
    return mDecorated->GetSprite(); }
  virtual bool IsActive()  { return mActive && mDecorated->IsActive(); }
  virtual void Update(float dt);


private:

  std::auto_ptr<CSpriteObj> mDecorated;
  float                     mFrequency;
  float                     mFlicker;
  bool                      mDraw;
  bool                      mActive;


};


#endif
