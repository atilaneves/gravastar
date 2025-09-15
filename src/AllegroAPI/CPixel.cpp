#include "CPixel.hpp"
#include "CCanvas.hpp"


void CPixel::Draw(CCanvas &canvas, int x, int y) const {
    _putpixel((BITMAP*)canvas.GetData(), x, y, mColour);
}


void CPixel::Erase(const CCanvas &canvas, int x, int y) {
    _putpixel((BITMAP*)canvas.GetData(), x, y, makecol(0, 0, 0));
}
