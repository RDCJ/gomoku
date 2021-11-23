#include "Setting.h"

int EDGE_SIZE = 30;
int GRID_SIZE = 53;
int BOARD_SIZE = 800;
int INF = 1000000;
int SEARCH_DEPTH = 10;
double DEFENCE_LV = 2.5;
int drct[8][2] = {
                            {0, -1}, {0, 1},
                            {1, 0}, {-1, 0},
                            {-1, -1}, {1, 1},
                            {1, -1}, {-1, 1}
                          };

int succ_score[5][3] = {
                                    {0, 0, 5},
                                    {0, 10, 15},
                                    {0, 20, 500},
                                    {0, 5000, 10000},
                                    {100000, 100000, 100000},
                                    };

int adtn_score[9] = {0, 0, 1, 100, 4000, 4500, 5000, 5500, 6000};
