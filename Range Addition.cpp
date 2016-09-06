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
#include <set>
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

///@brief   区间类
class interval {
public:
    int begin;  //  区间起始下标
    int end;    //  区间终止下标
    int val;    //  区间的值
    
    ///@brief   区间类的构造函数
    ///@param   beg 构造的区间类的起始下标
    ///@param   ed  构造的区间类的终止下标
    ///@param   vl  构造的区间类的值
    interval(int beg, int ed, int vl) : begin(beg), end(ed), val(vl) {}
    
};


class Solution {
public:
    ///@brief   对于一组初始值为0的数组，通过将指定区间的值加上指定值，计算最后更新后的数组
    ///@param   length  数组的长度
    ///@param   updates 数组的更新操作，每一个更新操作是一个三元组<a, b, c>，其中a是更新的数组起始下标，b是更新范围的终止下标，c是累加的值
    ///@return  返回更新后的数组
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> rslt(length, 0);
        sort(updates.begin(), updates.end(), mycmp);
        vector<interval> intervals;
        for (int i = 0; i != updates.size(); i++) {
            if (intervals.empty()) {
                interval intv(updates[i][0], updates[i][1], updates[i][2]);
                intervals.push_back(intv);
            }
            int j = 0;
            for (j = 0; j != intervals.size(); j++)
                if (intervals[j].begin >= updates[i][0] && intervals[j].begin <= updates[i][1])
                    break;
            if (j == intervals.size()) {
                interval intv(updates[i][0], updates[i][1], updates[i][2]);
                intervals.push_back(intv);
            }
        }
        
        return rslt;
    }
    
    ///@brief   比较函数
    ///@note    对区间按照起始下标进行排序
    static bool mycmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
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