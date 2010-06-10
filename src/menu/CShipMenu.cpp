#include "CShipMenu.hpp"
#include "CShipMenuItem.hpp"
#include "CShipMenuCursor.hpp"
#include "CVersusMenu.hpp"
#include "CDirectory.hpp"
#include "CResolution.hpp"
#include "CMenuInputPilot.hpp"
#include "CMenuInputBot.hpp"
#include "CGravMenu.hpp"
#include <algorithm>
#include <assert.h>


CShipMenu::CShipMenu(const CGravMenu &gravMenu, const CVersusMenu &versus):
  CStringMenu("Select Ships"),
  mSound("selectShip"), mGravMenu(gravMenu), mVersus(versus),
  mLevelMenu(gravMenu), mCursorsPos(4, CScreenPos(0, 0)) {

  mShipTypes.resize(kMaxNbPilots);
  CDirectory dir("Ships");

  mShipItems.push_back(new CShipMenuItem("Random", versus));

  for(int i = 0; i < dir.GetNbEntries(); i++)
    mShipItems.push_back(new CShipMenuItem(dir.GetEntryNoExt(i), versus));

  for(unsigned int i = 0; i < mShipItems.size(); i++)
    AddMenu(mShipItems[i], i % 4); //add to a column
}


CShipMenu::~CShipMenu() {
  Clear();
}


void CShipMenu::Clear() {
  for(unsigned int i = 0; i < mCursors.size(); i++) delete mCursors[i];
  mCursors.clear();
  for(int i = 0; i < kMaxNbPilots; i++) mShipTypes[i].clear();
}


void CShipMenu::CreateCursors() {
  Clear();

  int nbHumans = 0;
  for(int i = 0; i < mVersus.GetNbPilots(); i++)
    if(mVersus.GetPilotType(i) == "Human")
      nbHumans++;

  CMenuInputPilot *firstMenuInputPilot = NULL; //might be used below

  //when calling new, cursor gets added to mCursors automatically
  for(int i = 0; i < mVersus.GetNbPilots(); i++) {
    new CShipMenuCursor(*this, i, mVersus.GetPilotTeam(i),
			mVersus, mShipTypes[i]);
    mCursors[i]->SetRowsCols();
    mCursors[i]->SetCol(mCursorsPos[i].GetX());
    mCursors[i]->SetRow(mCursorsPos[i].GetY());

    if(nbHumans > 1) { //more than 1 human, special menu controls
      if(i < nbHumans) {
	CGravOptions options = mGravMenu.GetGravOptions();
	CMenuInputPilot *input = new CMenuInputPilot(i, options);
	mCursors[i]->AdoptInput(input);
	if(i == 0) firstMenuInputPilot = input;
      }
      else {
	assert(firstMenuInputPilot != NULL);
	mCursors[i]->AdoptInput(new CMenuInputBot(*firstMenuInputPilot));
      }
    }
  }
}


void CShipMenu::Run(CRootMenu &rootMenu) {
  mSound.PlayCentre();
  CreateCursors();
  while(RunStep(rootMenu)) {
    RemoveDormantCursors();
    if(IsAllDone()) {
      mLevelMenu.Run(rootMenu);
      CreateCursors();
    }
  }
  Clear();
}


void CShipMenu::RemoveDormantCursors() {
  std::vector<CMenuCursor*> dormant;

  for(unsigned int i = 0; i < mCursors.size(); i++) {
    CShipMenuCursor *cursor = (CShipMenuCursor*)mCursors[i];
    int index = cursor->GetIndex();
    if((int)mShipTypes[index].size() == mVersus.GetNbShips()) {
      dormant.push_back(mCursors[i]);
      mCursorsPos[index].SetX(mCursors[i]->GetCol());
      mCursorsPos[index].SetY(mCursors[i]->GetRow());
    }
  }

  for(unsigned int i = 0; i < dormant.size(); i++) {
    cursorPlace_t where = find(mCursors.begin(), mCursors.end(),
			       dormant[i]);
    mCursors.erase(where);
    delete dormant[i];
  }
}


bool CShipMenu::IsAllDone() const{
  bool allDone = true;
  for(int i = 0; i < mVersus.GetNbPilots(); i++) {
    if((int)mShipTypes[i].size() != mVersus.GetNbShips())
      allDone = false;
  }
  return allDone;
}


int CShipMenu::GetSubMenuX(int column) const {
 int width = 70;
 return CResolution::GetWidth() / 2 - 2*width + 30 + 70*column;
}


int CShipMenu::GetSubMenuY(int row) const {
 return CResolution::GetHeight() / 4 + 70*row;
}


std::string CShipMenu::GetShipType(int p, int s) const {
  return mShipTypes[p][s];
}
