#include "State.h"

State::State(int arr[15][15], int lastx, int lasty, int lastColor)
{
    _depth = 0;
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
            _arr[i][j] = arr[i][j];

    _lastPlace.x = lastx;
    _lastPlace.y = lasty;
    _lastPlace.color = lastColor;
    count_score(1);
    count_score(-1);
}


State::State(const State &other)
{
    for (int i=0; i<15; i++)
        for (int j=0; j<15; j++)
            _arr[i][j] = other._arr[i][j];
    _lastPlace = other._lastPlace;
    w_score = other.w_score;
    b_score = other.b_score;
}


State State::placeChess(int x, int y, int color)
{
    State newState(*this);
    newState._depth++;
    newState._arr[x][y] = color;
    newState._lastPlace.x = x;
    newState._lastPlace.y = y;
    newState._lastPlace.color = color;
    newState.count_score(1);
    newState.count_score(-1);
    return newState;
}


bool State::check_ard(int x, int y)
{
    if (_arr[x][y] != 0) return false;
    for(int i=0; i<8; i++)
    {
        int xx = x + drct[i][0], yy = y + drct[i][1];
        if (xx<0 || xx>14 || yy<0 || yy>14) continue;
        if (_arr[xx][yy] == 1 || _arr[xx][yy] == -1) return true;
    }
    return false;
}


int State::count_string_score(string str, char color)
{
    int score = 0;
    int head = 0, tail;
    //情况一：连珠 o, oo, ooo, oooo, ooooo
    while (head<str.length())
    {
        //寻找连续的一段
        while (head<str.length() && str[head] != color) head++;
        if (head >= str.length()) break;
        tail = head + 1;
        while (tail<str.length() && str[tail] == color) tail++;
        //计算长度和空位
        int len = tail - head, empty_num = 2;
        if (head == 0 || str[head-1] != 'o') empty_num--;//左边非空
        if (tail>=str.length() || str[tail] != 'o') empty_num--;//右边非空
        if (len>5) len = 5;
        score += succ_score[len-1][empty_num];
        head = tail;
    }
    //情况二：补位 o o , oo o , oo oo , oo ooo 等
    for (int i=0; i<str.length(); i++)
        if (str[i] == 'o')
        {
            int count = 0;
            //左边
            int k = 1;
            while (i-k>=0 && str[i-k] == color) k++;
            if (k == 1) continue;
            count += (k-1);
            //右边
            k = 1;
            while (i+k<str.length() && str[i+k] == color) k++;
            if (k == 1) continue;
            count += (k-1);

            score += adtn_score[count];
        }
    return score;
}


void State::count_score(int color)
{
    int score = 0;
    char col = to_char(color);
    for (int i=0; i<15; i++)//列得分
    {
        string crnt_string = "";
        for (int j=0; j<15; j++) crnt_string += to_char(_arr[i][j]);
        score += count_string_score(crnt_string, col);
    }
    for (int j=0; j<15; j++)//行得分
    {
        string crnt_string = "";
        for (int i=0; i<15; i++) crnt_string += to_char(_arr[i][j]);
        score += count_string_score(crnt_string, col);
    }
    for (int i=0; i<15; i++)//RT->LB得分（第一部分）
    {
        int x = i, y = 0;
        string crnt_string = "";
        while (x>=0 && x<=14 && y>=0 && y<=14)
        {
            crnt_string += to_char(_arr[x][y]);
            x--; y++;
        }
        score += count_string_score(crnt_string, col);
    }
    for (int i=1; i<15; i++)//RT->LB得分（第二部分）
    {
        int x = 14, y = i;
        string crnt_string = "";
        while (x>=0 && x<=14 && y>=0 && y<=14)
        {
            crnt_string += to_char(_arr[x][y]);
            x--; y++;
        }
        score += count_string_score(crnt_string, col);
    }
    for (int i=0; i<15; i++)//LT->RB得分（第一部分）
    {
        int x = i, y = 0;
        string crnt_string = "";
        while (x>=0 && x<=14 && y>=0 && y<=14)
        {
            crnt_string += to_char(_arr[x][y]);
            x++; y++;
        }
        score += count_string_score(crnt_string, col);
    }
    for (int i=1; i<15; i++)//LT->RB得分（第二部分）
    {
        int x = 0, y = i;
        string crnt_string = "";
        while (x>=0 && x<=14 && y>=0 && y<=14)
        {
            crnt_string += to_char(_arr[x][y]);
            x++; y++;
        }
        score += count_string_score(crnt_string, col);
    }
    if (color == 1) b_score = floor(DEFENCE_LV * score);
    else w_score = score;
}


char State::to_char(int color)
{
    if (color == 1) return 'b';
    else if (color == -1) return 'w';
    else return 'o';
}


bool State::judge_one(int x, int y, int color)//判断此棋子是否连5
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


bool State::if_end()
{
    if (this->_depth >= SEARCH_DEPTH) return true;
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
            if (judge_one(i, j, crnt_color)) return true;
        }
    return if_stalemate;
}

