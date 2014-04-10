#include "CShipMenuItem.hpp"
#include "CMenuIconShip.hpp"
#include "CDataFile.hpp"
#include "CUnderscoreRemover.hpp"
#include "deltadat.h"
#include "menudat.h"
#include <stdio.h>


static CDataFile* gDataFile;


CShipMenuItem::CShipMenuItem(const std::string &title,
			     const CVersusMenu &versus):
  CMenu(new CMenuIconShip(gDataFile = new CDataFile(GetFileName(title)),
			  GetIndex(title))),
  mVersus(versus), mDir("Ships") {
  
  SetNames(title, *gDataFile);
  delete gDataFile;
}


std::string CShipMenuItem::GetFileName(const std::string &title) {
  return title == "Random" ? "menu.dat" : "Ships/" + title + ".dat"; 
}


int CShipMenuItem::GetIndex(const std::string &title) {
  return title == "Random" ? QUESTION : BLUE_000;
}


void CShipMenuItem::SetNames(const std::string &title,
			     const CDataFile &dataFile) {
  
  char shipName[200], weaponName[200], specialName[200], superName[200];
  char quirks[200];

  if(title != "Random") {
    sscanf((char*)dataFile.GetData(NAMES),"%s %s %s %s %s",
	   shipName, weaponName, specialName, superName, quirks);
    mShipName    = CUnderscoreRemover::Remove(shipName);
    mWeaponName  = CUnderscoreRemover::Remove(weaponName);
    mSpecialName = CUnderscoreRemover::Remove(specialName);
    mSuperName   = CUnderscoreRemover::Remove(superName);
  }
  else {
    mShipName    = "Random";
    mWeaponName  = mSpecialName = mSuperName = "???";
  }
}

const std::string& CShipMenuItem::GetShipName() const { 
  if(mShipName != "Random") return mShipName;
  int shipIndex = rand() % mDir.GetNbEntries();
  return mDir.GetEntryNoExt(shipIndex);
}
