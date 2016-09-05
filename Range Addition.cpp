//
//  Range Addition.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/9/5.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Range Addition
///@author  zhaowei
///@date    2016.09.05
///@version 1.0

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution_tle {
public:
    ///@brief   对于一组初始为0的数组，通过将指定区间的值加上指定值，计算最后更新后的数组
    ///@param   length  数组的长度
    ///@param   updates 数组的更新操作，每一个更新操作是一个三元组<a, b, c>，其中a是更新的数组起始下标，b是更新范围的终止下标，c是累加的值
    ///@return  返回更新后的数组
    ///@note    1. 枚举；
    //          2. 对每一次更新都在输入数组上进行操作，对k此更新之后，就可以得出输出数组；
    //          3. 这种方法比较简单暴力，时间复杂度为O(kn)，其中k为更新操作的数量，n为每次操作的数组范围平均长度。很可能超时。果真超时了。TLE。
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> rslt(length, 0);
        for (int i = 0; i < updates.size(); i++) {
            for (int j = updates[i][0]; j <= updates[i][1]; j++) {
                rslt[j] += updates[i][2];
            }
        }
        return rslt;
    }
};

int main() {
    Solution slt;
    vector<int> update;
    update.push_back(1);
    update.push_back(3);
    update.push_back(2);
    vector<vector<int>> updates;
    updates.push_back(update);
    
    update.clear();
    update.push_back(2);
    update.push_back(4);
    update.push_back(3);
    updates.push_back(update);
    
    update.clear();
    update.push_back(0);
    update.push_back(2);
    update.push_back(-2);
    updates.push_back(update);
    
    vector<int> rslt = slt.getModifiedArray(5, updates);
    
    return 0;
}