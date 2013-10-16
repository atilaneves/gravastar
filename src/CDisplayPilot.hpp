#ifndef CDISPLAYPILOT_H
#define CDISPLAYPILOT_H

class Cereal;
class CBitmap;
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CTeam.hpp"
#include "CPilotStats.hpp"
#include <memory>
#include <stdint.h>

class CDisplayPilot {

    friend class SClientFrame;

public:

    CDisplayPilot() = default;
    CDisplayPilot(uint8_t index, const CScreenPos& pos, const CVector2& vel,
                  const CTeam& team,
                  uint8_t score, CPilotStats* stats, bool isAlive,
                  bool hasSplitScreen);

    CScreenPos GetPosition() const { return { mPosition.x, mPosition.y }; }
    CVector2 GetVelocity() const {
        return { static_cast<float>(mVelocity.x), static_cast<float>(mVelocity.y) };
    }
    const CTeam& GetTeam() const {return CTeam::FromHash(mTeam); }
    void DrawStats(CBitmap& bmp, int x, int y);
    uint8_t GetScore() const { return mScore; }
    bool IsAlive() const { return mIsAlive; }
    bool HasSplitScreen() const { return mHasSplitScreen; }
    void cerealise(Cereal& cereal);

private:
    template<typename T>
    struct Vector {
        Vector():x(), y() {}
        Vector(T _x, T _y):x(_x), y(_y) { }
        T x, y;
    };

    uint8_t mIndex;
    Vector<uint16_t> mPosition;
    Vector<int16_t> mVelocity;
    uint8_t mTeam;
    uint8_t mScore;
    std::shared_ptr<CPilotStats> mStats;
    bool mIsAlive;
    bool mHasSplitScreen;
};


#endif // CDISPLAYPILOT_H
