#ifndef CLEVEL_HEADER_H
#define CLEVEL_HEADER_H


#include "CCanvas.hpp"
#include <string>
#include <memory>


class CLevelHeader {

public:

  CLevelHeader(unsigned int levelNb);
  
  float              GetAirFriction()  const  { return mAirFriction;  }
  CCanvas&           GetCanvas()       const  { return *mCanvas;      }
  float              GetLandFriction() const  { return mLandFriction; }
  float              GetGravity()      const  { return mGravity;      }
  int                GetHeight()       const;
  const std::string& GetTitle()        const  { return mTitle;        }
  int                GetWidth()        const;


protected:

  std::string              mFileName;
  std::string              mCfgName;
  std::string              mTitle; //name of the level
  std::unique_ptr<CCanvas> mCanvas;
  int   mNbInds;
  float mGravity, mAirFriction, mLandFriction;


private:

  static const std::string GetFileName(unsigned int levelNb);

};


#endif
