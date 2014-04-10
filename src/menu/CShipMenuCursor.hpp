#ifndef CSHIPMENUCURSOR_H
#define CSHIPMENUCURSOR_H


#include "CMenuCursor.hpp"
#include "CGravSprite.hpp"
#include "CShipMenuInfo.hpp"
#include <memory>
class CTeam;


class CShipMenuCursor: public CMenuCursor {

public:


    CShipMenuCursor(CMenu &menu, int index, const CTeam& team,
                    const CVersusMenu& versus,
                    std::vector<std::string>& shipTypes);
    virtual ~CShipMenuCursor() { }

    virtual void DrawSprite(CCanvas &canvas);
    int GetIndex() const { return mIndex; }
    virtual void OnSelect();


private:

    int mIndex;
    const CVersusMenu &mVersus;
    std::vector<std::string>& mShipTypes;
    std::auto_ptr<CGravSprite> mGravSprite;
    CShipMenuInfo mInfo;

};

#endif
