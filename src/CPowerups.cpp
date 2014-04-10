#include "CPowerups.hpp"
#include "CLevel.hpp"
#include "CPowerupFactory.hpp"
#include "CPowerup.hpp"
#include "CGravSprite.hpp"
#include "CDataFile.hpp"
#include "CDirectory.hpp"
#include <stdlib.h>



CPowerups::CPowerups(CLevel& level, float rate):
    mLevel(level), mRate(rate) {
  
    const std::vector<std::string>& keys = CPowerupFactory::Instance().GetKeys();
    for (auto &key : keys) {
      mPowerups.push_back(nullptr); // have the space, but not the powerup yet
        CDataFile file("Powerups/" + key + ".dat");
        const int kFileIndex = 0;
        auto sprite = new CGravSprite(file.GetData(kFileIndex));
        mNames.push_back(key);
        mSpritesMap[key] = sprite;
    }
}


CPowerups::~CPowerups() {
  for (auto &elem : mSpritesMap)
    delete (elem).second;
}


void CPowerups::Generate(float dt) {

    if(rand()/float(RAND_MAX) < mRate*dt) {
        int powerupIndex = rand() % mPowerups.size();
        if(!mPowerups[powerupIndex]) {
            int x, y, side=10;
            do {
                x = rand() % mLevel.GetWidth();
                y = rand() % mLevel.GetHeight();
            } while(!mLevel.IsFreeSquare(x, y, side));
            CPowerupFactory& factory = CPowerupFactory::Instance();
            const std::string name = mNames[powerupIndex];
            mPowerups[powerupIndex] = factory.CreateObject(name, *this, mLevel,
                                                           CVector2(x, y),
                                                           *mSpritesMap[name]);
        }
    }
}


float CPowerups::NearestDistance(const CVector2& shipPos) const {
    const float bigDist = 1e10;
    const CPowerup* powerup = NearestPowerup(shipPos);
    return powerup ? (powerup->GetPos() - shipPos).Radius() : bigDist;
}


const CPowerup* CPowerups::NearestPowerup(const CVector2& shipPos) const {
  
    float minDist = 9e9;
    int minPowerup = -1;
  
    for(unsigned int i = 0; i<mPowerups.size(); i++) {
        if(mPowerups[i]) {
            float distance = (mPowerups[i]->GetPos() - shipPos).Radius();
            if(distance < minDist) {
                minDist = distance;
                minPowerup = i;
            }
        }
    }

    return minPowerup > 0 ? mPowerups[minPowerup] : nullptr;
}


void CPowerups::Remove(CPowerup *powerup) {
  for (auto &elem : mPowerups)
    if (elem == powerup)
      elem = nullptr;
}
