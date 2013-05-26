#ifndef CRADAR_H
#define CRADAR_H


#include "CCanvas.hpp"
#include "CVector2.hpp"
#include "CScreenPos.hpp"
#include "CDisplayPilot.hpp"
#include <vector>
class CPilot;


class CRadar {

public:

    enum { kRadius = 25 };
    using pilots_t = std::vector<CDisplayPilot>;

    CRadar();

    void Draw(CBitmap &bmp, int x, int y, const pilots_t &pilots,
              const pilots_t& humans,
              const CScreenPos &centrePos);


private:

    CCanvas mCanvas;

    CVector2 CalcRadiusAngle(const CDisplayPilot &pilot, const CVector2& centre) const;
};


#endif
