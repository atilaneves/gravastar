#ifndef CSTATSLIVES_H
#define CSTATSLIVES_H


class CCanvas;
class CTeam;
class CShipStatSprite;


class CLivesStats {

public:

    CLivesStats(CCanvas& canvas, const CTeam& team,
                const CShipStatSprite& statSprite, int score):
        mCanvas(canvas), mTeam(team), mStatSprite(statSprite), mScore(score) { }
    void Draw();

private:

    CCanvas& mCanvas;
    const CTeam& mTeam;
    const CShipStatSprite& mStatSprite;
    const int mScore;
};


#endif
