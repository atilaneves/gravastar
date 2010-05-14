#include "CColour.hpp"
#include <allegro.h>
#include <math.h>
#include <algorithm>



int CColour::GetColour(int red, int green, int blue) {
  return makecol(red, green, blue);
}


int CColour::GetBlack() {
  return GetColour(0, 0, 0);
}


int CColour::GetWhite() {
  return GetColour(255, 255, 255);
}


void CColour::RGBtoHSV(int colour, float &h, float &s, float &v) {
  int r = getr(colour);
  int g = getg(colour);
  int b = getb(colour);
  int min = std::min(std::min(r, g), b);
  int max = std::max(std::max(r, g), b);
  v = max;				// v
  float delta = max - min;

  if(max != 0)
    s = delta / max;		// s
  else {
    // r = g = b = 0  // s = 0, v is undefined
    h = -1;
    s = 0;
    v = 0;
    return;
  }

  if(max == min) {
    h = 0;
  }
  else if(r == max)
    h = (360 + 60 * ((g - b) / delta)); // between yellow & magenta
  else if( g == max )
    h = 120 + 60 * ((b - r) / delta); // between cyan & yellow
  else
    h = 240 + 60 * ((r - g) / delta); // between magenta & cyan

  if(h < 0)   h += 360;
  if(h > 360) h -= 360;
}


int CColour::HSVtoRGB(float h, float s, float v) {
  if( s == 0 ) return GetColour(int(v), int(v), int(v)); //grey

  h /= 60;
  int i = int(floor(h));
  float f = h - i;			// factorial part of h
  float p = v * ( 1 - s );
  float q = v * ( 1 - s * f );
  float t = v * ( 1 - s * ( 1 - f ) );
  int r, g, b;

  switch( i ) {
  case 0:
    r = (int)v;
    g = (int)t;
    b = (int)p;
    break;
  case 1:
    r = (int)q;
    g = (int)v;
    b = (int)p;
    break;
  case 2:
    r = (int)p;
    g = (int)v;
    b = (int)t;
    break;
  case 3:
    r = (int)p;
    g = (int)q;
    b = (int)v;
    break;
  case 4:
    r = (int)t;
    g = (int)p;
    b = (int)v;
    break;
  default:		// case 5:
    r = (int)v;
    g = (int)p;
    b = (int)q;
    break;
  }

  return GetColour(r, g, b);
}
