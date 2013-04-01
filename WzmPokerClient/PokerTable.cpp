
#include "PokerTable.h"

#include "d2d.h"

void PokerTable::Add(PokerFace& poker)
{
    pokerFaces.push_back(poker);
}

void PokerTable::Show(d2d* graphic)
{
    FLOAT left = 20;
    FLOAT top = 300;

    FLOAT deltaX = 20;
    FLOAT deltaY = 0;
    for (auto poker : pokerFaces)
    {
        graphic->ShowBitmap(poker.GetBitmap(), left, top);

        left += deltaX;
        top  += deltaY;
    }
}

