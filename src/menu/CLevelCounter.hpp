#ifndef CLEVEL_COUNTER_H
#define CLEVEL_COUNTER_H



class CLevelCounter {

public:

  CLevelCounter();

  int GetNbLevels()    const { return mNbLevels; }
  int GetRandomLevel() const;


private:

  int mNbLevels;

  static int FindNbLevels();

};

#endif
