#ifndef CSUPERSTATSDRAWER_H_
#define CSUPERSTATSDRAWER_H_

#include <cstddef>

class CCanvas;
class Cereal;

class CSuperStatsDrawer {
public:

    CSuperStatsDrawer() {}
    CSuperStatsDrawer(bool canUse, size_t spriteHash);
    void Draw(CCanvas& canvas) const;
    void cerealise(Cereal& cereal);

private:

    bool mCanUse;
    size_t mSpriteHash;
};


#endif // CSUPERSTATSDRAWER_H_
