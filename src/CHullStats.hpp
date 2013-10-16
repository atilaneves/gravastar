#ifndef CHULLSTATS_H
#define CHULLSTATS_H


class CCanvas;
class CTeam;


class CHullStats {

public:

    CHullStats(CCanvas &canvas, const CTeam& team, float hull, float maxHull);

    void Draw();


private:

    CCanvas& mCanvas;
    const CTeam& mTeam;
    const float mHull;
    const float mMaxHull;

};


#endif
