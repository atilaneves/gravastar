#include "CMoverBluePrint.hpp"
#include "CDataFile.hpp"
#include "CNose.hpp"
#include "CGravSprite.hpp"
#include <math.h>


CMoverBluePrint::CMoverBluePrint(int startPos,
                                 const CDataFile &dataFile,
                                 const CTeam &team, int colour) {

  const int kNbInQuad = CNose::kNbNoses/4; //# of sprites in one quadrant
 
  for(int n = 0; n < CNose::kNbNoses; ++n) {
    
    void *sprite = dataFile.GetData(startPos + n%kNbInQuad);
    float angle  =(M_PI/2)*(n/kNbInQuad);  //how much do we turn?
    const float scale = 1;
    
    mSprites.push_back(new CGravSprite(sprite, team, angle, scale,
                                       colour)); //rotate
  }
}
