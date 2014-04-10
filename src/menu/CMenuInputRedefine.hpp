#ifndef CMENUINPUTREDEFINE_H
#define CMENUINPUTREDEFINE_H

class CMenuInputRedefine: public CMenuInput {

public:  

  CMenuInputRedefine():mCancelled(false) { }

  virtual bool Up()     { return false; }
  virtual bool Down()   { return false; }   
  virtual bool Left()   { return false; }    
  virtual bool Right()  { return false; }   
  virtual bool Select() { return false; }
  virtual bool Cancel() {
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
