#ifndef CSCREENPOS_H
#define CSCREENPOS_H

#include "CVector.hpp"
#include "CVector2.hpp"

typedef CVector<int> CScreenPos;
CScreenPos VectorToScreenPos(const CVector2& vec);
CVector2 ScreenPosToVector(const CScreenPos& pos);

#endif
