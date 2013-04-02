
#ifndef Poker_Face_h
#define Poker_Face_h

#include "d2d.h"

//����
class PokerFace
{
public:
    PokerFace(int value, ID2D1Bitmap* bitmap);

    inline ID2D1Bitmap* GetBitmap();
    inline FLOAT GetWidth();

    int GetColor() { return Color; }
    int GetNumber() { return Number; }

private:
    int Color; //��ɫ����λ��, 1-����,2-÷��,3-����,4-����
    int Number; //�Ƶ�����, ʮλ�͸�λ

    ID2D1Bitmap* pBitmap; //ͼƬ
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

