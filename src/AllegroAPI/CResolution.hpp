#ifndef CRESOLUTION_H
#define CRESOLUTION_H


class CCanvas;


class CResolution {

public:


  static int      GetHeight();
  static CCanvas &GetScreen() { return *sScreen; }
  static int      GetWidth();
  static void     SetColourDepth(int depth);
  static bool     SetMode(int width, int height);
  static void     SetWindowed(bool w) { sWindowed=w; sChangedWindowed=true; }


private:

  static CCanvas *sScreen;
  static bool     sWindowed;
  static bool     sChangedWindowed;

};


#endif
