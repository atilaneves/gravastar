#ifndef CSTARFIELD_H
#define CSTARFIELD_H


#include "CMenuBackground.hpp"
#include "CDataFile.hpp"
#include "CCanvas.hpp"
#include <memory>


class CStarField:public CMenuBackground {

public:

  enum { kNbStars=32, kSpeedStars=1, kLayersStars=4, kDeltaColour=102 };

  CStarField(int width,int height);
  virtual ~CStarField();

  virtual void Draw(CCanvas &canvas) override;
  virtual void NewCanvas(int width, int height) override;

private:

  struct Stars2D {
    int x, y;
  };

  CDataFile mDataFile;
  int mWidth;
  int mHeight;
  int mBackgroundX;
  int mBackgroundStep;
  Stars2D mStars[kLayersStars][kNbStars];
  std::unique_ptr<CCanvas> mBackground;
  std::unique_ptr<CCanvas> mStar1;
  std::unique_ptr<CCanvas> mStar2;

  void AnimateStars();
  void InitStars();
  void MoveStars();
  void ShiftCanvas(CCanvas *canvas);

};

#endif
