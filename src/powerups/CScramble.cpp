#include "CScramble.hpp"
#include "CEffectFactory.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"
#include <stdlib.h>


REG_EFFECT(CScramble) //register w/ the factory


static float duration = 1.5;
CScramble::CScramble(const CTeam &team, CShip& ship, CLevel& level):
  CFlickerEffect(team, ship, level, duration, ship.mScrambleSprites) {

}


void CScramble::Affect() {
  if(!mShip.IsAlive()) {
    AtJustFinished();
    return;
  }
  CPilotInputBot input;
  if(rand() % 2 == 0) {
    if(rand() % 5 == 0) input.SetLeft();
    else                input.SetRight();
  }
  if(rand() % 5  == 0) input.SetThrust();
  if(rand() % 10 == 0) input.SetWeapon();
  if(rand() % 20  == 0) {
    input.SetSpecial();
    input.SetWeapon(false);
  }
  mShip.ApplyInput(input);
}
