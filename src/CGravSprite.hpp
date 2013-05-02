#ifndef CGRAVSPRITE_H
#define CGRAVSPRITE_H


#include "CSpriteable.hpp"
#include "CSprite.hpp"
#include "CSpriteCollision.hpp"
#include "CScreenPos.hpp"
#include "CVector2.hpp"
#include "CTeam.hpp"
#include <memory>
#include <unordered_map>
class CSpriteCanvas;



class CGravSprite: public CSpriteable {

public:

    CGravSprite(void *data, const CTeam &team = CTeam::sWhite,
                float angle = 0, float scale = 1, int colour = -1);
    virtual ~CGravSprite();

    static CGravSprite* GetSprite(size_t hash) { return sSprites[hash]; }
    static bool EnableHashing(bool e) { sHashing = e; return e;}

    positions_t      Collided(const CCanvas &canvas, const CVector2 &pos) const;
    bool             Collided(const CCanvas& canvas, const CGravSprite& sprite,
                              const CVector2& pos1, const CVector2& pos2) const;
    virtual void     Draw (CCanvas &canvas, int x, int y) const;
    virtual void     Erase(CCanvas &canvas, int x, int y) const;
            size_t   GetHash() const { return mSpriteIndex; }
             int     GetHeight() const;
    const CSprite*   GetSprite() const { return mSprite.get(); }
             int     GetWidth()  const;
             bool    InSprite(int x, int y) const { return mCollision.InSprite(x, y); }

private:

    std::unique_ptr<CSprite> mSprite; //what you draw with
    std::unique_ptr<CSprite> mErase;  //what you erase with
    CSpriteCollision mCollision;
    size_t mSpriteIndex;
    static bool sHashing;
    static size_t sSpriteIndex;
    static std::unordered_map<size_t, CGravSprite*> sSprites;    

    void Transform(BITMAP *bmp, const CTeam &team, int colour, 
                   CSpriteCanvas &draw, CSpriteCanvas &erase);

};



#endif
