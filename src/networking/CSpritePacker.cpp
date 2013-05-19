#include "CSpritePacker.hpp"
#include <limits>
#include <assert.h>
#include <chrono>
#include <stdint.h>
#include <iostream> //DELETE

using std::chrono::duration_cast;


static void writeUInt16(CSpritePacker::FrameBytes& data, uint16_t datum) {
    data.push_back(datum >> 8);
    data.push_back(datum & 0xff);
}

static void writeUInt32(CSpritePacker::FrameBytes& data, uint32_t datum) {
    data.push_back(datum >> 24);
    data.push_back((datum >> 16) & 0xff);
    data.push_back((datum >> 8) & 0xff);
    data.push_back(datum & 0xff);

}


auto CSpritePacker::Pack(const Sprites& sprites) const -> FrameBytes {
    static const auto start = mClock.now();
    assert(sprites.size() <= std::numeric_limits<uint16_t>::max());
    const auto milliseconds = duration_cast<std::chrono::milliseconds>(mClock.now() - start).count();
    assert(milliseconds <= std::numeric_limits<uint32_t>::max());

    FrameBytes data;
    writeUInt32(data, milliseconds);
    writeUInt16(data, sprites.size());

    for(const auto& sprite: sprites) {
        assert(sprite.GetHash() <= std::numeric_limits<uint16_t>::max());
        std::cout << "Packing " << sprite.GetHash() << ", x: " <<
            sprite.GetX() << ", y: " << sprite.GetY() << std::endl; //DELETE
        writeUInt16(data, sprite.GetHash());
        writeUInt16(data, sprite.GetX());
        writeUInt16(data, sprite.GetY());
    }

    //DELETE
    std::cout << "0x";
    for(const auto& byte: data) {
        printf("%02x", (unsigned)byte);
    }
    std::cout << std::endl;

    return data;
}
