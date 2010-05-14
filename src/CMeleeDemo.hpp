#ifndef CMELEEDEMO_H
#define CMELEEDEMO_H


#include "CMelee.hpp"
class CSound;


class CMeleeDemo:public CMelee {

public:

  CMeleeDemo(const CGravOptions &options);
  virtual ~CMeleeDemo();


private:

  virtual int  GetWinner();
  virtual bool IsGameOver();
  CGravOptions RandomOptions(CClientOptions clientOptions) const;

};

#endif
