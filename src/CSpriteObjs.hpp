#ifndef CSPRITEOBJS_H
#define CSPRITEOBJS_H


#include "CSpriteObj.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CRadar.hpp"
#include "CChrono.hpp"
#include "Cereal.hpp"
#include <list>
#include <vector>

class CSpriteObjs {
public:

    typedef std::list<CSpriteObj*> objs_t;
    typedef objs_t::iterator objPlace_t;
    typedef objs_t::reverse_iterator robjPlace_t;
    using Pilots = CRadar::pilots_t;
    using FrameBytes = Cereal::Bytes;
    using SpritePositions = std::vector<CLevelSprite>;

    static void        AddObj(CSpriteObj *sprObj, bool back = true);
    static void        DeleteAll();
    static bool        HasObj(CSpriteObj *sprObj);
    static bool        HasFlicker(CSpriteObj *flicker);
    static void        RemoveObj(CSpriteObj *sprObj);
    static void        Erase();
    static FrameBytes  Pack(const Pilots& pilots);
    static CSpriteObj* HitObj(CScreenPos pos, bool drawn = true); //anyone here?
    static void        Stop(const CVector2& pos, const CSpriteObj &ship,
                            float maxTime);
    static void        Update(float dt);


private:

    static objs_t sObjs;
    static SpritePositions sSpritePositions;
    static CChrono sChrono;

    static void DrawObj(CSpriteObj* sprObj);
    static void EraseObj(CSpriteObj* sprObj);
    static void DeleteObj(CSpriteObj *sprObj);
};


#endif
