#ifndef CSTATSLIVES_H
#define CSTATSLIVES_H


class CPilot;
class CCanvas;
class CShipStatSprite;


class CLivesStats {

public:

  CLivesStats(const CPilot& pilot, CCanvas& canvas):
    mPilot(pilot),mCanvas(canvas) { }
  void Draw();
  void SetStatSprite(const CShipStatSprite* sprite) { mStatSprite = sprite; }


private:

  const CPilot&          mPilot;
        CCanvas&         mCanvas;
  const CShipStatSprite* mStatSprite;

};


#endif
