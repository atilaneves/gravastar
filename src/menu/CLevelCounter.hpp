#ifndef CLEVEL_COUNTER_H
#define CLEVEL_COUNTER_H

#include "CCycleString.hpp" //strings_t

class CLevelCounter {

public:

    CLevelCounter();

    int GetNbLevels()    const { return mNbLevels; }
    int GetRandomLevel() const;
    strings_t GetLevelTitles() const;


private:

  int mNbLevels;

  static int FindNbLevels();

};

#endif
