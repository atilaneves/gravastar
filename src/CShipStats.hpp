#ifndef CSHIPSTATS_H
#define CSHIPSTATS_H


class CShip;


class CShipStats {

public:

  CShipStats(const CShip &ship);


private:

  const CShip& mShip;

};


#endif
