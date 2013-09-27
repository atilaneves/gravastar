#ifndef SCLIENTFRAME_H_
#define SCLIENTFRAME_H_

#include "CDisplayPilot.hpp"
#include "CLevelSprite.hpp"
#include "Cereal.hpp"
#include <vector>
#include <stdint.h>
#include <cassert>
#include <iostream>

struct SClientFrame {
    using Pilots  = std::vector<CDisplayPilot>;
    using Sprites = std::vector<CLevelSprite>;

    uint32_t milliseconds;
    Pilots pilots;
    Sprites sprites;
    void cerealise(Cereal& cereal) {
        cereal.grain(milliseconds);
        cereal.grain<uint8_t>(pilots);
        cereal.grain<uint16_t>(sprites);
    }
    void SetPilot(unsigned index) {
        for(unsigned i = 0; i < pilots.size(); ++i) {
            pilots[i].mHasSplitScreen = (i == index);
        }
    }
};


#endif // SCLIENTFRAME_H_
