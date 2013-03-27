#include "CSpritePacker.hpp"
#include <string>

auto CSpritePacker::Pack(Sprites sprites) -> FrameBytes {
    FrameBytes data;
    for(const auto& sprite: sprites) {
        const std::string datum = "x: " + std::to_string(sprite->GetPos().GetX()) + " " +
                                  "y: " + std::to_string(sprite->GetPos().GetY()) + "\n";
        for(auto c: datum) {
            data.push_back(c);
        }
    }
    return data;
}
