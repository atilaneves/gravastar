#ifndef CPILOT_SCORE_H
#define CPILOT_SCORE_H


class CFont;
class CCanvas;
#include <string>

class CPilotScore {

public:

 CPilotScore(int index);

 void Draw(const CFont &font, CCanvas &canvas,int x,int y) const;
 int  GetScore() const;
 bool operator>(const CPilotScore &pilotScore) const;


private:

 int  mIndex;

};

#endif
