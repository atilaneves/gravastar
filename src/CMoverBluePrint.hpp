#ifndef CMOVERBLUEPRINT_H
#define CMOVERBLUEPRINT_H


#include "CSpriteVector.hpp"
class CDataFile;
class CTeam;


class CMoverBluePrint {

public:

  CMoverBluePrint(int startPos, const CDataFile &dataFile,
		  const CTeam &team, int colour = -1);

  const CSpriteVector& GetSprites() const { return mSprites; }


private:

 CSpriteVector mSprites;

};


#endif
