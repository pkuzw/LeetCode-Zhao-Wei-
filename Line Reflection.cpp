//
//  Line Reflection.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/22.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Line Reflection
///@author  zhaowei
///@date    2016.08.22
///@version 1.0

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

#include <stdio.h>

using namespace std;

class Solution {
public:
    ///@brief   判断一组二维平面上的点能否被平行于y轴的直线轴对称
    ///@param   points  点组
    ///@return  如果存在平行于y轴的线使得点轴对称，返回true；否则返回false
    ///@note    1. 先将点按照y轴坐标进行分类，对于y值相同的点，判断其是否存在对称轴；
    //          2. 判断每种y值的对称轴是否相同；
    //          3. 如果前两点都满足，则存在对称轴；否则不存在；
    //          4. 需要考虑重复点的情况，另外对于点位于对称轴上的情形，认为也对称；
    //          5. 时间复杂度为O(n^2)，空间复杂度为O(n)。
    bool isReflected(vector<pair<int, int>>& points) {
        unordered_map<int, vector<int>> hash_tbl;
        for (int i = 0; i != points.size(); i++) {
            hash_tbl[points[i].second].emplace_back(points[i].first);
        }
        double axis_init = 0;
        for (unordered_map<int, vector<int>>::iterator i = hash_tbl.begin(); i != hash_tbl.end(); i++) {
            if (i == hash_tbl.begin()) {
                if (!isSymmetry(i->second, axis_init))  return false;
            }
            else {
                double axis = 0;
                if (isSymmetry(i->second, axis) && axis == axis_init)   continue;
                else return false;
            }
        }
        return true;
    }
    
    ///@brief   判断一组数是否存在对称轴，使得其轴对称
    ///@param   ivec    整型数组
    ///@param   axis    对称轴
    ///@return  如果存在对称轴，返回true；否则返回false
    bool isSymmetry(vector<int> ivec, double& axis) {
        sort(ivec.begin(), ivec.end());
        vector<int>::iterator end_unique = unique(ivec.begin(), ivec.end());    //  使用unique算法，删除排好序的相邻重复元素，其包含在<algorithm>头文件中，返回结束重复元素的迭代器位置，其并未改变容器大小，还需再次调用erase函数清除尾部的重复元素
        ivec.erase(end_unique, ivec.end());
        int len = ivec.size();
        for (int i = 0; i < (len / 2) - 1; i++) {
            if (double(double(ivec[i] + ivec[len - 1 - i]) / 2) != double(double(ivec[i + 1] + ivec[len - 1 - i - 1]) / 2))
                return false;
        }
        axis = (double(ivec.front() + ivec.back())) / 2;
        if (len % 2) {
            if (axis == (double)ivec[len / 2])  return true;
            else    return false;
        }
        return true;
    }
};

int main() {
    vector<pair<int, int>> points;
    Solution slt;
    points.push_back(make_pair(0, 0));
    points.push_back(make_pair(1, 0));
    points.push_back(make_pair(3, 0));
/*  points.push_back(make_pair(2, 1));
    points.push_back(make_pair(-2, 1));
/*
    points.push_back(make_pair(1, 2));
    points.push_back(make_pair(-2, 2));
    points.push_back(make_pair(0, 2));
    points.push_back(make_pair(-1, 2));
  */
    bool rslt = slt.isReflected(points);
    return 0;
}

























