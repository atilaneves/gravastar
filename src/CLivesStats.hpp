#ifndef CSTATSLIVES_H
#define CSTATSLIVES_H


class CCanvas;
class CTeam;
class CShipStatSprite;


class CLivesStats {

public:

    CLivesStats(const CTeam& team,
                const CShipStatSprite& statSprite, int score):
        mTeam(team), mStatSprite(statSprite), mScore(score) { }
    void Draw(CCanvas& canvas) const;

private:

    const CTeam& mTeam;
    const CShipStatSprite& mStatSprite;
    const int mScore;
};


#endif
