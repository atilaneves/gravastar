#include "CWeapons.hpp"
#include "CSpecialFactory.hpp"


CWeapons::CWeapons(const std::string& name, const CShipBluePrint& bluePrint,
                   CShip &ship, CLevel &level):
    mWeapon(new CWeapon(bluePrint, ship, level)),
    mSpecial(CSpecialFactory::Instance().CreateObject(name, bluePrint,
                                                      ship, level)),
    mSuper(bluePrint, level, ship) {

}


void CWeapons::ApplyInput(const CPilotInput& input) {
    mSuper.ApplyInput(input);
    if(!mSuper.IsActive()) {
        mWeapon->ApplyInput(input);
        mSpecial->ApplyInput(input);
    }
    else
        mSpecial->NotUsing();
}


void CWeapons::Update(float dt) {
    mSuper.Update(dt);
    if(!mSuper.IsActive()) {
        mWeapon->Update(dt);
        mSpecial->Update(dt);
    }
}
