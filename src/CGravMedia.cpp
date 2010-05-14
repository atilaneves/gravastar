#include "CGravMedia.hpp"
#include "CGravOptions.hpp"


CGravMedia::CGravMedia(const CGravOptions &options):
  mLevel(options.GetMeleeOptions().GetLevelNb()),
  mShipYard(mLevel, options) {

}
