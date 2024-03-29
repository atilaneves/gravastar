#include "CSpriteObjs.hpp"
#include "CSpriteObj.hpp"
#include "CShips.hpp"
#include "CFlicker.hpp"
#include "SClientFrame.hpp"
#include "Cerealiser.hpp"
#include "debug.hpp"
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <limits>
#include <assert.h>
#include <chrono>
#include <stdint.h>


CSpriteObjs::objs_t CSpriteObjs::sObjs;
CSpriteObjs::SpritePositions CSpriteObjs::sSpritePositions;
CChrono CSpriteObjs::sChrono;

void CSpriteObjs::Update(float dt) {

    sSpritePositions.clear();

    for (auto &sObj : sObjs) {
        //DEBUG("Update  obj %p of type %s\n", *o, typeid(**o).name());
      (sObj)->Update(dt);
      if ((sObj)->IsActive())
        DrawObj(sObj);
    }

    std::vector<CSpriteObj*> toDelete; //inactive sprite objs

    for (auto &sObj : sObjs)
      if (!(sObj)->IsActive())
        toDelete.push_back(sObj); // find all at same time

    for (auto &elem : toDelete)
      DeleteObj(elem); // safe to delete all of them now
}


void CSpriteObjs::Erase() {
  for (auto &sObj : sObjs)
    EraseObj(sObj);
}


void CSpriteObjs::AddObj(CSpriteObj *obj, bool back) {
    DEBUG("Adding   obj %p of type %s, total will be %d\n",
          static_cast<void*>(obj), typeid(*obj).name(), (int)sObjs.size() + 1);
    if(back) sObjs.push_back(obj);
    else     sObjs.push_front(obj);
}


void CSpriteObjs::DeleteObj(CSpriteObj *obj) {
    DEBUG("Deleting obj %p of type %s, total will be %d\n",
          static_cast<void*>(obj), typeid(*obj).name(), (int)sObjs.size() - 1);
    sObjs.remove(obj);
    if(obj->IsUpdated()) obj->Erase();
    delete obj;
}


void CSpriteObjs::RemoveObj(CSpriteObj *obj) {
    DEBUG("Removing obj %p of type %s, total will be %d\n",
          static_cast<void*>(obj), typeid(*obj).name(), (int)sObjs.size() - 1);
    auto where = find(sObjs.begin(), sObjs.end(), obj);
    if(where != sObjs.end()) sObjs.erase(where);
}


void CSpriteObjs::DeleteAll() {
  for (auto &sObj : sObjs) {
    DEBUG("(all) deleting obj %p of type %s\n", static_cast<void *>(sObj),
          typeid(*sObj).name());
    delete sObj;
    }
    sObjs.clear();
}


bool CSpriteObjs::HasObj(CSpriteObj *obj) {
  auto where = find(sObjs.begin(), sObjs.end(), obj);
    return where != sObjs.end();
}


bool CSpriteObjs::HasFlicker(CSpriteObj* flicker) {
    return flicker && HasObj(flicker) && dynamic_cast<CFlicker*>(flicker);
}


CSpriteObj* CSpriteObjs::HitObj(CScreenPos pos, bool drawn) { //anybody here?
  for (auto o = sObjs.rbegin(); o != sObjs.rend(); ++o)
        //if they've hit - drawn specifies if they had to have been drawn or not
        if(((*o)->IsUpdated() || !drawn) && (*o)->InSprite(pos))
            return (*o); //we have our target!
  return nullptr; // couldn't find any spr obj in (x,y)
}


void CSpriteObjs::Stop(const CVector2& pos, const CSpriteObj &ship,
                       float maxTime) {
  for (auto &sObj : sObjs) {
    if (sObj == &ship)
      continue;
    CVector2 direction = (sObj)->GetPos() - pos;
        float scale = CShips::GetDistanceScaling(direction);
        float deltaT = maxTime * scale;
        (sObj)->Stop(deltaT);
    }
}


void CSpriteObjs::DrawObj(CSpriteObj* sprObj) {
    const auto spritePos = sprObj->Draw();
    if(spritePos.WasDrawn()) sSpritePositions.push_back(spritePos);
    sprObj->SetUpdated(true);
}


void CSpriteObjs::EraseObj(CSpriteObj* sprObj) {
    sprObj->Erase();
    sprObj->SetUpdated(false);
}

auto CSpriteObjs::Pack(const Pilots& pilots) -> FrameBytes {
    assert(sSpritePositions.size() <= std::numeric_limits<uint16_t>::max());
    const uint32_t milliseconds = sChrono.SinceStartMs();
    assert(milliseconds <= std::numeric_limits<decltype(milliseconds)>::max());

    Cerealiser cereal;
    cereal << SClientFrame{milliseconds, pilots, sSpritePositions};
    return cereal.getBytes();
}
