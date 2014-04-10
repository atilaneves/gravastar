#include "CSpriteCanvas.hpp"
#include "CColour.hpp"


CSpriteCanvas::CSpriteCanvas(void *data):
  CCanvas(data) {

  Constructor(data);
}


CSpriteCanvas::CSpriteCanvas(const CBitmap &bitmap):
  CCanvas(bitmap) {

  Constructor(bitmap.GetData());
}


void CSpriteCanvas::Constructor(void *data) {
  Clear();
  CCanvas canvas(data);
  canvas.Draw(*this, 0, 0);
}


CSpriteCanvas::CSpriteCanvas(int w, int h):
  CCanvas(w, h) {

  Clear();

}

void CSpriteCanvas::Clear() { 
 clear_to_color(mData, GetMask()); 
}
