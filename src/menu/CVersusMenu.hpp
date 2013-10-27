#ifndef CVERSUSMENU_H
#define CVERSUSMENU_H


class CSprite;
class CCycleLeaf;
class CCycleString;
class CCycleTeam;
class CTeam;
class CMeleeOptions;
class CGravMenu;
class CShipMenu;
#include "CPilotOptions.hpp"
#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
#include "CGravOptions.hpp"
#include <vector>


class CVersusMenu: public CStringMenu {

public:

    enum { kMaxNbPilots = 4 };

    CVersusMenu(const CSprite *cursorSprite, const CGravMenu &gravMenu);

    std::vector<CPilotOptions> GetPilotOptions(int nbPilots,
                                               const std::vector<CPilotInputOptions>& pilotInputOpts) const;


    CGravOptions       GetGravOptions()    const;
    CClientOptions     GetClientOptions()  const;
    CMeleeOptions      GetMeleeOptions()   const;
          std::string  GetMeleeType()      const;
          int          GetNbPilots()       const;
          int          GetNbShips()        const;
          int          GetNbShips(int p)   const;
          std::string  GetPilotName(int p) const;
    const CTeam&       GetPilotTeam(int p) const;
          std::string  GetPilotType(int p) const;
          std::string  GetShipType(int p, int s) const;
    const shipTypes_t& GetShipTypes(int p) const;
          float        GetPowerupRate() const;


private:

    const CGravMenu& mGravMenu;
    CMenuCursor mCursor;
    CCycleString *mMeleeType;
    CShipMenu *mShipMenu;
    CCycleLeaf *mNbHumans, *mNbBots, *mLimit, *mPowerupRate;
    std::vector<CCycleTeam*> mTeams;

            void CreateTeams();
            void CreateTypes();
            void KeepInBounds();
            void SetTypeString();
    virtual void Update(CRootMenu &rootMenu) override;

};


#endif
