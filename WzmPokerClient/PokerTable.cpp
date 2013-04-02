
#include "PokerTable.h"

#include "d2d.h"

//往桌面上发一张牌
void PokerTable::Add(PokerFace& poker)
{
    pokerFaces.push_back(poker);
}

//显示桌面
void PokerTable::Show(d2d* graphic)
{
    ShowPokersOnTable(graphic);

    D2D1_RECT_F pos = {100, 100, 300, 300};

    T_Pattern pattern = GetPokerPattern();
    wstring text = GetPatternName(pattern);

    graphic->ShowText( text, pos);
}

void PokerTable::ShowPokersOnTable(d2d* g)
{
    FLOAT left = 20;
    FLOAT top = 300;

    FLOAT deltaX = 10;
    FLOAT deltaY = 0;
    for (auto face : pokerFaces)
    {
        g->ShowBitmap(face.GetBitmap(), left, top);

        left += deltaX + face.GetWidth(); //向右一个牌面+一个空隙
        top  += deltaY;
    }
}

//从5张牌中判断出是什么牌型
T_Pattern PokerTable::GetPokerPattern()
{
    if (pokerFaces[0].GetColor() == pokerFaces[1].GetColor() &&
        pokerFaces[1].GetColor() == pokerFaces[2].GetColor() &&
        pokerFaces[2].GetColor() == pokerFaces[3].GetColor() &&
        pokerFaces[3].GetColor() == pokerFaces[4].GetColor() &&
        pokerFaces[4].GetColor() == pokerFaces[5].GetColor())
    {
        return Flush;
    }

    return High_Card;
}

wstring PokerTable::GetPatternName(T_Pattern& pattern)
{
    switch (pattern)
    {
    case High_Card:
        return L"高牌";

    case One_Pair:
        return L"一对";

    case Two_Pair:
        return L"两对";

    case Three_Kind:
        return L"三条";

    case Straight:
        return L"顺子";

    case Flush:
        return L"同花";

    case Full_House:
        return L"葫芦";

    case Four_Kind:
        return L"四条"; //铁支

    case Straight_Flush:
        return L"同花顺";

    case Royal_Straight_Flush:
        return L"皇家同花顺";
    default:
        break;
    }
}
