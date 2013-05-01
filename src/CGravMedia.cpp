#include "CGravMedia.hpp"
#include "CMeleeOptions.hpp"


CGravMedia::CGravMedia(const CMeleeOptions &meleeOptions,
                       const CClientOptions::AllPilotOptions& allPilotOptions):
  mLevel(meleeOptions.GetLevelNb()),
  mShipYard(mLevel, allPilotOptions) {

}
