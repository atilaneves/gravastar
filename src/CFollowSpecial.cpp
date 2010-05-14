#include "CFollowSpecial.hpp"
#include "CShipBluePrint.hpp"
#include "CShip.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"
#include "CPilot.hpp"
#include "CFollowFactory.hpp"
#include "CFollowBluePrint.hpp"
#include "CRect.hpp"
#include "CRectFill.hpp"
#include "CSpriteObjs.hpp"


CFollowSpecial::CFollowSpecial(const CShipBluePrint &shipBluePrint,
			       CShip &ship, CLevel &level):
  CSpecial(shipBluePrint, ship),
  mBluePrint(*shipBluePrint.mFollowSpecBluePrint.get()),
  mSprites(mBluePrint.GetSprites()),
  mLevel(level),
  mStatSprite(mBluePrint.mStatSprite), mSound(mBluePrint.mSound),
  mFollower(0) {


}


void CFollowSpecial::PlaySound() {
  mSound.Play(mShip.GetPos());
}


const CGravSprite& CFollowSpecial::GetSprite() const {
  return *((mBluePrint.GetSprites())[0]);
}


CMoverObj* CFollowSpecial::UseAt(const CVector2& pos, const CVector2& vel,
				 const std::string& name, bool shadow) {
  if(!mFollower) {
    CSound * const sound = 0;
    const CVector2 offset(0, 0);
    CFollowFactory& factory = CFollowFactory::Instance();
    mFollower = factory.CreateObject(name, mBluePrint.GetSprites(),
				     mLevel, mShip, sound, offset);
    PlaySound();
  }

  return mFollower;
}


void CFollowSpecial::NotUsing() {
  if(mFollower && CSpriteObjs::HasObj(mFollower) &&
     dynamic_cast<CFollower*>(mFollower))
    mFollower->Die();
  mFollower = 0;
}


bool CFollowSpecial::IsActive() const {
  return mFollower ? mFollower->IsActive() : false; 
}


float CFollowSpecial::GetDepletionScale(float dt) const {
  return 50*dt;
}


void CFollowSpecial::DrawStats(CCanvas &canvas) const {

  mStatSprite.Draw(canvas, 0, 11);

  const int kMaxSpecial=10; //reference
  const int kMaxWidth=22;

  int outerRim = 2;
  int x0 = 37, y0 = 10; //where special bar starts
  float maxSpecialGauge = mShip.GetWeapons().GetMaxSpecialGauge();
  int w0 = int(kMaxWidth*(maxSpecialGauge/kMaxSpecial)) + outerRim;
  int h0 = 5;
  
  CRect rect(canvas, x0, y0, x0+w0-1, y0+h0-1, CTeam::sWhite.GetMainColour());
  
  int x1 = x0 + outerRim/2;
  int y1 = y0 + outerRim/2;
  int w1 = int(kMaxWidth*mShip.GetWeapons().GetSpecialGauge()/kMaxSpecial);
  if(w1<0) w1=0; //has to go forward...
  int h1 = h0 - outerRim;
  
  if(w1) CRectFill rectFill(canvas, x1,y1,x1+w1-1,y1+h1-1,
			    mShip.GetPilot().GetTeam().GetSecondaryColour());
}
