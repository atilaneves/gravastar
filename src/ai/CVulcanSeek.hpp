#ifndef CVULCAN_SEEK_H
#define CVULCAN_SEEK_H


#include "CSeekAndDestroy.hpp"


class CVulcanSeek:public CSeekAndDestroy {

public:

  CVulcanSeek(CPilotBot &pilot);

  virtual float GetWeaponAngle() const;
  virtual bool  WantsToShoot() { return mIsClustering; }


private:

  bool mIsBombing;
  bool mIsClustering;

  virtual void SetShootControl(CPilotInputBot &input);
  virtual void Think();


};



#endif
