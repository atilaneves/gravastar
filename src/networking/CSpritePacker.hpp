#ifndef CSPRITE_PACKER_HPP_
#define CSPRITE_PACKER_HPP_

#include "CSpriteObjs.hpp"
#include <vector>
#include <chrono>

class CSpritePacker {

public:

    using FrameBytes = CSpriteObjs::FrameBytes;
    using Sprites = CSpriteObjs::objs_t;

    FrameBytes Pack(const Sprites& sprites) const;

private:

    std::chrono::high_resolution_clock mClock;
};


#endif
