#ifndef CSHIPSOUNDS_H
#define CSHIPSOUNDS_H


#include "CSound.hpp"
class CShipYard;


class CShipSounds {

  friend class CShip;
  friend class CEngine;
  friend class CShipAura;
  friend class CSuper;
  friend class CSpecial;
  friend class CSoliton;
  friend class CVoidhar;
  friend class CPhantom;
  friend class CGamma;


public:

  CShipSounds();


private:

  CSound         mSpawnSound, mExaustSound;
  CSound         mSuperSound, mSuperExpSound, mSuperBeamSound;
  CSound         mRepairSound, mKlangSound;
  CSound         mFlashForward, mShockwave, mEMP;

};


#endif
