#ifndef CMENUINPUT_HPP
#define CMENUINPUT_HPP


class CMenuInput {

public:

  virtual ~CMenuInput() { }

  virtual bool Up();
  virtual bool Down();
  virtual bool Left();
  virtual bool Right();
  virtual bool Select();
  virtual bool Cancel();


protected:

   static bool sUp;
   static bool sDown;
   static bool sLeft;
   static bool sRight;
   static bool sSelect;
   static bool sCancel;

  bool PressedNow(bool pressed, bool &wasPressing);


};

#endif
