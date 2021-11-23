#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include<QImage>
#include<QPainter>
#include<QString>
#include<QFont>
#include<QFontMetrics>
#include<cstring>

#include "Setting.h"
#include "AI.h"
#include "OnePlace.h"
#include "State.h"

class Chessboard
{
    public:
        Chessboard();
        void begin();
        void show(QPainter* painter);
        void show_end_message(QPainter* painter);

        void placeChess(int x, int y);
        void AI_Place(State st);
        void Player_Place(int x, int y);

        int getState() const {return _state;}
        bool judge_one(int x, int y, int color);//判断此棋子是否连5
        void judge();//判断整个棋盘

    private:
        QImage _boardPic, _white, _black;//白棋：-1，黑棋：1
        int _arr[15][15];
        int nowPlaceColor;//现在要落子的颜色
        int _state;//-2为未开始，-1为白棋胜利，1为黑棋胜利， 0为游戏继续， 2为和局
        int _chessNum;
        AI _myAI;
};

#endif // CHESSBOARD_H
