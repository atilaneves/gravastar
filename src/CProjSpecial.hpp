#ifndef CPROJSPECIAL_H
#define CPROJSPECIAL_H


#include "CSpecial.hpp"
#include "CSound.hpp"
class CProjBluePrint;
class CLevel;


class CProjSpecial: public CSpecial {

public:

  CProjSpecial(const CShipBluePrint &shipBluePrint,
	       CShip &ship, CLevel &level);

  virtual const CGravSprite& GetSprite() const;

  virtual void DrawStats(CCanvas &canvas) const;
  virtual bool IsActive() const { return true; }
  virtual void PlaySound();
  virtual CMoverObj* UseAt(const CVector2& pos, const CVector2& vel,
			   const std::string& name, bool shadow);


private:

  const CProjBluePrint&  mBluePrint;
  CLevel&                mLevel;
  const CShipStatSprite& mStatSprite;
  CSound                 mSound;

  virtual       float 	         GetDepletionScale(float dt) const { return 1; }
  virtual const CShipStatSprite& GetStatSprite()     const {
    return mStatSprite; }
  virtual 	void  	   	 NotUsing() { }


};


#endif
