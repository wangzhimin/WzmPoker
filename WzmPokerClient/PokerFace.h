
#ifndef Poker_Face_h
#define Poker_Face_h

#include "d2d.h"

//牌面
class PokerFace
{
public:
    PokerFace(int value, ID2D1Bitmap* bitmap);

    inline ID2D1Bitmap* GetBitmap();
    inline FLOAT GetWidth();

    int GetColor() { return Color; }
    int GetNumber() { return Number; }

private:
    int Color; //花色，百位数, 1-方块,2-梅花,3-红桃,4-黑桃
    int Number; //牌的数字, 十位和个位

    ID2D1Bitmap* pBitmap; //图片
};

inline ID2D1Bitmap* PokerFace::GetBitmap()
{
    return pBitmap;
}

inline FLOAT PokerFace::GetWidth()
{
    if (pBitmap == nullptr)
    {
        return 0;
    }

    return pBitmap->GetSize().width;
}


#endif

