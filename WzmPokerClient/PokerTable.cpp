
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

        left += deltaX + face.GetWidth(); //����һ������+һ����϶
        top  += deltaY;
    }
}

//��5�������жϳ���ʲô����
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
        return L"����";

    case One_Pair:
        return L"һ��";

    case Two_Pair:
        return L"����";

    case Three_Kind:
        return L"����";

    case Straight:
        return L"˳��";

    case Flush:
        return L"ͬ��";

    case Full_House:
        return L"��«";

    case Four_Kind:
        return L"����"; //��֧

    case Straight_Flush:
        return L"ͬ��˳";

    case Royal_Straight_Flush:
        return L"�ʼ�ͬ��˳";
    default:
        break;
    }
}
