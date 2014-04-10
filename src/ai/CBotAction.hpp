#ifndef CBOTACTION_H
#define CBOTACTION_H


class CPilotBot;
class CPilotInputBot;


class CBotAction { //different things the cpu can do

public:

  CBotAction(CPilotBot &pilot):mPilot(pilot) { }

  virtual float GetWeaponAngle() const { return 0; } //wrt to ship's nose
  virtual void  SetShootControl(CPilotInputBot &input) { } //super,special,
  virtual void  Think() = 0; //decide how to accomplish the job
  virtual bool WantsToShoot() { return false; }

  int    GetTargetIndex() const { return mTargetIndex; }
  float GetTargetAngle() const { return mTargetAngle; }
  float GetNoseAngle()   const { return mNoseAngle; }
  //float GetX()           const { return mX; }
  //float GetY()           const { return mY; }


protected:

  void SetNoseAngle(float cruiseSpeed = 325);

  int       mTargetIndex;
  float    mTargetAngle;
  float    mNoseAngle;
  float     mX,mY;
  CPilotBot& mPilot;


};

#endif
