#include "CSubCanvas.hpp"
#include "CCanvas.hpp"


CSubCanvas::CSubCanvas(const CCanvas &canvas, int x, int y,
                       int width, int height):
  CBitmap(create_sub_bitmap((BITMAP*)canvas.GetData(), x, y, width, height)),
  mMainCanvas(&canvas), mX(x), mY(y), mWidth(width), mHeight(height) {

}


CSubCanvas::CSubCanvas(const CSubCanvas &subCanvas):
  CBitmap(create_sub_bitmap((BITMAP*)subCanvas.mMainCanvas->GetData(),
                            subCanvas.mX, subCanvas.mY,
                            subCanvas.mWidth, subCanvas.mHeight)),
  mMainCanvas(subCanvas.mMainCanvas), mX(subCanvas.mX), mY(subCanvas.mY),
  mWidth(subCanvas.mWidth), mHeight(subCanvas.mHeight) {
}
