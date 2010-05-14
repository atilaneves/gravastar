#ifndef CPILOT_H
#define CPILOT_H


#include "CPilotOptions.hpp"
#include "CShip.hpp"
#include "CPilotInput.hpp"
#include "CPilotStats.hpp"
#include <string>
#include <memory>
class CShipYard;
class CLevel;
class CBitmap;
class CMeleeScore;
class CGravSprite;
class CShipStatSprite;


class CPilot {

public:

  CPilot(const CPilotOptions &options, const CShipYard &shipYard,
	 CMeleeScore& meleeScore);
  virtual ~CPilot() { }

          void AddDamage(float amount, CPilot &pilot);
          void AddFrag(CPilot &pilot);
  virtual void CheckControls() = 0;
          void DrawStats(CBitmap& b, int x, int y) { mStats.Draw(b, x, y); }
          void GameOver() { mNbShips = 0; }
          int  GetIndex()   const { return mIndex; }
  const CPilotInput& GetInput() const { return *mInput; }
  const std::string& GetName() const;
          int  GetNbShips() const { return mNbShips; }
          int  GetScore()   const;
          CShip& GetShip() const { return *mShip; }
          int GetShipIndex() const { return mOptions.GetNbShips() - mNbShips; }
  const std::string& GetShipName(int i=0) const { return
						    mOptions.GetShipName(i); }
  const CShipStatSprite& GetShipStatSprite(int index=0) const;
  const CTeam& GetTeam()    const { return mOptions.GetTeam(); }
  virtual bool HasSplitScreen() const = 0;
          bool IsAlive() const;
  virtual void NextShip();
  static  void ResetIndex() { sIndex = 0; }



private:

  static int sIndex;

  int          mIndex;
  int          mNbShips;
  int          mNbFrags;
  float        mSuperGauge;
  CShip*       mShip;
  CPilotStats  mStats;

  CShip* SpawnShip();


protected:

  std::auto_ptr<CPilotInput> mInput;
  const CPilotOptions& mOptions;
  const CShipYard&     mShipYard;
  CMeleeScore&         mMeleeScore;

  bool IsSurvival() const;

};


#endif
