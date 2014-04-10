#ifndef CSHIP_STAT_SPRITE_H
#define CSHIP_STAT_SPRITE_H


class CCanvas;
class CDataFile;
class CTeam;
#include "CDrawable.hpp"
#include "CGravSprite.hpp"
#include <memory>


class CShipStatSprite: public CDrawable {

public:

    CShipStatSprite(void *data, const CTeam& team);
    CShipStatSprite(const CShipStatSprite& sprite);
    virtual ~CShipStatSprite() { }

    virtual void Draw(CCanvas &canvas, int x, int y) const override;
    virtual int GetWidth() const override { return mSprite->GetWidth(); }
    virtual int GetHeight() const override { return mSprite->GetHeight(); }
          size_t GetHash() const { return mSprite->GetHash(); }


private:

    float        mScale;
    const CTeam& mTeam;
    std::unique_ptr<CGravSprite> mSprite;
};

#endif
