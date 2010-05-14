#include "CExplosiveBluePrint.hpp"
#include "CDataFile.hpp"
#include "CGravSprite.hpp"
#include "CExplosion.hpp"


CExplosiveBluePrint::CExplosiveBluePrint(int startPos,
					 const std::string &name,
					 const CDataFile &dataFile,
					 const CTeam &team):
  mMoverBluePrint(startPos, dataFile, team) {


  std::string fileName = "Explosions/" + name + "Exp.dat";

  if(!CDataFile::FileExists(fileName))
    fileName = "Explosions/shipExp.dat";

  CDataFile expData(fileName);

  for(int i = 0; i < CExplosion::kNbFrames; ++i)
    mExplosionSprites.push_back(new CGravSprite(expData.GetData(i),
						team));

  if(CDataFile::FileExists("Sounds/" + name + "Exp.wav"))
    mSound.reset(new CSound(name + "Exp"));
  else
    mSound.reset(new CSound("shipExp"));
}
