#include "CShipStatSprite.hpp"
#include "CGravSprite.hpp"
#include "CDataFile.hpp"
#include "CCanvas.hpp"
#include "deltadat.h"
#include <math.h> //M_PI


CShipStatSprite::CShipStatSprite(void *data, const CTeam& team):
  mTeam(team) {

  float angle = M_PI/2;
  CCanvas canvas(data); //just to get width
  mScale = 11.0 / canvas.GetWidth();
  mSprite.reset(new CGravSprite(data, team, angle, mScale));
}


CShipStatSprite::CShipStatSprite(const CShipStatSprite& sprite):
  mScale(sprite.mScale), mTeam(sprite.mTeam) {

  CCanvas canvas(sprite.GetWidth(), sprite.GetHeight());
  sprite.Draw(canvas, 0, 0);
  float angle = 0;
  mSprite.reset(new CGravSprite(canvas.GetData(), mTeam, angle, mScale));
}


void CShipStatSprite::Draw(CCanvas& canvas, int x, int y) const {
  mSprite->Draw(canvas, x, y);
}
