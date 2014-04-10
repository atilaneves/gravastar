#ifndef CCONTROL_TYPE_MENU_H
#define CCONTROL_TYPE_MENU_H


#include "CCycleStringEnter.hpp"
class CRedefineMenu;
class CPilotInputOptions;


class CControlTypeMenu: public CCycleStringEnter {

public:

  CControlTypeMenu(CRedefineMenu &redefine, 
		   const CPilotInputOptions& options,
		   const std::string &title,
		   const strings_t& strings,
		   int max, int min = 1);


private:

  CRedefineMenu& mRedefine;

  virtual void Run(CRootMenu &rootMenu);


};


#endif
