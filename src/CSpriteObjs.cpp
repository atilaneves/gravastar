#include "CSpriteObjs.hpp"
#include "CSpriteObj.hpp"
#include "CShips.hpp"
#include "CFlicker.hpp"
#include "debug.hpp"
#include <typeinfo>
#include <algorithm>
#include <vector>
#include "CShip.hpp"


CSpriteObjs::objs_t CSpriteObjs::sObjs;


void CSpriteObjs::Update(float dt) {
  
  for(objPlace_t o = sObjs.begin(); o != sObjs.end(); ++o) {
    //DEBUG("Update  obj %p of type %s\n", *o, typeid(**o).name());
    (*o)->Update(dt);
    if((*o)->IsActive()) DrawObj(*o);
  }
  
  std::vector<CSpriteObj*> toDelete; //inactive sprite objs
  
  for(objPlace_t o = sObjs.begin(); o != sObjs.end(); ++o) 
    if(!(*o)->IsActive()) toDelete.push_back(*o); //find all at same time
      
  for(unsigned int i = 0; i < toDelete.size(); i++)
    DeleteObj(toDelete[i]); //safe to delete all of them now
}


void CSpriteObjs::Erase() {
  for(objPlace_t o = sObjs.begin(); o!=sObjs.end(); ++o) EraseObj(*o);
}


void CSpriteObjs::AddObj(CSpriteObj *obj, bool back) {
  DEBUG("Adding   obj %p of type %s, total will be %d\n",
	obj, typeid(*obj).name(), sObjs.size() + 1);
  if(back) sObjs.push_back(obj);
  else     sObjs.push_front(obj);
}


void CSpriteObjs::DeleteObj(CSpriteObj *obj) {
  DEBUG("Deleting obj %p of type %s, total will be %d\n",
		    obj, typeid(*obj).name(), sObjs.size() - 1);
  sObjs.remove(obj);
  if(obj->IsUpdated()) obj->Erase();
  delete obj;
}


void CSpriteObjs::RemoveObj(CSpriteObj *obj) {
  DEBUG("Removing obj %p of type %s, total will be %d\n",
		    obj, typeid(*obj).name(), sObjs.size() - 1);
  objPlace_t where = find(sObjs.begin(), sObjs.end(), obj);
  if(where != sObjs.end()) sObjs.erase(where);
}


void CSpriteObjs::DeleteAll() {
  for(objPlace_t o = sObjs.begin(); o!=sObjs.end(); ++o) {
    DEBUG("(all) deleting obj %p of type %s\n", *o,typeid(**o).name());
    delete *o;
  }
  sObjs.clear();
}


bool CSpriteObjs::HasObj(CSpriteObj *obj) {
  objPlace_t where = find(sObjs.begin(), sObjs.end(), obj);
  return where != sObjs.end();
}


bool CSpriteObjs::HasFlicker(CSpriteObj* flicker) {
  return flicker && HasObj(flicker) && dynamic_cast<CFlicker*>(flicker);
}


CSpriteObj* CSpriteObjs::HitObj(CScreenPos pos, bool drawn) { //anybody here?
  for(robjPlace_t o = sObjs.rbegin(); o != sObjs.rend(); ++o)
    //if they've hit - drawn specifies if they had to have been drawn or not
    if(((*o)->IsUpdated() || !drawn) && (*o)->InSprite(pos))
      return (*o); //we have our target!
  return 0; //couldn't find any spr obj in (x,y)
}


void CSpriteObjs::Stop(const CVector2& pos, const CSpriteObj &ship, 
		       float maxTime) {
  for(objPlace_t o = sObjs.begin(); o != sObjs.end(); ++o) {
    if(*o == &ship) continue;
    CVector2 direction = (*o)->GetPos() - pos;
    float scale = CShips::GetDistanceScaling(direction);
    float deltaT = maxTime * scale;
    (*o)->Stop(deltaT);   
  }
}


void CSpriteObjs::DrawObj(CSpriteObj* sprObj) {
  // DEBUG("Drawing  obj %p of type %s at (%d, %d)\n",
  // 	sprObj, typeid(*sprObj).name(),
  // 	int(sprObj->GetPos().GetX()), int(sprObj->GetPos().GetY()));
  sprObj->Draw();
  sprObj->SetUpdated(true);
}


void CSpriteObjs::EraseObj(CSpriteObj* sprObj) {
  sprObj->Erase();
  sprObj->SetUpdated(false);
}
