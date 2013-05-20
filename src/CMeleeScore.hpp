#ifndef CMELEE_SCORE_H
#define CMELEE_SCORE_H


#include "CPilotScore.hpp"
#include "CFont.hpp"
#include <vector>
#include <string>
#include <map>
class CTeam;
class CPilot;
class CCanvas;
class CFont;
class CSound;
class CPilotInput;
class CSong;

typedef std::map<std::string, CSound*>::iterator soundPlace_t;


class CMeleeScore {

public:

    enum { kNbColours=4 };

    CMeleeScore(CCanvas &canvas, const std::string& meleeType,
                CSong& song);
    ~CMeleeScore();

    void Draw(int winner, const std::string& title,
              const CPilotInput &input);
    const std::string& GetMeleeType() const { return mMeleeType; }
    void PlaySound(const CTeam& team);


private:

    CCanvas &mCanvas;
    CSong &mSong;
    std::string mMeleeType;
    CFont mFont;
    std::map<std::string, CSound*> mSounds;

    void DrawGeometry(int x, int y, int col) const;
    void End(const CPilotInput &input) const;
    std::vector<CPilotScore> GetScores() const;
};


#endif
