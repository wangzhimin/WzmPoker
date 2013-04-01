
#ifndef Poker_Box_h
#define Poker_Box_h

#include <d2d1.h>
#include "PokerFace.h"

#include <unordered_map>
#include <deque>
using namespace std;


class d2d;
//���ƺ��ӣ���ʵҲ���˿˹���
class PokerBox
{
public:
    PokerBox();

    void Initialize(d2d* g);
    void LoadBitmapByIDB(int IDB_Start, int IDB_End);
    void Cleanup();

    PokerFace GetNextPoker();

    void dump();

private:
    d2d* graphic;
    unordered_map<int, ID2D1Bitmap*> allPokers; //������λͼ��Դ
    deque<PokerFace> pokerFactory; //һ����
};

#endif

