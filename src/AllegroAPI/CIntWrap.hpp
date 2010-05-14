#ifndef CINTRWAP_H
#define CINTRWAP_H


class CIntWrap {

public:

  CIntWrap(int max, int min = 0);

  CIntWrap& operator=(int value);
  CIntWrap& operator++();
  CIntWrap& operator--();
  CIntWrap  operator++(int);
  CIntWrap  operator--(int);
  CIntWrap& operator+=(int amount);
  CIntWrap& operator-=(int amount);

  int  GetMax() const { return mMax; }
  int  GetMin() const { return mMin; }
  void SetMax(int m) { mMax = m; }
  void SetMin(int m) { mMin = m; }
  int  ToInt() const { return mValue; }


private:

  int mMin, mMax, mValue;

  void KeepInBounds();
  void Increment();
  void Decrement();

};

#endif
