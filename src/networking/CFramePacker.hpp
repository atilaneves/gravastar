#ifndef CFRAME_PACKER_HPP_
#define CFRAME_PACKER_HPP_

#include "CSpriteObjs.hpp"
#include <vector>
#include <chrono>

class CFramePacker {

public:

    using FrameBytes = CSpriteObjs::FrameBytes;
    using Sprites = CSpriteObjs::SpritePositions;
    using Pilots = CSpriteObjs::Pilots;

    FrameBytes Pack(const Pilots& pilots, const Sprites& sprites) const;

private:

    std::chrono::high_resolution_clock mClock;
};


#endif
