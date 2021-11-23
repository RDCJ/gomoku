#ifndef AI_H
#define AI_H
#include<queue>
#include<cstdlib>
#include<ctime>
#include "State.h"
#include "OnePlace.h"

using namespace std;

class AI
{
    public:
        AI(int color);
        OnePlace MinMaxSearch(State st);
        int trueAIValue(State st, int trueAIBest, int partnerBest);
        int partnerValue(State st, int trueAIBest, int partnerBest);

    private:
        int _myColor;
};

#endif // AI_H
