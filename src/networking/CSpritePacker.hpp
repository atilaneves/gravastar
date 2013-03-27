#ifndef CSPRITE_PACKER_HPP_
#define CSPRITE_PACKER_HPP_

#include "CSpriteObjs.hpp"
#include <vector>


class CSpritePacker {

public:

    using FrameBytes = CSpriteObjs::FrameBytes;
    using Sprites = const CSpriteObjs::objs_t&;

    FrameBytes Pack(Sprites sprites);
};


#endif
