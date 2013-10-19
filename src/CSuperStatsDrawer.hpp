#ifndef CSUPERSTATSDRAWER_H_
#define CSUPERSTATSDRAWER_H_

#include <cstddef>

class CCanvas;

class CSuperStatsDrawer {
public:
    CSuperStatsDrawer(bool canUse, size_t spriteHash);
    void Draw(CCanvas& canvas) const;

private:

    const bool mCanUse;
    const size_t mSpriteHash;
};


#endif // CSUPERSTATSDRAWER_H_
