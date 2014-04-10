#ifndef CSPRITEVECTOR_H
#define CSPRITEVECTOR_H


class CGravSprite;
#include <vector>


class CSpriteVector {

public:

  CSpriteVector();
  CSpriteVector(int nbCopies, const CGravSprite* sprite);
  CSpriteVector(const CSpriteVector &vec);
  ~CSpriteVector();

  void push_back(CGravSprite* sprite);
  int  GetNbSprites() const { return int(mSprites.size()); }
  void SetDeleteSprites(bool d) { mDeleteSprites = d; }

  const CGravSprite* operator[](unsigned int index) const;
  CSpriteVector&     operator=(const CSpriteVector &vec);
  bool               operator==(const CSpriteVector &vec) const;


private:

  bool mDeleteSprites;
  std::vector<const CGravSprite*> mSprites;


};


#endif
