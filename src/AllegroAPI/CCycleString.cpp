#include "CCycleString.hpp"
#include "CFont.hpp"
#include "CMenuIconString.hpp"



CCycleString::CCycleString(const std::string &title, const strings_t &strings,
                           int max, int min):
  CCycleLeaf(title, max,min),
  mStrings(strings) {

}
