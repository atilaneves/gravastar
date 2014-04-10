#ifndef CCOLOUR_H
#define CCOLOUR_H


class CColour {

public:

  static int GetColour(int red, int green, int blue);
  static int GetTransparent();
  static int GetBlack();
  static int GetWhite();
  static void RGBtoHSV(int colour, float &h, float &s, float &v);
  static int HSVtoRGB(float h, float s, float v);

private:

};

#endif
