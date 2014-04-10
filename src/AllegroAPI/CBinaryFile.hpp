#ifndef CBINARY_FILE_H
#define CBINARY_FILE_H


#include <string>


class CBinaryFile {

public:

  CBinaryFile(const std::string &fileName);
  ~CBinaryFile();

  char *GetData()   const { return mBuffer; }
  long  GetLength() const { return mLength; }


private:

  char *mBuffer;
  long  mLength;

};


#endif
