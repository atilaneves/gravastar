#ifndef CMENUNULL_H
#define CMENUNULL_H


#include "CMenu.hpp"
#include <memory>


class CMenuNull: public CMenu {

public:

  CMenuNull();


private:

  std::auto_ptr<CMenuIcon> mIcon;

};

#endif
