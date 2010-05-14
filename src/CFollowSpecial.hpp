#ifndef CFOLLOWSPECIAL_H
#define CFOLLOWSPECIAL_H


#include "CSpecial.hpp"
#include "CSound.hpp"
class CSpriteVector;
class CLevel;
class CFollowBluePrint;
class CFollower;


class CFollowSpecial: public CSpecial {

public:

  CFollowSpecial(const CShipBluePrint &shipBluePrint,
		 CShip &ship, CLevel &level);

  virtual const CGravSprite& GetSprite() const;

  virtual void DrawStats(CCanvas &canvas) const;
  virtual bool IsActive() const;
  virtual void PlaySound();
  virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
			   const std::string& name, bool shadow);


private:

  const CFollowBluePrint& mBluePrint;
  const CSpriteVector&    mSprites;
  CLevel&                 mLevel;
  const CShipStatSprite&  mStatSprite;
  CSound                  mSound;
  CFollower              *mFollower;

  virtual       float            GetDepletionScale(float dt) const;
  virtual const CShipStatSprite& GetStatSprite()     const {
    return mStatSprite; }
  virtual 	void  	   	 NotUsing();


};


#endif
