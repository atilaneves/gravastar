#ifndef CSHIPMENUINFO_H
#define CSHIPMENUINFO_H


#include "CDirectory.hpp"
#include "CFont.hpp"
#include "CCanvas.hpp"
#include "CTimeCounter.hpp"
#include <map>
#include <string>
class CTeam;
class CVersusMenu;
class CCanvas;
class CShipStatSprite;
class CShipMenuItem;


class CShipMenuInfo {

public:

  CShipMenuInfo(int index, const CTeam &team, const CVersusMenu& versus);
  ~CShipMenuInfo();

  void Draw(CCanvas &canvas, const CShipMenuItem &item);


private:

  enum { kRectWidth=160,kRectHeight=120,kLineWidth=7,kRadius=30,kDeltaY=40 };

  typedef std::map<std::string, CCanvas*>::iterator spritePlace_t;
  typedef std::map<std::string, CShipStatSprite*>::iterator statPlace_t;

  int mIndex;
  const CTeam& mTeam;
  CDirectory mDirectory;
  CFont mSmallFont, mBigFont;
  CCanvas mCanvas;
  const CVersusMenu& mVersus;
  CTimeCounter mTimeCounter;
  std::map<std::string, CCanvas*> mSprites;
  std::map<std::string, CShipStatSprite*> mStatSprites;
 

  void AddSprite(const std::string& name, CCanvas *canvas);
  void DrawGeometry();
  void DrawSprite(const CShipMenuItem &shipItem);
  void DrawSquad(const CShipMenuItem& shipItem);
  void Write(const CShipMenuItem &shipItem);

};

#endif
