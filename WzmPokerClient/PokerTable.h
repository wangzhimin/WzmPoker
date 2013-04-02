
#ifndef Poker_Table_h
#define Poker_Table_h

#include "PokerFace.h"

#include <vector>
using namespace std;

enum T_Pattern
{
    High_Card,
    One_Pair,
    Two_Pair,
    Three_Kind,
    Straight, //˳��
    Flush,    //ͬ��
    Full_House, //��«��3+2
    Four_Kind,
    Straight_Flush, //ͬ��˳
    Royal_Straight_Flush //�ʼ�ͬ��˳
};

class d2d;
class PokerTable
{
public:
    void Add(PokerFace& poker);
    void Show(d2d* graphic);
private:
    void ShowPokersOnTable(d2d* g);
    T_Pattern GetPokerPattern();
    wstring GetPatternName(T_Pattern& pattern);

    vector<PokerFace> pokerFaces;
};

#endif

