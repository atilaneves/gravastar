#ifndef CSHIPS_H
#define CSHIPS_H


class CShip;
class CSpriteObj;
class CPilot;
#include "CVector2.hpp"
#include "CScreenPos.hpp"
#include <list>

typedef std::list<CShip*> ships_t;
typedef std::list<CShip*>::iterator shipPlace_t;


class CShips {

public:

  static shipPlace_t AddShip(CShip *ship);
  static CShip*      Find(const CScreenPos &pos, bool updated = true);
  static float       GetDistanceScaling(const CVector2& direction);
  static bool 	     HasShip(CShip *ship);
  static bool	     IsClearLine(const CShip &ship, int x, int y);
  static bool        IsAllElseInvulnerable(CShip& ship);
  static void        PushAll(const CVector2& collision,
			     float force, CSpriteObj* hitShip,
			     CPilot& pilot, float damage = 0);
  static void 	     RemoveAll();
  static void 	     RemoveShip(CShip *ship);
  static void        StartEffect(const CShip* ship, int effect,float duration);


private:

  static std::list<CShip*> sShips;


};


#endif
