
#include "PokerTable.h"

#include "d2d.h"

//�������Ϸ�һ����
void PokerTable::Add(PokerFace& poker)
{
    pokerFaces.push_back(poker);
}

//��ʾ����
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

