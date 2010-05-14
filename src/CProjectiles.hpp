#ifndef CPROJECTILES_H
#define CPROJECTILES_H


class CProjectile;
class CSpriteObj;
class CPilot;
class CShip;
#include "CVector2.hpp"
#include "CScreenPos.hpp"
#include <list>

typedef std::list<CProjectile*> projs_t;
typedef std::list<CProjectile*>::iterator projPlace_t;


class CProjectiles {

public:

  static projPlace_t AddProjectile(CProjectile *projectile);
  static void        DamageAll(const CVector2& collision,
			       float damage);
  static bool        HasTowards(const CShip& ship);
  static void 	     RemoveAll();
  static void 	     RemoveProjectile(CProjectile *projectile);


private:

  static projs_t sProjectiles;

  static float GetMaxAngle(int width, float radius);

};


#endif
