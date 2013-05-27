#ifndef CDISPLAYPILOT_H
#define CDISPLAYPILOT_H

class CPilotStats;
class Cereal;
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CTeam.hpp"
#include <stdint.h>

class CDisplayPilot {

    friend class SClientFrame;

public:

    CDisplayPilot():mStats(*static_cast<CPilotStats*>(nullptr)) { }
    CDisplayPilot(const CScreenPos& pos, const CVector2& vel, const CTeam& team,
                  CPilotStats& stats, bool isAlive, bool hasSplitScreen):
        mPosition(pos.GetX(), pos.GetY()), mVelocity(vel.GetX(), vel.GetY()),
        mTeam(team.GetHash()), mStats(stats), mIsAlive(isAlive), mHasSplitScreen(hasSplitScreen) {
    }

    CScreenPos GetPosition() const { return { mPosition.x, mPosition.y }; }
    CVector2 GetVelocity() const {
        return { static_cast<float>(mVelocity.x), static_cast<float>(mVelocity.y) };
    }
    const CTeam& GetTeam() const {return CTeam::FromHash(mTeam); }
    CPilotStats& GetStats() { return mStats; }
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

    Vector<uint16_t> mPosition;
    Vector<int16_t> mVelocity;
    uint8_t mTeam;
    CPilotStats& mStats;
    bool mIsAlive;
    bool mHasSplitScreen;

};


#endif // CDISPLAYPILOT_H
