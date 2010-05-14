#ifndef CFOLLOW_FACTORY_H
#define CFOLLOW_FACTORY_H


#include "CFactory.hpp"
#include "CVector2.hpp"
#include "CFollower.hpp"
#include <string>
class CProjBluePrint;
class CShip;
class CSound;
class CSpriteVector;


typedef CFollower* (*CreateFollowCB)(const CSpriteVector&, CLevel&,
				     CMoverObj&, CSound*,  const CVector2&);


typedef CFactory<CFollower, std::string, CreateFollowCB,
		 const CSpriteVector&, CLevel&, CMoverObj&, CSound*,
		 const CVector2&> CFollowFactory;


#define REG_FOLLOW(pname, cname) static CFollower* CreateFollow(\
 const CSpriteVector& sp, CLevel& lv, CMoverObj& mv, CSound* sn=0,\
 const CVector2 &of=CVector2(0, 0)) \
 { return new cname(sp, lv, mv, sn, of); } \
 static const bool regFollow =\
 CFollowFactory::Instance().Register(pname, CreateFollow);

#define REG_EXTRA_FOLLOW(pname, cname) static CFollower* CreateExtraFollow(\
 const CSpriteVector& sp, CLevel& lv, CMoverObj& mv, CSound* sn=0,\
 const CVector2 &of=CVector2(0, 0)) \
 { return new cname(sp, lv, mv, sn, of); } \
 static const bool regExtraFollow =\
 CFollowFactory::Instance().Register(pname, CreateExtraFollow);



#endif
