#ifndef CMENUINPUTREDEFINE_H
#define CMENUINPUTREDEFINE_H

#include "CMenuInput.hpp"
#include "CKeyboard.hpp"

class CMenuInputRedefine: public CMenuInput {

public:

  CMenuInputRedefine():mCancelled(false) { }

  virtual bool Up() override { return false; }
  virtual bool Down() override { return false; }
  virtual bool Left() override { return false; }
  virtual bool Right() override { return false; }
  virtual bool Select() override { return false; }
  virtual bool Cancel() override {
    if(mCancelled) return true;
    mCancelled = PressedNow(CKeyboard::KeyPressed(CKeyboard::kEsc), sCancel);
    return mCancelled;
  }

  bool Cancelled() const { return mCancelled; }
  void Reset() { mCancelled = false; }


private:

  bool mCancelled;



};

#endif
