#include "CSpriteVector.hpp"
#include "CGravSprite.hpp"
#include <stdio.h>


CSpriteVector::CSpriteVector():
    mDeleteSprites(true) {

}


CSpriteVector::CSpriteVector(const CSpriteVector &vec):
    mDeleteSprites(false), mSprites(vec.mSprites) {

}


CSpriteVector::CSpriteVector(int nbCopies, const CGravSprite* sprite):
    mDeleteSprites(false), mSprites(nbCopies, sprite) {
}


CSpriteVector::~CSpriteVector() {
    if(!mDeleteSprites) return;
    for (auto &elem : mSprites)
      delete elem;
}


void CSpriteVector::push_back(CGravSprite *sprite) {
    if(!mDeleteSprites)
        fprintf(stderr,
                "called CSpriteVector::push_back w/ mDeleteSprites false!\n");
    mSprites.push_back(sprite);
}


const CGravSprite* CSpriteVector::operator[](unsigned int index) const {
    return mSprites[index];
}


CSpriteVector& CSpriteVector::operator=(const CSpriteVector &vec) {
    if(*this == vec) return *this; //self assignment
    mSprites = vec.mSprites;
    return *this;
}


bool CSpriteVector::operator==(const CSpriteVector &vec) const {
    return mSprites == vec.mSprites;
}
