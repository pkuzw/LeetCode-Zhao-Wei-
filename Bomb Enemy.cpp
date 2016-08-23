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
    //          3. 时间复杂度为O(mn)，空间复杂度为O(1)，其中m和n分别是行列数
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
    return 0;
}



































