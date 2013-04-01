
#ifndef Poker_Box_h
#define Poker_Box_h

#include <d2d1.h>

#include <unordered_map>
using namespace std;


class d2d;
//发牌盒子，其实也是扑克工厂
class PokerBox
{
public:
    PokerBox();

    void Initialize(d2d* g);
    void LoadBitmapByIDB(int IDB_Start, int IDB_End);
    void Cleanup();

    void dump();

private:
    d2d* graphic;
    unordered_map<int, ID2D1Bitmap*> allPokers;
};

#endif

