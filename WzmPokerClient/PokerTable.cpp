
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
}

void PokerTable::ShowPokersOnTable(d2d* g)
{
    FLOAT left = 20;
    FLOAT top = 300;

    FLOAT deltaX = 20;
    FLOAT deltaY = 0;
    for (auto poker : pokerFaces)
    {
        g->ShowBitmap(poker.GetBitmap(), left, top);

        left += deltaX;
        top  += deltaY;
    }
}

