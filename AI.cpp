#include "AI.h"


AI::AI(int color)
{
    _myColor = color;
}


OnePlace AI::MinMaxSearch(State st)
{
    int ansValue = -INF;
    OnePlace ans;

    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
        {
            if (st.check_ard(i, j) == false) continue;
            State child_st = st.placeChess(i, j, _myColor);
            int child_value = partnerValue(child_st, -INF, INF);
            if (child_value > ansValue)
            {
                ansValue = child_value;
                ans = child_st.getLastPlace();
            }
        }
    return ans;
}


int AI::trueAIValue(State st, int trueAIBest, int partnerBest)
{
    if (st.if_end()) return st.priority_score();
    int max = -INF;
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
        {
            if (st.check_ard(i, j) == false) continue;
            State child_st = st.placeChess(i, j, -st.getLastPlace().color);
            int child_value = partnerValue(child_st, trueAIBest, partnerBest);
            if (child_value > max) max = child_value;
            if (max > partnerBest) return max;
            if (child_value > trueAIBest) trueAIBest = child_value;
        }
    return max;
}


int AI::partnerValue(State st, int trueAIBest, int partnerBest)
{
    if (st.if_end()) return st.priority_score();
    int min = INF;
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
        {
            if (st.check_ard(i, j) == false) continue;
            State child_st = st.placeChess(i, j, -st.getLastPlace().color);
            int child_value = trueAIValue(child_st, trueAIBest, partnerBest);
            if (child_value < min) min = child_value;
            if (min < trueAIBest) return min;
            if (child_value < partnerBest) partnerBest = child_value;
        }
    return min;
}
