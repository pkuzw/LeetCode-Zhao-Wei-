//
//  Design Hit Counter.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/25.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Design Hit Counter
///@author  zhao wei
///@date    2016.08.25
///@version 1.0

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

///@note    1. 可以将问题看做给定一个升序的正整数数组，然后给定上界b，求出[b - 300, b]中的元素数目
//          2. 二分查找用来找到小于等于b的最大值和大于等于b-300的最小值，将二者的下标相减就是中间的元素数目
//          3. 查找的时间复杂度为O(logn)，空间复杂度为O(n)，其中n为正整数数目
//          4. 对于有序的容器，可以采用lower_bound()和upper_bound()来确定边界。lower_bound返回第一个不小于指定值的迭代器；upper_bound返回第一个大于指定值的迭代器
//          5. 因为有可能同时有多个点击需要记录，所以整数数组内有重复元素
//          6. 其下边界就是大于val-300的第一个元素，即upper_bound(val-300)
//          7. 其上边界是不小于val的第一个元素。分两种情况，如果上边界等于val，则需要向后遍历，直至大于val；否则当前上边界就是有效hit的末尾哨兵位置

class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
        
    }
    
    /** Record a hit.
     @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        hits.push_back(timestamp);
    }
    
    /** Return the number of hits in the past 5 minutes.
     @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        vector<int>::iterator l = upper_bound(hits.begin(), hits.end(), timestamp - 300);
        vector<int>::iterator r = lower_bound(hits.begin(), hits.end(), timestamp);
        while (r != hits.end() && *r == timestamp)
            r++;
        return r - l;
    }
    
private:
    vector<int> hits;
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */

int main() {
    HitCounter hc;
    hc.hit(1);
    hc.hit(1);
    hc.hit(1);
    hc.hit(2);
    hc.hit(2);
    hc.hit(3);
    hc.hit(3);
    
    int r = 0;
    
    r = hc.getHits(15);
    
    hc.hit(300);
    hc.hit(300);
    hc.hit(301);
    hc.hit(301);
    hc.hit(301);
    
    r = hc.getHits(300);
    r = hc.getHits(303);
    return 0;
}
