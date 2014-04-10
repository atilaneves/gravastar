//adapted by me (Atila) but not written by me
#include "CStarField.hpp"
#include "CCanvas.hpp"
#include "CDataFile.hpp"
#include "starsdat.h"
#include <allegro.h>


static volatile long timer_counter=0;

void inc_timer_counter() {
 timer_counter++;
}
END_OF_FUNCTION(inc_timer_counter);


CStarField::CStarField(int width,int height):
   mDataFile("stars.dat"), mWidth(width), mHeight(height),
   mBackgroundX(0), mBackgroundStep(0) {

  mStar1.reset(new CCanvas(mDataFile.GetData(kSTAR1)));
  mStar2.reset(new CCanvas(mDataFile.GetData(kSTAR2)));
  NewCanvas(width, height);

  LOCK_VARIABLE(timer_counter);
  LOCK_FUNCTION(inc_timer_counter);
  int nbMilliSecs = 1;
  install_int(inc_timer_counter,nbMilliSecs);
}


void CStarField::NewCanvas(int width, int height) {
  mBackground.reset(new CCanvas(width, height));
  CCanvas canvas(mDataFile.GetData(kBACKGROUND));
  canvas.StretchBlit(*mBackground.get(), 0, 0, width, height);
  mWidth = width;
  mHeight = height;
  InitStars();
}


void CStarField::InitStars() {
  for(int a=1; a<kLayersStars; a++) {
    for(int b=0; b<kNbStars; b++) {
      mStars[a][b].x = (rand() % mWidth);
      mStars[a][b].y = (rand() % mHeight);
    }
  }
}

CStarField::~CStarField() {
  remove_int(inc_timer_counter);
}


void CStarField::Draw(CCanvas &canvas) {

 AnimateStars(); //move them if it's time

 if(mBackgroundX == 0)
    mBackground->Draw(canvas,0,0);
 else {
    mBackground->MaskBlit(canvas, mBackgroundX, 0, 0, 0,
                          canvas.GetWidth() - mBackgroundX,
                          canvas.GetHeight());
    mBackground->MaskBlit(canvas, 0, 0, canvas.GetWidth() - mBackgroundX,
                          0, mBackgroundX, canvas.GetHeight());
 }

 for(int b=0; b<kNbStars; b++) {
    canvas.PutPixel(mStars[3][b].x,mStars[3][b].y, makecol(165, 165, 255));
    mStar2->Draw(canvas, mStars[2][b].x, mStars[2][b].y);
    mStar1->Draw(canvas, mStars[1][b].x, mStars[1][b].y);
 }

}


void CStarField::MoveStars() {

 static int whenToDraw = 0; //Diferent speed of star layers
 int c = kLayersStars - 2;
 whenToDraw++;

 if (whenToDraw > kLayersStars-1) c = kLayersStars-1;
 if (whenToDraw > kLayersStars) {
    c = kLayersStars;
    whenToDraw = 0;
 }

 for(int a = 1; a < c ; a++) {
    for(int b=0 ; b<kNbStars; b++) {
       mStars[a][b].x -= (kSpeedStars * mWidth) / 640;

       if(mStars[a][b].x > mWidth) mStars[a][b].x = 0;
       if(mStars[a][b].x < 0) {
          mStars[a][b].x = mWidth;
          mStars[a][b].y = (rand() % mHeight);
       }
    }
 }

 if(c == kLayersStars) {
    mBackgroundStep++;
    if(mBackgroundStep == 2) {
       mBackgroundX++;
       mBackgroundStep = 0;
    }
    if(mBackgroundX > mWidth) mBackgroundX = 0;
 }

}


void CStarField::AnimateStars() {

 static long stars_move_time=0;  //speed in msec of the stars

 if(timer_counter > stars_move_time) {
    MoveStars();
    stars_move_time = timer_counter + 5;
 }

}


void CStarField::ShiftCanvas(CCanvas *canvas) {
 for(int y=0; y<canvas->GetHeight(); y++)
    for(int x=0; x<canvas->GetWidth(); x++)
       canvas->PutPixel(x,y,canvas->GetPixel(x,y)+kDeltaColour);
}
