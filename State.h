#ifndef STATE_H
#define STATE_H
#include<string>
#include<cmath>
#include "Setting.h"
#include "OnePlace.h"
using namespace std;

class State
{
    public:
        State(int arr[15][15], int lastx, int lasty, int lastColor);
        State(const State &other);
        State placeChess(int x, int y, int color);
        bool check_ard(int x, int y);

        OnePlace getLastPlace() const {return _lastPlace;}
        int getDepth() const {return _depth;}


        int count_string_score(string str, char color);
        void count_score(int color);
        double priority_score() const {return w_score-b_score;}

        char to_char(int color);

        bool judge_one(int x, int y, int color);//判断此棋子是否连5
        bool if_end();//判断整个棋盘

    private:
        int _depth;
        int _arr[15][15];
        int w_score, b_score;
        OnePlace _lastPlace;
};

#endif // STATE_H
