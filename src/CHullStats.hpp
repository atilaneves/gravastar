#ifndef CHULLSTATS_H
#define CHULLSTATS_H


class CCanvas;
class CTeam;


class CHullStats {

public:

    CHullStats(const CTeam& team, float hull, float maxHull);

    void Draw(CCanvas &canvas) const;


private:

    const CTeam& mTeam;
    const float mHull;
    const float mMaxHull;

};


#endif
