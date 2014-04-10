#ifndef CMENU_VIDEO_H
#define CMENU_VIDEO_H


#include "CStringMenu.hpp"
#include "CMenuCursor.hpp"
class CCycleString;
class CCycleLeaf;
class CMeleeOptions;
class CSprite;
class CClientOptions;


class CVideoMenu: public CStringMenu {

public:


  CVideoMenu(CSprite *cursorSprite, const CClientOptions& options);

          int  GetHeight()     const;
          bool GetSmartSplit() const;
          int  GetWidth()      const;
          bool GetWindowed()   const;
  virtual void Run(CRootMenu &rootMenu);


private:

  CMenuCursor mCursor;
  int mOldWindowed, mOldResolution;
  CCycleString *mWindowed;
  CCycleString *mSmart;
  CCycleString *mResolution;
  
  virtual void Update(CRootMenu &rootMenu);

};

#endif
