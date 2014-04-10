#ifndef CINDLOADER_H
#define CINDLOADER_H


#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include <deque>
#include <vector>
#include <string>
class CCanvas;


typedef std::deque<CScreenPos> IndsPos_t;
typedef std::vector<void*>     IndsBmp_t;

class CIndLoader {

public:

  CIndLoader(std::string &fileName, const CCanvas &canvas, IndsBmp_t indBmps,
	     void* baseBmp);

  CVector2 GetBasePos(int i) const { return Pos2Vector(mBasesPos[i]); }
  CVector2 GetIndPos(int i)  const { return Pos2Vector(mIndsPos[i]);  }
  int      GetNbBases()      const { return mBasesPos.size();         }


private:

        std::string mFileName;
  const CCanvas&    mCanvas;
        IndsPos_t   mIndsPos, mBasesPos;

  IndsPos_t  FindIndsPos(IndsBmp_t bmps);
  bool       LoadCoords();
  CScreenPos LoadPos(FILE *fp);
  CVector2   Pos2Vector(const CScreenPos& pos) const {
    return CVector2(pos.GetX(), pos.GetY()); }
  void       SaveCoords();

};


#endif
