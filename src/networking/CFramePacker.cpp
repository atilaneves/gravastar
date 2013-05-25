#include "CFramePacker.hpp"
#include "Cerealiser.hpp"
#include <limits>
#include <assert.h>
#include <chrono>
#include <stdint.h>


using std::chrono::duration_cast;


static void writePilots(Cerealiser& cereal, const CFramePacker::Pilots& pilots) {
    cereal.write<uint8_t>(pilots.size());
    for(const auto& pilot: pilots) {
        cereal.write<uint16_t>(pilot.position.GetX());
        cereal.write<uint16_t>(pilot.position.GetY());
        cereal.write(static_cast<int16_t>(pilot.velocity.GetX()));
        cereal.write(static_cast<int16_t>(pilot.velocity.GetY()));
        cereal.write<uint8_t>(pilot.team.GetHash());
        cereal.write<uint8_t>(pilot.isAlive);
        cereal.write<uint8_t>(pilot.hasSplitScreen);
    }
}


static void writeSprites(Cerealiser& cereal, const CFramePacker::Sprites& sprites) {
    cereal.write<uint16_t>(sprites.size());
    for(const auto& sprite: sprites) {
        assert(sprite.GetHash() <= std::numeric_limits<uint16_t>::max());
        cereal.write<uint16_t>(sprite.GetHash());
        cereal.write<uint16_t>(sprite.GetX());
        cereal.write<uint16_t>(sprite.GetY());
    }
}

auto CFramePacker::Pack(const Pilots& pilots, const Sprites& sprites) const -> FrameBytes {
    static const auto start = mClock.now();
    assert(sprites.size() <= std::numeric_limits<uint16_t>::max());
    const uint32_t milliseconds = duration_cast<std::chrono::milliseconds>(mClock.now() - start).count();
    assert(milliseconds <= std::numeric_limits<decltype(milliseconds)>::max());

    Cerealiser cereal;
    cereal << milliseconds;

    writePilots(cereal, pilots);
    writeSprites(cereal, sprites);

    return cereal.getBytes();
}
