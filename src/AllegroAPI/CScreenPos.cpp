#include "CScreenPos.hpp"


CScreenPos VectorToScreenPos(const CVector2& vec) {
    return { static_cast<int>(vec.GetX()), static_cast<int>(vec.GetY()) };
}

CVector2 ScreenPosToVector(const CScreenPos& pos) {
    return { static_cast<float>(pos.GetX()), static_cast<float>(pos.GetY()) };
}
