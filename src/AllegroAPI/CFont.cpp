#include "CFont.hpp"
#include "CDataFile.hpp"
#include "CCanvas.hpp"


int        CFont::sNbFonts  = 0;
CDataFile* CFont::sDataFile = 0;


CFont::CFont(int fontIndex) {
  if(sNbFonts == 0) //1st font ever, load the file
    sDataFile = new CDataFile("fonts.dat");
  
  if(fontIndex >= 0)
    mFont=(FONT*)sDataFile->GetData(fontIndex);
  else
    mFont=font; //default allegro font
  
  sNbFonts++;
}


CFont::CFont(const CFont &font) {
  sNbFonts++;
  mFont = font.mFont;
}


CFont& CFont::operator=(const CFont& font) {
  mFont = font.mFont;
  return *this;
}


CFont::~CFont() {
  sNbFonts--;
  if(sNbFonts == 0) delete sDataFile;
}


void CFont::Print(CCanvas &canvas,int x,int y,int col, int bg,
                  const std::string &str) const {
 textprintf_ex((BITMAP*)canvas.GetData(),mFont,x,y,col,bg,str.c_str());
}


void CFont::PrintCentre(CCanvas &canvas,int x,int y,int col, int bg,
                        const std::string &str) const {
 textprintf_centre_ex((BITMAP*)canvas.GetData(),mFont,x,y,col,bg,str.c_str());
}
