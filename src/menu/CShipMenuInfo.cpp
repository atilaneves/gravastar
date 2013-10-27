#include "CShipMenuInfo.hpp"
#include "CShipMenuItem.hpp"
#include "CSprite.hpp"
#include "CColour.hpp"
#include "CDataFile.hpp"
#include "CTimeCounter.hpp"
#include "CCircle.hpp"
#include "CRectFill.hpp"
#include "CLine.hpp"
#include "CResolution.hpp"
#include "CTeam.hpp"
#include "CVersusMenu.hpp"
#include "CShipStatSprite.hpp"
#include "deltadat.h"
#include "fontsdat.h"
#include "menudat.h"
#include <stdio.h>
#include <math.h>


CCanvas* createCanvas(const CDataFile& dataFile, int index) {
    CCanvas *canvas = new CCanvas(dataFile.GetData(index));
    for(int y = 0; y < canvas->GetHeight(); ++y)
        for(int x = 0; x < canvas->GetWidth(); ++x)
            if(canvas->GetPixel(x, y) == CColour::GetBlack())
                canvas->PutPixel(x, y, canvas->GetMask());
    return canvas;
}


CShipMenuInfo::CShipMenuInfo(int index, const CTeam &team,
                             const CVersusMenu& versus):
    mIndex(index), mTeam(team), mDirectory("Ships"),
    mSmallFont(Westminster8), mBigFont(MetroStyleExtendedBold22),
    mCanvas(kRectWidth+1,kDeltaY+kRectHeight+1),
    mVersus(versus) {

    mTimeCounter.Start(0.05);

    for(int i = 0; i < mDirectory.GetNbEntries(); i++) {
        std::string shipName(mDirectory.GetEntryNoExt(i));
        CDataFile dataFile("Ships/" + shipName + ".dat");
        AddSprite(shipName, createCanvas(dataFile, BLUE_000));
    }

    CDataFile questionFile("menu.dat");
    AddSprite("Random", createCanvas(questionFile, QUESTION));
    }


void CShipMenuInfo::AddSprite(const std::string& name, CCanvas *canvas) {
    mSprites[name]     = canvas;
    mStatSprites[name] = new CShipStatSprite(canvas->GetData(), mTeam);
}


CShipMenuInfo::~CShipMenuInfo() {
    for(spritePlace_t i = mSprites.begin(); i != mSprites.end(); ++i)
        delete (*i).second;
    for(statPlace_t i = mStatSprites.begin(); i != mStatSprites.end(); ++i)
        delete (*i).second;
}


void CShipMenuInfo::Draw(CCanvas &canvas, const CShipMenuItem &shipItem) {

    DrawGeometry();
    Write(shipItem);
    DrawSprite(shipItem);
    DrawSquad(shipItem);
    int x = mIndex%2 == 0 ? 0 : CResolution::GetWidth() - kRectWidth-1;
    int y = mIndex/2 == 0 ? 70 : CResolution::GetHeight()-kRectHeight-kDeltaY-1;
    mCanvas.Draw(canvas,x,y);
}


void CShipMenuInfo::DrawGeometry() {

    int colour = mTeam.GetDarkColour();
    CRectFill r1(mCanvas, 0, 0, mCanvas.GetWidth()-1,
                 mCanvas.GetHeight()-1,colour);
    CRectFill r2(mCanvas, kLineWidth,kDeltaY,mCanvas.GetWidth()-kLineWidth,
                 mCanvas.GetHeight()-kLineWidth, mCanvas.GetMask());

    char title[100];
    sprintf(title,"Player%d",mIndex+1);
    mBigFont.PrintCentre(mCanvas,kRectWidth/2,3,mCanvas.GetMask(), -1, title);
    CCircle c1(mCanvas, kLineWidth*2+kRadius,kDeltaY+kLineWidth+kRadius,
               kRadius,CColour::GetWhite());
    CLine l1(mCanvas, kLineWidth*3+kRadius*2,kDeltaY+kLineWidth*3,
             kRectWidth-kLineWidth*2,kDeltaY+kLineWidth*3,
             CColour::GetWhite()); //horiz. line
    CLine l2(mCanvas,kLineWidth*3+kRadius*2-8,kDeltaY+kLineWidth*3+5,
             kLineWidth*3+kRadius*2,kDeltaY+kLineWidth*3,
             CColour::GetWhite()); //diag. line
}


void CShipMenuInfo::Write(const CShipMenuItem &shipItem) {

    mSmallFont.Print(mCanvas,kLineWidth*3+kRadius*2,
                     kDeltaY+kLineWidth,
                     CColour::GetWhite(), -1, shipItem.GetShipName());
    mSmallFont.Print(mCanvas,kLineWidth*3+kRadius*2,
                     kDeltaY+(kLineWidth+4)*2+6,
                     CColour::GetWhite(), -1, shipItem.GetWeaponName());
    mSmallFont.Print(mCanvas,kLineWidth*3+kRadius*2,
                     kDeltaY+(kLineWidth+4)*3+6,
                     CColour::GetWhite(), -1, shipItem.GetSpecialName());
    mSmallFont.Print(mCanvas,kLineWidth*3+kRadius*2,
                     kDeltaY+(kLineWidth+4)*4+6,
                     CColour::GetWhite(), -1, shipItem.GetSuperName());
}


void CShipMenuInfo::DrawSprite(const CShipMenuItem &shipItem) {

    static int fixAngle=0;
    if(!mTimeCounter.IsActive()) {
        fixAngle = (fixAngle + 1) % 256; //0-255 fixed point angle
        mTimeCounter.Start(0.05);       //start timer again
    }

    CCanvas &sprite = *mSprites[shipItem.GetShipName()];
    int sx =kLineWidth*2+kRadius - sprite.GetWidth()/2;
    int sy =kDeltaY+kLineWidth+kRadius - sprite.GetHeight()/2;
    sprite.Draw(mCanvas, sx, sy, fixAngle << 16);

}


void CShipMenuInfo::DrawSquad(const CShipMenuItem& shipItem) {

    if(mVersus.GetMeleeType() == "Squad") {
        int width  =  18;
        int height =  18;
        for(int i = 0; i < mVersus.GetNbShips(mIndex); i++) {
            int nbPerRow = 5;
            int x = kLineWidth*3+(i%nbPerRow)*(3*width)/2;
            int y = mCanvas.GetHeight() - kLineWidth - 2 - height;
            if(i<5) y -= height+2; //top row
            mStatSprites[mVersus.GetShipType(mIndex, i)]->Draw(mCanvas,x,y);
        }
    }
}
