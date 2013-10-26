#include "CPilotInputProxy.hpp"
#include "Cereal.hpp"


CPilotInputProxy::CPilotInputProxy(bool left, bool right, bool thrust,
                                   bool weapon, bool special, bool super, bool start):
    mLeft(left), mRight(right), mThrust(thrust),
    mWeapon(weapon), mSpecial(special), mSuper(super), mStart(start)
{
}


void CPilotInputProxy::cerealise(Cereal& cereal) {
    cereal.grain(mLeft);
    cereal.grain(mRight);
    cereal.grain(mThrust);
    cereal.grain(mWeapon);
    cereal.grain(mSpecial);
    cereal.grain(mSuper);
    cereal.grain(mStart);
}
