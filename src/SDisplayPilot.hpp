#ifndef SDISPLAYPILOT_H
#define SDISPLAYPILOT_H

class CTeam;
class CPilotStats;
#include "CScreenPos.hpp"
#include "CVector2.hpp"

struct SDisplayPilot {
    //SDisplayPilot(CScreenPos p, CVector2 v, const CTeam& t
    const CScreenPos position;
    const CVector2 velocity;
    const CTeam& team;
    CPilotStats& stats;
    const bool isAlive;
    const bool hasSplitScreen;
};


#endif // SDISPLAYPILOT_H
