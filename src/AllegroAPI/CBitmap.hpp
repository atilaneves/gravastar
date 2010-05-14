#ifndef CBITMAP_H
#define CBITMAP_H


#include "CColour.hpp"
#include <allegro.h>
typedef BITMAP BitmapImp_t;


class CBitmap {

public:

  CBitmap(BitmapImp_t *data);
  ~CBitmap();
  
  void         Blit(CBitmap &bitmap, int x0, int y0, int x1, int y1,
		    int w, int h) const ;
  void         Blit(CBitmap &bitmap, int x1 = 0, int y1 = 0) const;
  void         Clear(int colour = CColour::GetBlack());
  BitmapImp_t *CopyBitmap(void *data);
  void         Draw(const CBitmap &bitmap, int x=0, int y=0, int fixAngle=0);
  void         Flip(int x=0, int y=0) const;
  void        *GetData() const              { return mData;        }
  int          GetHeight() const            { return mData->h;     }
  int          GetMask() const;
  int          GetPixel(int x, int y) const { return getpixel(mData, x, y); }
  int          GetWidth()  const            { return mData->w;     }
  void         MaskBlit(CBitmap &bitmap, int x0, int y0, int x1, int y1,
			int w, int h) const;
  void         PutPixel(int x, int y, int c) { putpixel(mData, x, y, c); }
  void         StretchBlit(CBitmap &bitmap, int x, int y, int w, int h) const;


  
protected:
  
  BitmapImp_t *mData; //this is where it's at
    
};


#endif
