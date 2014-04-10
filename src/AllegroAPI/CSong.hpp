#ifndef CSONG_H
#define CSONG_H


#include <string>


class CSong {

public:

  CSong(const std::string& name):mName(name) { }
  virtual ~CSong() { }
  virtual void Adjust(bool loop = true) = 0;
  const std::string& GetName() const { return mName; }
  virtual void PlayLoop() = 0;
  virtual bool Poll() = 0;
  virtual void Stop() = 0;


private:

  std::string mName;

};

#endif
