#include "CSpriteMenuBkg.hpp"
#include "CCanvas.hpp"
#include "CSprite.hpp"



CSpriteMenuBkg::CSpriteMenuBkg(CSprite &sprite, int x, int y):
   mSprite(sprite), mX(x), mY(y) {

}


void CSpriteMenuBkg::Draw(CCanvas &canvas) {
 mSprite.Draw(canvas, mX, mY);
}
