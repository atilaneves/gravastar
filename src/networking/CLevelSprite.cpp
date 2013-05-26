#include "CLevelSprite.hpp"
#include "Cereal.hpp"
#include <limits>
#include <cassert>

void CLevelSprite::cerealise(Cereal& cereal) {
    assert(mHash <= std::numeric_limits<uint16_t>::max());
    cereal.grain(mHash);
    cereal.grain(mX);
    cereal.grain(mY);
}
