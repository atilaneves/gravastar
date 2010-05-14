#include "CPixel.hpp"
#include "CCanvas.hpp"


void CPixel::Draw(const CCanvas &canvas, int x, int y) {
    _putpixel((BITMAP*)canvas.GetData(), x, y, mColour);
}


void CPixel::Erase(const CCanvas &canvas, int x, int y) {
    _putpixel((BITMAP*)canvas.GetData(), x, y, makecol(0, 0, 0));
}
