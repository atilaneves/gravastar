#ifndef CMENU_ICON_CYCLE_H
#define CMENU_ICON_CYCLE_H


class CFont;
class CCycleLeaf;
#include "CMenuIcon.hpp"
#include "CMenuIconString.hpp"
#include "CColour.hpp"
#include <string>


class CMenuIconCycle:public CMenuIcon {

public:

  CMenuIconCycle(const std::string &title, const CCycleLeaf &cycleMenu);
  virtual ~CMenuIconCycle() { }

  virtual int GetHeight() const override { return mTitle.GetHeight(); }
  const std::string& GetTitle() const { return mTitle.GetTitle(); }
  virtual int GetWidth() const override;
          void SetTitle(const std::string& t) { mTitle.SetTitle(t); }



protected:

  const CFont& mFont;
  CMenuIconString mTitle;
  const CCycleLeaf& mCycleMenu;

  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight=false) const override;

};

#endif
