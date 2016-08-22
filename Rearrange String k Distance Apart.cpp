//
//  Rearrange String k Distance Apart.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/22.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Rearrange String k Distance Apart
///@author  zhaowei
///@date    2016.08.22
///@version 1.0

#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    ///@brief   重新组合字符串，使得其中的相同字符至少有k的距离
    ///@param   str 原始字符串
    ///@param   k   相同字符串相距的距离
    ///@return  返回新的满足条件的字符串
    ///@note    1. 用最大堆来维护数据
    //          2. 用一个缓冲区来保证每次循环中相同字符的间隔大于指定值
    //          3. 时间复杂度为O(n)，空间复杂度为O(n).
    string rearrangeString(string str, int k) {
        if (k == 0) return str;
        int len = str.size();
        
        string rslt;
        unordered_map<char, int> dict;
        priority_queue<pair<int, char>> pq;
        
        for (int i = 0; i != len; i++)  dict[str[i]]++;
        
        for (auto i = dict.begin(); i != dict.end(); i++)   pq.push(make_pair(i->second, i->first));
        
        while (!pq.empty()) {
            vector<pair<int, char>> cache;  //  存储每次while循环中的字符
            int count = min(k, len);    //  每次while循环的步数
            for (int i = 0; i != count; i++) {
                if (pq.empty()) return "";
                auto tmp = pq.top();
                pq.pop();
                rslt.push_back(tmp.second);
                if (--tmp.first > 0)    cache.push_back(tmp);
                len--;
            }
            for (auto i = cache.begin(); i != cache.end(); i++) pq.push(*i);
        }
        return rslt;
    }
};

int main() {
    string str = "aaabbccd";
    Solution slt;
    string rslt = slt.rearrangeString(str, 2);
    return 0;
}