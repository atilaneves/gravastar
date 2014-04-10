#include "CShipYard.hpp"
#include "CTeam.hpp"
#include "CShip.hpp"
#include "CShipFactory.hpp"
#include <stdio.h>
#include <stdlib.h>


CShipYard::CShipYard(CLevel &level,
                     const CClientOptions::AllPilotOptions& allPilotOptions):
    mLevel(level) {
    //builds blueprints for all ships/teams for all pilots

    for(const auto& pilotOptions: allPilotOptions) {
        const auto& team = pilotOptions.GetTeam();
        for(const auto& shipName: pilotOptions.GetShipNames()) {
            if(!HasBluePrint(shipName, team)) InsertBluePrint(shipName, team);
        }
    }
}


CShip* CShipYard::CreateShip(const std::string &shipName, const CTeam &team,
                             CPilot &pilot) const {
    //creates a ship, fetching the necessary blueprint
    auto& factory = CShipFactory::Instance();
    return factory.CreateObject(shipName, GetBluePrint(shipName, team),
                                pilot, mLevel);
}


bool CShipYard::HasBluePrint(const std::string &shipName,
                             const CTeam &team) const {
    const auto it = mMap.find(GetID(shipName, team));
    return it == mMap.end() ? false : true;
}


const CShipBluePrint& CShipYard::GetBluePrint(const std::string &shipName,
                                              const CTeam &team) const {

    const auto it = mMap.find(GetID(shipName, team));
    if(it != mMap.end()) return *(it->second); //all gd, return it

    fprintf(stderr, "ShipYard didn't have ship %s team %s!\n",
            shipName.c_str(), team.GetName().c_str()); //oops
    exit(1);
}


const std::string CShipYard::GetID(const std::string &shipName,
                                   const CTeam &team) const {
    return std::string(shipName + "," + team.GetName());
}


void CShipYard::InsertBluePrint(const std::string &shipName,
                                const CTeam &team) {

    auto* bluePrint = new CShipBluePrint(shipName, team, *this);
    const auto id = GetID(shipName, team); //use std::pair instead?

    bool success = mMap.insert(std::make_pair(id, bluePrint)).second;

    if(success) return;

    fprintf(stderr, "Yard insertion failed for id %s\n", id.c_str());
    exit(1);
}


CShipYard::~CShipYard() {
    for(const auto& pair: mMap) {
        delete pair.second;
    }
}
