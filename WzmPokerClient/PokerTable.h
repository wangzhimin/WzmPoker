
#ifndef Poker_Table_h
#define Poker_Table_h

#include "PokerFace.h"

#include <vector>
using namespace std;

class d2d;
class PokerTable
{
public:
    void Add(PokerFace& poker);
    void Show(d2d* graphic);
private:
    void ShowPokersOnTable(d2d* g);

    vector<PokerFace> pokerFaces;
};

#endif

