#ifndef CDISPLAYPILOT_H
#define CDISPLAYPILOT_H

class Cereal;
class CBitmap;
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CTeam.hpp"
#include "CPilotStats.hpp"
#include <stdint.h>

class CDisplayPilot {

    friend class SClientFrame;

public:

    CDisplayPilot() {}
    CDisplayPilot(uint8_t index, const CScreenPos& pos, const CVector2& vel,
                  uint8_t teamHash,
                  uint8_t score, CPilotStats stats, bool isAlive,
                  bool hasSplitScreen);

    CScreenPos GetPosition() const { return { mPosition.x, mPosition.y }; }
    CVector2 GetVelocity() const {
        return { static_cast<float>(mVelocity.x), static_cast<float>(mVelocity.y) };
    }
    const CTeam& GetTeam() const {return CTeam::FromHash(mTeamHash); }
    void DrawStats(CCanvas& canvas) const;
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
    uint8_t mTeamHash;
    uint8_t mScore;
    CPilotStats mStats;
    bool mIsAlive;
    bool mHasSplitScreen;
};


#endif // CDISPLAYPILOT_H
