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
  fileName = CDataFile::GetFileName(fileName);

  if(!CDataFile::FileExists(fileName))
    fileName = CDataFile::GetFileName("Explosions/shipExp.dat"); //default

  CDataFile expData(fileName);

  for(int i = 0; i < CExplosion::kNbFrames; ++i)
    mExplosionSprites.push_back(new CGravSprite(expData.GetData(i),
						team));

  std::string wavFileName = "Sounds/" + name + "Exp.wav";
  if(CDataFile::FileExists(CDataFile::GetFileName(wavFileName)))
    mSound.reset(new CSound(name + "Exp"));
  else
    mSound.reset(new CSound("shipExp"));
}
