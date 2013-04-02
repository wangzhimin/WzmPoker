
#include "PokerFace.h"

PokerFace::PokerFace(int value, ID2D1Bitmap* bitmap)
    :Color(value/100),
     Number(value%100),
     pBitmap(bitmap)
{

}

