//
//  Bomb Enemy.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/23.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Bomb Enemy
///@author  zhao wei
///@date    2016.08.23
///@version 1.0 TLE

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution_v1_0 {
public:
    ///@brief   给定一个二维棋盘，其中E表示敌人，W表示墙，0表示空位，计算出能够杀死的最大敌人数。炸弹有且仅有一枚，只能放在空位上，其能够消灭所在行和列上的所有敌人，但是会被墙挡住
    ///@param   grid    棋盘
    ///@return  返回杀死的最大敌人数
    ///@note    1. 枚举
    //          2. 对于所有空位进行遍历，找到能够杀死的最大敌人数
    //          3. 时间复杂度为O(m*n*(m + n）)，空间复杂度为O(1)，其中m和n分别是行列数
    //          4. TLE
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty())    return 0;
        int rslt = 0;
        int row = grid.size(), col = grid[0].size();
        for (int i = 0; i != row; i++) {
            for (int j = 0; j != col; j++) {
                if (grid[i][j] == 'W' || grid[i][j] == 'E') continue;
                else    rslt = max(rslt, killedEnemies(i, j, grid));
            }
        }
        return rslt;
    }
    
    ///@brief   计算炸弹在指定位置能够杀死的敌人数
    ///@param   row, col    炸弹位置
    ///@param   grid        棋盘
    ///@return  返回杀死的敌人数
    int killedEnemies(const int& row, const int& col, vector<vector<char>>& grid) {
        int kill_enemies_cnt = 0;
        int l = col - 1, r = col + 1, u = row - 1, d = row + 1;
        while (l >= 0) {
            if (grid[row][l] == 'E') {
                kill_enemies_cnt++;
                l--;
            }
            else if (grid[row][l] == 'W')   break;
            else    l--;
        }
        while (u >= 0) {
            if (grid[u][col] == 'E') {
                kill_enemies_cnt++;
                u--;
            }
            else if (grid[u][col] == 'W')   break;
            else    u--;
        }
        while (r < grid[0].size()) {
            if (grid[row][r] == 'E') {
                kill_enemies_cnt++;
                r++;
            }
            else if (grid[row][r] == 'W')   break;
            else    r++;
        }
        while (d < grid.size()) {
            if (grid[d][col] == 'E') {
                kill_enemies_cnt++;
                d++;
            }
            else if (grid[d][col] == 'W')   break;
            else    d++;
        }
        return kill_enemies_cnt;
    }
};

class Solution_v1_1 {
    struct segment {
        int start_x, start_y, end_x, end_y;
        int enemies;
        segment(int sx, int sy, int ex, int ey, int enemies) : start_x(sx), start_y(sy), end_x(ex), end_y(ey), enemies(enemies) {}
    };
    
    vector<segment> row_segments, col_segments;
public:
    ///@note    1. 对棋盘进行预处理，计算出每行和每列被墙所阻隔的区间内的敌人数目；
    //          2. 对所有相交区间进行遍历，找出相交区间上敌人的最大数目，交点必须为'0'。
    //          3. 时间复杂度为O((m + k) * l)，其中m是行数，k是墙的数目，l是区间的平均长度
    //          4. TLE
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty())    return 0;
        int rslt = 0;
        getRowSeg(grid);
        getColSeg(grid);
        
        for (int i = 0; i != row_segments.size(); i++) {
            for (int j = 0; j != col_segments.size(); j++) {
                rslt = max(rslt, killEnemiesOfTwoSeg(row_segments[i], col_segments[j], grid));
            }
        }
        return rslt;
    }
    
    ///@brief   对棋盘的行区间进行预处理
    ///@param   grid    棋盘
    void getRowSeg(vector<vector<char>>& grid) {
        for (int i = 0; i != grid.size(); i++) {
            int wall_x = -1, wall_y = -1;
            int enemies_cnt = 0;
            for (int j = 0; j != grid[0].size(); j++) {
                if (grid[i][j] == 'W') {
                    if (wall_x == -1 && wall_x == -1) {
                        wall_x = i;
                        wall_y = j;
                        if (j > 0) {
                            segment seg(i, 0, i, j-1, enemies_cnt);
                            row_segments.push_back(seg);
                            enemies_cnt = 0;
                        }
                    }
                    else {
                        segment seg(i, wall_y+1, i, j-1, enemies_cnt);
                        row_segments.push_back(seg);
                        enemies_cnt = 0;
                        wall_x = i;
                        wall_y = j;
                    }
                }
                else if (grid[i][j] == 'E') {
                    enemies_cnt++;
                }
            }
            if (wall_x == -1 && wall_y == -1) {
                segment seg(i, 0, i, grid[0].size()-1, enemies_cnt);
                row_segments.push_back(seg);
            }
            else {
                segment seg(i, wall_y+1, i, grid[0].size()-1, enemies_cnt);
                row_segments.push_back(seg);
            }
        }
    }
    
    ///@brief   对棋盘的列区间进行预处理
    ///@param   grid    棋盘
    void getColSeg(vector<vector<char>>& grid) {
        for (int j = 0; j != grid[0].size(); j++) {
            int wall_x = -1, wall_y = -1;
            int enemies_cnt = 0;
            for (int i = 0; i != grid.size(); i++) {
                if (grid[i][j] == 'W') {
                    if (wall_x == -1 && wall_x == -1) {
                        wall_x = i;
                        wall_y = j;
                        if (i > 0) {
                            segment seg(0, j, i-1, j, enemies_cnt);
                            col_segments.push_back(seg);
                            enemies_cnt = 0;
                        }
                    }
                    else {
                        segment seg(wall_x+1, j, i-1, j, enemies_cnt);
                        col_segments.push_back(seg);
                        wall_x = i;
                        wall_y = j;
                        enemies_cnt = 0;
                    }
                }
                else if (grid[i][j] == 'E') {
                    enemies_cnt++;
                }
            }
            if (wall_x == -1 && wall_y == -1) {
                segment seg(0, j, grid.size()-1, j, enemies_cnt);
                col_segments.push_back(seg);
            }
            else {
                segment seg(wall_x+1, j, grid.size()-1, j, enemies_cnt);
                col_segments.push_back(seg);
            }
        }
    }
        
    ///@brief   判断两个区间的最大杀敌数目
    ///@param   s1  行区间
    ///@param   s2  列区间
    ///@param   grid    棋盘
    ///@return  返回两个区间的的敌人数
    int killEnemiesOfTwoSeg(segment& s1, segment& s2, vector<vector<char>>& grid) {
        if (s1.start_y <= s2.start_y && s1.end_y >= s2.start_y
            && s2.start_x <= s1.start_x && s2.end_x >= s1.start_x
            && grid[s1.start_x][s2.start_y] == '0')
            return s1.enemies + s2.enemies;
        return 0;
    }
};

int main() {
    /*
     0 E 0 0
     E 0 W E
     0 E 0 0
     */
    vector<vector<char>> grid;
    vector<char> line;
    line.push_back('0');
    line.push_back('E');
    line.push_back('0');
    line.push_back('0');
    grid.push_back(line);
    line.clear();
    
    line.push_back('E');
    line.push_back('0');
    line.push_back('W');
    line.push_back('E');
    grid.push_back(line);
    line.clear();
    
    line.push_back('0');
    line.push_back('E');
    line.push_back('0');
    line.push_back('0');
    grid.push_back(line);
    line.clear();
    
    Solution_v1_0 slt_v1;
    int rslt = slt_v1.maxKilledEnemies(grid);
    
    Solution slt;
    rslt = slt.maxKilledEnemies(grid);
    return 0;
}



































