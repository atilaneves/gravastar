#ifndef CNOSE_H
#define CNOSE_H


class CPilotInput;
class CShipBluePrint;
class CShip;
#include "CTimeCounter.hpp"
#include "CVector2.hpp"


class CNose {

public:

  enum { kNbNoses = 32 };

  CNose(const CShipBluePrint &bluePrint, CShip& ship);

  static int   Angle2NoseIndex(float angle);
         void  ApplyInput(const CPilotInput &controls);
         void  BackTrack();
         float GetAngle() const;
         float GetOmega() const { return mOmega; }
         int   GetNose()  const;
  static float NoseIndex2Angle(int nose);
         void  Set(float orientation, float omega = 0);
         void  Spin(const CVector2& force);
         void  Update(float dt);


private:

  float mTurnPower;
  float mNose;
  float mOmega; //angular velocity
  float mLastUpdate;
  CShip& mShip;
  CTimeCounter mSpinCounter;


};


#endif
