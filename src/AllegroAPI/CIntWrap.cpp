#include "CIntWrap.hpp"


CIntWrap::CIntWrap(int max,int min):
  mMin(min), mMax(max), mValue(min) {

  //max is open, min is closed
}


CIntWrap& CIntWrap::operator++() {
  Increment();
  return *this;
}


CIntWrap& CIntWrap::operator--() {
  Decrement();
  return *this;
}


CIntWrap CIntWrap::operator++(int) {
  Increment();
  return *this;
}


CIntWrap CIntWrap::operator--(int) {
  Decrement();
  return *this;
}


void CIntWrap::Increment() {
  mValue++;
  KeepInBounds();
}


void CIntWrap::Decrement() {
  mValue--;
  KeepInBounds();
}



CIntWrap& CIntWrap::operator+=(int amount) {
  mValue += amount;
  KeepInBounds();
  return *this;
}


CIntWrap& CIntWrap::operator-=(int amount) {
  mValue -= amount;
  KeepInBounds();
  return *this;
}


CIntWrap& CIntWrap::operator=(int value) {
  mValue = value;
  KeepInBounds();
  return *this;
}


void CIntWrap::KeepInBounds() {
  while(mValue < mMin) mValue += mMax - mMin + 1;
  while(mValue > mMax) mValue -= mMax - mMin + 1;
}
