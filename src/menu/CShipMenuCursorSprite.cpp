#include "CShipMenuCursorSprite.hpp"
#include "CCanvas.hpp"
#include "CTeam.hpp"
#include "CGravSprite.hpp"
#include "CRectFill.hpp"
#include "CCircle.hpp"
#include "CColour.hpp"
#include "CStringMenu.hpp"
#include "CFont.hpp"
#include <stdio.h>
#include <math.h>


CGravSprite* CShipMenuCursorSprite::CreateSprite(int index, const CTeam &team) {

 int radius = 30;
 int halfWidth = 10, rectHeight=12;
 int width,height;
 width = height = radius*2 + rectHeight*2 + 1;
 //int deltaX = width -radius + rectHeight + 4; //set this for client code
 CCanvas canvas(width, height);
 CCircle c(canvas, rectHeight + radius, rectHeight + radius, radius,
         team.GetDarkColour());
 int dy = 0;
 if(index == 2) dy = rectHeight + radius*2;
 CRectFill r(canvas, rectHeight+radius-halfWidth, dy,
             rectHeight + radius + halfWidth, rectHeight + dy,
             team.GetDarkColour());
 char title[200];
 sprintf(title,"P%d",index+1);
 CStringMenu::GetFont().PrintCentre(canvas, rectHeight + radius + 2, 2 + dy,
                                    CColour::GetBlack(), -1, title);
 float angle = index*(M_PI/2);
 if(index == 2) angle = 0; //don't rotate 180 degrees

 return new CGravSprite(canvas.GetData(), team, angle);
}
