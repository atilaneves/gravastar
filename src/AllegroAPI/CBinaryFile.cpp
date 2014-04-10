#include "CBinaryFile.hpp"
#include <stdio.h>
#include <stdlib.h>


CBinaryFile::CBinaryFile(const std::string &fileName) {

  FILE *fp=fopen(fileName.c_str(), "rb");
  if(fp==NULL) {
    fprintf(stderr, "\n*** Error: could not open %s ***\n\n",
	    fileName.c_str());
    exit(1);
  }

  int offset=0;
  fseek(fp, offset, SEEK_END);
  mLength = ftell(fp); //file size
  rewind(fp);

  mBuffer = (char*)malloc(mLength); //enough for whole file
  int bytesPerWord=1;
  fread(mBuffer, bytesPerWord, mLength, fp); //read file into buffer
  fclose(fp);

}


CBinaryFile::~CBinaryFile() {
  free(mBuffer);
}
