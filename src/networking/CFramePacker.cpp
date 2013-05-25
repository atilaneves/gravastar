#include "CFramePacker.hpp"
#include <limits>
#include <assert.h>
#include <chrono>
#include <stdint.h>
#include <iostream>


using std::chrono::duration_cast;

static void writeUInt8(CFramePacker::FrameBytes& data, uint8_t datum) {
    data.push_back(datum);
}

static void writeUInt16(CFramePacker::FrameBytes& data, uint16_t datum) {
    data.push_back(datum >> 8);
    data.push_back(datum & 0xff);
}

static void writeInt16(CFramePacker::FrameBytes& data, int16_t datum) {
    const auto ptr = reinterpret_cast<const uint16_t*>(&datum);
    data.push_back(*ptr >> 8);
    data.push_back(*ptr & 0xff);
}


static void writeUInt32(CFramePacker::FrameBytes& data, uint32_t datum) {
    data.push_back(datum >> 24);
    data.push_back((datum >> 16) & 0xff);
    data.push_back((datum >> 8) & 0xff);
    data.push_back(datum & 0xff);

}

static void writePilots(CFramePacker::FrameBytes& data, const CFramePacker::Pilots& pilots) {
    writeUInt8(data, pilots.size());
    for(const auto& pilot: pilots) {
        std::cout << "Server: " << pilot.position.GetX() << "," << pilot.position.GetY() <<
            "; " << pilot.velocity.GetX() << "," << pilot.velocity.GetY() <<
            "; " << pilot.team.GetName() << "; " << pilot.isAlive << " " << pilot.hasSplitScreen <<
            std::endl;
        writeUInt16(data, pilot.position.GetX());
        writeUInt16(data, pilot.position.GetY());
        writeInt16(data, static_cast<int16_t>(pilot.velocity.GetX()));
        writeInt16(data, static_cast<int16_t>(pilot.velocity.GetY()));
        writeUInt8(data, pilot.team.GetHash());
        writeUInt8(data, pilot.isAlive);
        writeUInt8(data, pilot.hasSplitScreen);
    }
}


static void writeSprites(CFramePacker::FrameBytes& data, const CFramePacker::Sprites& sprites) {
    writeUInt16(data, sprites.size());
    for(const auto& sprite: sprites) {
        assert(sprite.GetHash() <= std::numeric_limits<uint16_t>::max());
        writeUInt16(data, sprite.GetHash());
        writeUInt16(data, sprite.GetX());
        writeUInt16(data, sprite.GetY());
    }
}

auto CFramePacker::Pack(const Pilots& pilots, const Sprites& sprites) const -> FrameBytes {
    static const auto start = mClock.now();
    assert(sprites.size() <= std::numeric_limits<uint16_t>::max());
    const auto milliseconds = duration_cast<std::chrono::milliseconds>(mClock.now() - start).count();
    assert(milliseconds <= std::numeric_limits<uint32_t>::max());

    FrameBytes data;
    writeUInt32(data, milliseconds);

    writePilots(data, pilots);
    writeSprites(data, sprites);

    return data;
}
