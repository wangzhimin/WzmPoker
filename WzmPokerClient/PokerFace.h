
#ifndef Poker_Face_h
#define Poker_Face_h

#include "d2d.h"

//����
class PokerFace
{
public:
    PokerFace(int num, ID2D1Bitmap* bitmap);

    inline ID2D1Bitmap* GetBitmap();

private:
    int value; //�Ƶ�����
    ID2D1Bitmap* pBitmap;

};

inline ID2D1Bitmap* PokerFace::GetBitmap()
{
    return pBitmap;
}


#endif

