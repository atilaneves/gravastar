#include "CCanvas.hpp"
#include "CColour.hpp"


CCanvas::CCanvas(void *data):
  CBitmap(data == screen ? screen : CopyBitmap(data)) {
}


CCanvas::CCanvas(const CBitmap &bitmap):
  CBitmap(mData = CopyBitmap(bitmap.GetData())) {
}


CCanvas::CCanvas(int w, int h):
  CBitmap(create_bitmap(w, h)) {

  Clear();

}


CCanvas& CCanvas::operator=(const CCanvas &canvas) {
  if(mData != screen) destroy_bitmap(mData);
  mData = CopyBitmap(canvas.mData);
  return *this;
}
