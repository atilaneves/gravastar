#include "CMenuNull.hpp"
#include "CMenuIconNull.hpp"


static CMenuIcon *icon;

CMenuNull::CMenuNull():
  CMenu(icon = new CMenuIconNull),
  mIcon(icon) {

}
