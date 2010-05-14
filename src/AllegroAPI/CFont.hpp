#ifndef CFONT_H
#define CFONT_H


class CCanvas;
class CDataFile;
#include <allegro.h>
#include <string>



class CFont {

public:

  CFont(int fontIndex = -1);
  CFont(const CFont& font);
  CFont& operator=(const CFont& font);
  ~CFont();
  
  int   GetHeight() const { return text_height(mFont); }
  int   GetLength(const std::string &str) const {
    return text_length(mFont,str.c_str()); }
  void  Print(CCanvas &canvas, int x, int y, int col, int bg,
	      const std::string &str) const;
  void  PrintCentre(CCanvas &canvas,int x,int y,int col, int bg,
		    const std::string &str) const;


private:

 static int        sNbFonts;
 static CDataFile *sDataFile;

 FONT *mFont;

};

#endif
