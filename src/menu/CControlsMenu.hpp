#ifndef CCONTROLSMENU_H
#define CCONTROLSMENU_H


class CCycleStringEnter;
class CVersusMenu;
class CClientOptions;
class CRedefineMenu;
class CPilotInputOptions;
#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
#include <vector>


class CControlsMenu: public CStringMenu {

public:

    enum { kMaxNbPilots = 4 };

    CControlsMenu(const CVersusMenu &versus, const CClientOptions& options);
    virtual ~CControlsMenu() { }

    virtual void Draw(CCanvas &canvas) override;
             int   GetJoyIndex(int i) const;
             std::vector<CPilotInputOptions> GetPilotInputOptions(int nbPilots) const;


private:

    CMenuCursor mCursor;
    const CVersusMenu& mVersus;
    std::vector<CCycleStringEnter*> mControlTypes;
    std::vector<CRedefineMenu*> mRedefines;

    virtual int GetSubMenuX(int column) const override;
};



#endif
