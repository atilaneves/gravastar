#include "CDisplayPilot.hpp"
#include "Cereal.hpp"


void CDisplayPilot::cerealise(Cereal& cereal) {
    cereal.grain(mPosition.x);
    cereal.grain(mPosition.y);
    cereal.grain(mVelocity.x);
    cereal.grain(mVelocity.y);
    cereal.grain(mTeam);
    cereal.grain(mIsAlive);
}
