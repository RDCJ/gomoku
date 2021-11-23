#ifndef SETTING_H
#define SETTING_H

extern int EDGE_SIZE;//边框像素大小
extern int GRID_SIZE;//每一格的像素大小
extern int BOARD_SIZE;//棋盘边长
extern int drct[8][2];//八个方向的坐标变换值
extern int succ_score[5][3];//各种情况的得分
extern int adtn_score[9];//额外的得分
extern int INF;
extern int SEARCH_DEPTH;//限制搜索深度
extern double DEFENCE_LV;//AI的防御倾向
#endif // SETTING_H
