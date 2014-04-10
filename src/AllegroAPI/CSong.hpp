#ifndef CSONG_H
#define CSONG_H


#include <string>
#include <utility>

class CSong {

public:
  CSong(std::string name) : mName(std::move(name)) {}
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
