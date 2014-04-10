#ifndef CMELEEDEMO_H
#define CMELEEDEMO_H


#include "CMeleeOnServer.hpp"


class CMeleeDemo:public CMeleeOnServer {

public:

  CMeleeDemo(const CGravOptions &options);
  virtual ~CMeleeDemo();


private:
  virtual int GetWinner() override;
  virtual bool IsGameOver() override;
  CGravOptions RandomOptions(CClientOptions clientOptions) const;

};

#endif
