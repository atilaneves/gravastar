#ifndef CRADAR_H
#define CRADAR_H


#include "CCanvas.hpp"
#include "CVector2.hpp"
#include "CScreenPos.hpp"
#include <vector>
class CPilot;


typedef std::vector<CPilot*> pilots_t;


class CRadar {

public:

    enum { kRadius = 25 };

    CRadar();

    void Draw(CBitmap &bmp, int x, int y, const pilots_t &pilots,
              const pilots_t& humans,
              const CScreenPos &centrePos);


private:

    CCanvas mCanvas;

    CVector2 CalcRadiusAngle(const CPilot &pilot, const CVector2& centre);

};


#endif
