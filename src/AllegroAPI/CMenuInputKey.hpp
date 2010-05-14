#ifndef CMENUINPUTKEY_H
#define CMENUINPUTKEY_H


class CMenuInputKey {

public:

  bool Pressed();

  static CMenuInputKey sUp;
  static CMenuInputKey sDown;
  static CMenuInputKey sLeft;
  static CMenuInputKey sRight;
  static CMenuInputKey sSelect;
  static CMenuInputKey sCancel;


private:

  int  mKey;
  bool mWasPressing;

  CMenuInputKey(int key);

};


#endif
