#include "CStringMenu.hpp"
#include "CMenuIconString.hpp"
#include "CFont.hpp"
#include <stdio.h>
#include <stdlib.h>

const CFont *CStringMenu::sFont = nullptr; // default font

CStringMenu::CStringMenu(const std::string &title):
  CMenu(new CMenuIconString(title, *sFont)) {

  if (sFont) return; //all ok, nothing to do

  fprintf(stderr, "Font not set in CStringMenu!\n"); //oops
  exit(1);

}


void CStringMenu::SetFont(const CFont *font) {
  sFont = font;
}


const std::string& CStringMenu::GetTitle() const { 
    return ((CMenuIconString*)mIcon.get())->GetTitle();
}
