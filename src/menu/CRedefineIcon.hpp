#ifndef CREDEFINEICON_H
#define CREDEFINEICON_H


#include "CMenuIcon.hpp"
#include "CFont.hpp"
class CVersusMenu;
class CRedefineMenu;


class CRedefineIcon: public CMenuIcon {

public:

    enum { kWidth = 120 };

    CRedefineIcon(CRedefineMenu &redefine, const CVersusMenu &versus,
                  int pilotNb);
    virtual ~CRedefineIcon() { }


    virtual void Draw(CCanvas &canvas, int x, int y, bool highlight) const override;
    virtual int  GetHeight() const override;
    virtual int  GetWidth() const override;


private:

    CRedefineMenu &mRedefine;
    const CVersusMenu &mVersus;
    const int mPilotNb;
    CFont mFont, mPilotFont;

    void DrawButtons(CCanvas &canvas, int x, int y, bool highlight) const;
    void DrawRectangles(CCanvas &canvas, int x, int y) const;


};


#endif
