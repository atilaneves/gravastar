#include "CStealthMine.hpp"
#include "CColour.hpp"
#include "CTeam.hpp"
#include "CCanvas.hpp"
#include "CGravSprite.hpp"
#include "CLevel.hpp"
#include "CPilot.hpp"

int CStealthMine::sNbStealths = 0;
CGravSprite* CStealthMine::sInvisible = 0;



CStealthMine::CStealthMine(const CProjBluePrint &bluePrint, CShip& ship,
			   const CVector2& pos, const CVector2& vel,
			   bool shadow):
  CProjectile(bluePrint, ship, pos, vel, shadow),
  mIsInvisible(false) {

  mCounter.Start(5);
  if(!sNbStealths) sInvisible = CreateInvisible();
  sNbStealths++;
}


CStealthMine::~CStealthMine() {
  sNbStealths--;
  if(!sNbStealths) delete sInvisible;
}


CGravSprite* CStealthMine::CreateInvisible() {
  const CGravSprite& oldSprite = GetSprite();
  CCanvas canvas(oldSprite.GetWidth(), oldSprite.GetHeight());
  oldSprite.Draw(canvas, 0, 0);
  float angle = 0, scale = 1;
  return new CGravSprite(canvas.GetData(), CTeam::sWhite, angle, scale,
			 CColour::GetColour(0, 0, 1));
}


void CStealthMine::Update(float dt) {
  if(mCounter.JustFinished()) mIsInvisible = true;
  CProjectile::Update(dt);
}


CVector2 CStealthMine::CalcAcc() {
  return CVector2(mVel.Theta()) * -1000;
}


const CGravSprite& CStealthMine::GetSprite() const {
  return mIsInvisible ? *sInvisible : CProjectile::GetSprite();
}


void CStealthMine::Hit(CShip& ship, CScreenPos pos, float dt) {
  if(ship.GetPilot().GetTeam() != mPilot.GetTeam())
    CProjectile::Hit(ship, pos, dt);
}


void CStealthMine::Hit(CProjectile& proj, CScreenPos pos, float dt) {
  CProjectile *projPtr = dynamic_cast<CStealthMine*>(&proj);
  if(!projPtr) CProjectile::Hit(proj, pos, dt); //don't hit each other
}
