#ifndef CTEAM_H
#define CTEAM_H

//a team of pilots working together, defined by a colour


#include <stdio.h>
#include <allegro.h>
#include <string>
#include <vector>
#include <utility>

class CTeam {

public:

  static CTeam sBlue, sRed, sGreen, sYellow, sWhite;

  bool operator==(const CTeam& team) const { return mName == team.mName; }
  bool operator!=(const CTeam& team) const { return mName != team.mName; }

  static const CTeam& FindByName(const std::string& name);
  static const CTeam& FromHash(uint8_t hash);
         int          GetDarkColour() const { return mColours[0]; }
         uint8_t      GetHash() const;
         int          GetMainColour() const { return mColours[6]; }
         int          GetSecondaryColour() const { return mColours[4]; }
  const  std::string& GetName() const { return mName; }
  static void         LoadColours();
         int          TransformColour(int colour) const;


private:

  enum { kNbColours = 14 };

  const std::string mName;
  const float mStart, mEnd;
  std::vector<int> mColours;

  CTeam(std::string name, float start, float end)
      : mName(std::move(name)), mStart(start), mEnd(end) {}

  static int   GetBlueIndex(int colour);
         void  LoadMyColours();
         FILE* OpenFile();

};


#endif
