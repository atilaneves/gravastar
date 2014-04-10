#include "CResolution.hpp"
#include "CCanvas.hpp"
#include <allegro.h>


bool     CResolution::sWindowed = true;
bool     CResolution::sChangedWindowed = false;
CCanvas *CResolution::sScreen = nullptr;

bool CResolution::SetMode(int width, int height) {
 //only change if we have to

  if(width == GetWidth() && height == GetHeight() && !sChangedWindowed) return false;

  if(sWindowed)
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
  else
    set_gfx_mode(GFX_AUTODETECT, width, height, 0, 0);

  sScreen = new CCanvas(screen);

  set_display_switch_mode(SWITCH_BACKGROUND);
  //CSound::SetMaxX(width);
  sChangedWindowed = false; //reset
  return true; //actually changed the gfx mode
}


void CResolution::SetColourDepth(int depth) {
  set_color_depth(depth);
}

int CResolution::GetHeight() {
 return SCREEN_H;
}


int CResolution::GetWidth() {
 return SCREEN_W;
}
