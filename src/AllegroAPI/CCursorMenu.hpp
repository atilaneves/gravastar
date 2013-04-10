#ifndef CCURSOR_MENU_HPP_
#define CCURSOR_MENU_HPP_

class CSprite;
#include "CMenuCursor.hpp"

template<class T>
class CCursorMenu: public T {
public:

    template<typename... ARGS>
    CCursorMenu(const CSprite *cursorSprite, ARGS... args):T(args...), mCursor(*this, cursorSprite) { }


private:

    CMenuCursor mCursor;

};

#endif
