#ifndef CVECTOR_H
#define CVECTOR_H


#include <cmath>


template<typename T>
class CVector {

public:

  CVector(T x, T y):mX(x), mY(y) { }
  CVector(const CVector<float> &v):mX((T)v.GetX()), mY((T)v.GetY()) { }
  CVector(T theta):mX(std::cos(theta)), mY(std::sin(theta)) { }

  T     Angle(const CVector<T>& v) const;
  T     GetX()     const { return mX; }
  T     GetY()     const { return mY; }
  bool  PointsUp() const { return Theta() < 0.0;        }
  T     Radius2()  const { return mX*mX + mY*mY;        }
  T     Radius()   const { return std::sqrt(Radius2()); }
  void  SetTheta(T theta);
  void  Set(const CVector<T> &vec) { mX = vec.mX; mY = vec.mY; }
  void  SetX(T x)        { mX = x; }
  void  SetY(T y)        { mY = y; }
  T     Theta()    const;

        CVector<T>& operator+=(const CVector<T> &v);
        CVector<T>& operator-=(const CVector<T> &v);
        CVector<T>& operator*=(T scalar);
        CVector<T>& operator/=(T scalar);
  const CVector<T>  operator+(const CVector<T> &v) const;
  const CVector<T>  operator-(const CVector<T> &v) const;
  const         T   operator*(const CVector<T> &v) const;

  const CVector<T>  operator*(T scalar) const;
  const CVector<T>  operator/(T scalar) const;


private:

  T mX, mY;

};


template<typename T>
CVector<T>& CVector<T>::operator+=(const CVector<T> &v) {
  mX += v.mX;
  mY += v.mY;
  return *this;
}


template<typename T>
CVector<T>& CVector<T>::operator-=(const CVector<T> &v) {
  mX -= v.mX;
  mY -= v.mY;
  return *this;
}


template<typename T>
const CVector<T> CVector<T>::operator+(const CVector<T> &v) const {
  CVector<T> result(*this);
  result += v;
  return result;
}


template<typename T>
const CVector<T> CVector<T>::operator-(const CVector<T> &v) const {
  CVector<T> result(*this);
  result -= v;
  return result;
}

template<typename T>
CVector<T>& CVector<T>::operator*=(T scalar) {
  mX *= scalar;
  mY *= scalar;
  return *this;
}


template<typename T>
const CVector<T> CVector<T>::operator*(T scalar) const {
  CVector<T> result(*this);
  result *= scalar;
  return result;
}


template<typename T>
const CVector<T> operator*(T scalar, const CVector<T> &v) {
  CVector<T> result(v);
  result *= scalar;
  return result;
}


template<typename T>
CVector<T>& CVector<T>::operator/=(T scalar) {
  mX /= scalar;
  mY /= scalar;
  return *this;
}


template<typename T>
const CVector<T> CVector<T>::operator/(T scalar) const {
  CVector<T> result(*this);
  result /= scalar;
  return result;
}


template<typename T>
const CVector<T> operator/(T scalar, const CVector<T> &v) {
  CVector<T> result(v);
  result /= scalar;
  return result;
}


template<typename T>
const T CVector<T>::operator*(const CVector<T> &v) const {
  return mX * v.mX + mY * v.mY;
}


template<typename T>
void CVector<T>::SetTheta(T theta) {
  mX = std::cos(theta);
  mY = std::sin(theta);
}



template<typename T>
T CVector<T>::Angle(const CVector<T>& v) const {
  float theta = std::acos((*this * v) / (Radius() * v.Radius()));
  if(theta < 0) theta += 2*M_PI;
  return theta;
}


template<typename T>
T CVector<T>::Theta() const {
  T theta = atan2(mY, mX);
  if(theta < 0)      theta += 2*M_PI;
  if(theta > 2*M_PI) theta -= 2*M_PI;
  return theta;
}


#endif
