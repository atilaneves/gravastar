#ifndef CHULLSTATS_H
#define CHULLSTATS_H


class CPilot;
class CCanvas;


class CHullStats {

public:

  CHullStats(const CPilot &pilot, CCanvas &canvas);

  void Draw();


private:

  const CPilot& mPilot;
  CCanvas&      mCanvas;

};


#endif
