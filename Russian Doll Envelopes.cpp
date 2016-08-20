//
//  Russian Doll Envelopes.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/19.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@author  zhaowei
///@date    2016.08.20
///@version 1.0

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    ///@brief   计算能够完全包含子信封的最大嵌套数目
    ///@param   envelopes   信封的尺寸，嵌套时要求较大信封的长宽值应该大于较小信封的长宽值
    ///@return  返回最大嵌套信封数目
    ///@note    1. 动态规划
    //          2. 先对信封按照宽度升序、高度降序进行排序，之所以是高度按照降序，是为了后添加进来的信封高度尽可能的小
    //          3. 时间复杂度为O(nlogn)，空间复杂度为O(n)
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), cmp);
        vector<int> dp;
        for (int i = 0; i != envelopes.size(); i++) {
            auto iter = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
            if (iter == dp.end())    dp.push_back(envelopes[i].second);
            else    *iter = envelopes[i].second;
        }
        return dp.size();
    }
    
    ///@brief   排序函数
    ///@return  按照宽度升序、高度降序的顺序来对信封数组进行排序
    static bool cmp(pair<int, int> &i, pair<int, int> &j) {
        if (i.first == j.first) return i.second > j.second;
        else    return i.first < j.first;
    }
};

int main() {
    return 0;
}
