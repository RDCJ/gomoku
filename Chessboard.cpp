#include "Chessboard.h"

Chessboard::Chessboard(): _myAI(-1)
{
    _state = -2;
    nowPlaceColor = 1;//黑棋先下
    _boardPic.load(":/image/chessboard.png");
    _white.load(":/image/white.png");
    _black.load(":/image/black.png");
    //图片源于QQ游戏五子棋
}

void Chessboard::begin()
{
    _state = 0;
    nowPlaceColor = 1;
    _chessNum = 0;
    memset(_arr, 0, sizeof (_arr));
}


void Chessboard::placeChess(int x, int y)
{
    if (_state == 0 && _arr[x][y] == 0)
    {
        _chessNum++;
        _arr[x][y] = nowPlaceColor;
        nowPlaceColor = -nowPlaceColor;
        judge();
    }
}


void Chessboard::AI_Place(State st)
{
    /*if (_chessNum <= 1)//AI第一步先随机落子
    {
        int x = st.getLastPlace().x, y = st.getLastPlace().y;
        srand((int)time(0));
        int k = rand()%8;
        int xx = x + drct[k][0], yy = y + drct[k][1];
        while(xx<0 || xx>14 || yy<0 || yy>14)
        {
            k = rand()%8;
            xx = x + drct[k][0]; yy = y + drct[k][1];
        }
        placeChess(xx, yy);
        return;
    }*/

    OnePlace ai_choice = _myAI.MinMaxSearch(st);
    placeChess(ai_choice.x, ai_choice.y);
    return;
}


void Chessboard::Player_Place(int x , int y)
{
    if (_arr[x][y] == 0 && nowPlaceColor == 1)
    {
        placeChess(x, y);
        if (_state == 0)//如果没有结束则轮到AI下
        {
            State crnt_st(_arr, x, y, 1);//将当前局面转换成一个节点
            AI_Place(crnt_st);
        }
    }
}


bool Chessboard::judge_one(int x, int y, int color)//判断此棋子是否连5
{
    for (int i=0; i<8; i++)//枚举8个方向
    {
        int xx = x, yy = y;
        bool flag = true;
        for (int j=1; j<=4 && flag==true; j++)//判断此方向上的后4个棋子的颜色
        {
            xx += drct[i][0]; yy += drct[i][1];
            if (xx<0 || xx>14 || yy<0 || yy>14) flag = false;//超出边界或者颜色不符
            else if (_arr[xx][yy] != color) flag = false;
        }
        if (flag) return true;
    }
    return false;
}


void Chessboard::judge()
{
    bool if_stalemate = true;
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)//枚举棋盘上的点
        {
            int crnt_color = _arr[i][j];
            if (crnt_color == 0)
            {
                if_stalemate = false;//有空位则不为和局
                continue;
            }
            if (judge_one(i, j, crnt_color))
            {
                _state = crnt_color;
                return;
            }
        }
    if (if_stalemate == true) _state = 2;
}


void Chessboard::show(QPainter* painter)
{
    if (_state != -2)
    {
        painter->drawImage(0, 0, _boardPic);
        for (int i=0; i<15; i++)
            for (int j=0; j<15; j++)
            {
                int x = EDGE_SIZE + i * GRID_SIZE;
                int y = EDGE_SIZE + j * GRID_SIZE;
                if (_arr[i][j] == -1)
                    painter->drawImage(x - 24, y - 24, _white);
                if (_arr[i][j] == 1)
                    painter->drawImage(x - 24, y - 24, _black);
            }
    }
    if (_state !=-2 && _state != 0)
        show_end_message(painter);
}


void Chessboard::show_end_message(QPainter *painter)
{
    QFont font("Microsoft YaHei", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    painter->setFont(font);
    QString message;
    switch (_state)
    {
        case -1:
            message = "白棋获胜";
            break;
        case 1:
            message = "黑棋获胜";
            break;
        case 2:
            message = "和棋";
            break;
    };
    double textWidth = fm.width(message);
    painter->drawText(BOARD_SIZE/2 - textWidth/2, 60, message);
    painter->resetTransform();
}
