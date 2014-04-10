#ifndef CMENUINPUTPILOT_H
#define CMENUINPUTPILOT_H


#include "CMenuInput.hpp"
#include "CPilotInput.hpp"
#include <memory>
#include <vector>
class CClientOptions;
class CMenuInputBot;

class CMenuInputPilot: public CMenuInput {

public:

  CMenuInputPilot(int index, const CClientOptions& options);
  virtual ~CMenuInputPilot();

  void AddBot(CMenuInputBot* bot);

  virtual bool Up() override;
  virtual bool Down() override;
  virtual bool Left() override;
  virtual bool Right() override;
  virtual bool Select() override;
  virtual bool Cancel() override;

private:
  std::unique_ptr<CPilotInput> mInput;
  std::vector<CMenuInputBot*> mBots;
  bool mUp, mDown, mLeft, mRight, mSelect, mCancel;

};

#endif
