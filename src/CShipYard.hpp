#ifndef CSHIPYARD_H
#define CSHIPYARD_H


//a place to get ship blueprints, ships are loaded here at the start of
//a melee, then whenever a new ship object is created it copies the gfx, etc
//from the blueprint found in the shipyard

#include <map>
#include <string>
#include "CShipBluePrint.hpp"
#include "CSound.hpp"
#include "CShipSounds.hpp"


class CTeam;
class CGravOptions;
class CShip;
class CPilot;
class CLevel;


class CShipYard {

public:

  enum { kNbTeams = 4 };

  CShipYard(CLevel &level, const CGravOptions &options);
  ~CShipYard();

  CShip* CreateShip(const std::string &shipName, const CTeam &team,
		    CPilot &pilot) const;

  const CShipBluePrint& GetBluePrint(const std::string &shipName,
				     const CTeam &team) const;
  const CShipSounds& GetSounds() const { return mSounds; }


private:

  typedef std::map<std::string, CShipBluePrint*> BluePrintMap_t;
  typedef BluePrintMap_t::const_iterator ConstBluePrintIterator_t;
  typedef BluePrintMap_t::iterator BluePrintIterator_t;

  BluePrintMap_t mMap;
  CLevel&        mLevel;
  CShipSounds    mSounds;

  const std::string GetID(const std::string &shipName,
			  const CTeam &team) const;
  bool              HasBluePrint(const std::string &shipName,
				 const CTeam &team) const;
  void              InsertBluePrint(const std::string &shipName,
				    const CTeam &team);

};


#endif
