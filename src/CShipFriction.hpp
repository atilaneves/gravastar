#ifndef CSHIPFRICTION_H
#define CSHIPFRICTION_H


#include "CVector2.hpp"
class CShip;
class CLevel;

class CShipFriction {

public:

  CShipFriction(const CShip &ship, const CLevel &level);

  CVector2 CalcAcc();
  void     SetInTerrain() { mInTerrain = true; }


private:

  bool          mInTerrain;
  const CShip&  mShip;
  const CLevel& mLevel;

  float GetFriction();
  
};


#endif
