
#include "PokerBox.h"

#include "d2d.h"
#include "resource.h"

#include <ctime> 
#include <algorithm>
using namespace std;


PokerBox::PokerBox()
    :graphic(nullptr)
{
}

void PokerBox::Initialize(d2d* g)
{
    graphic = g;

    LoadBitmapByIDB(IDB_PNG102, IDB_PNG114);
    LoadBitmapByIDB(IDB_PNG202, IDB_PNG214);
    LoadBitmapByIDB(IDB_PNG302, IDB_PNG314);
    LoadBitmapByIDB(IDB_PNG402, IDB_PNG414);

    srand( (unsigned)time(NULL) ); //�����漴�������������� 
    random_shuffle(pokerFactory.begin(), pokerFactory.end());
}

void PokerBox::LoadBitmapByIDB(int IDB_Start, int IDB_End)
{
    if (graphic == nullptr)
    {
        return;
    }

    for (int index = IDB_Start; index <= IDB_End; ++index)
    {
        ID2D1Bitmap* pBitmap = graphic->CreateBitmapFromResource(index, 126, 173);
        if (pBitmap != nullptr)
        {
            allPokers[index] = pBitmap;

            //��ʼ��һ����
            PokerFace face(index, pBitmap);
            pokerFactory.push_back(face);
        }
    }
}

void PokerBox::Cleanup()
{
    if (!allPokers.empty())
    {
        for(auto& value : allPokers)
        {
            if (value.second != nullptr)
            {
                SafeRelease(value.second);
            }
        }

        allPokers.clear();
    }
}

//��һ����
PokerFace PokerBox::GetNextPoker()
{
    PokerFace& onePoker = pokerFactory.front();
    pokerFactory.pop_front();

    return onePoker;
}


void PokerBox::dump()
{
    FLOAT left = 20;
    FLOAT top = 300;

    FLOAT deltaX = 20;
    FLOAT deltaY = 0;
    for(auto it = allPokers.begin(); it != allPokers.end(); ++it)
    {
        if ((*it).second != nullptr)
        {
            graphic->ShowBitmap((*it).second, left, top);

            left += deltaX;
            top  += deltaY;
        }
    }
}
