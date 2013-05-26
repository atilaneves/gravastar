#include "CLunaSeek.hpp"
#include "CSeekFactory.hpp"
#include "CPilotBot.hpp"
#include "CPilots.hpp"
#include "CScramble.hpp"
#include "CPilotInputBot.hpp"
#include "CShip.hpp"



REG_SEEK("Luna", CLunaSeek)



CLunaSeek::CLunaSeek(CPilotBot &pilot):
    CSeekAndDestroy(pilot) {

}


void CLunaSeek::SetShootControl(CPilotInputBot &input) {

    if(mPilot.GetShip().GetWeapons().CanSuper())
        input.SetSuper();
    else if(mPilot.GetShip().GetWeapons().CanSpecial() &&
            !CPilots::GetPilot(mTargetIndex).GetShip().
            IsEffectOn(CScramble::GetID()))
        input.SetSpecial();
    else if(!IsTooHot()) //not waiting to cool down, fire away!
        input.SetWeapon();


}
