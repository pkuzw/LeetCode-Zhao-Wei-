//
//  Android Unlock Patterns.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/7/22.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Android Unlock Patterns
///@author  zhaowei
///@date    2016.07.22
///@version 1.0

#include <iostream>
using namespace std;

class Solution {
public:
    ///@brief   计算安卓手机锁屏的种类数目
    ///@param   m   最少按钮数
    ///@param   n   最多按钮数
    ///@return  返回安卓手机9键盘的锁屏方法种类，要求一笔画；穿过的按键之前应该被访问过；数字的顺序有意义
    int numberOfPatterns(int m, int n) {
        int rslt = 0;
        for (int len = m; len <= n; len++) {
            rslt += calPatterns(-1, len);
            for (int i = 0; i < 9; i++) {
                used[i] = false;
            }
        }
        return rslt;
    }
    
    ///@brief   判断一个模式是否合法
    bool isValid(int index, int last) {
        if (used[index])    return false;
        if (last == -1) return true;
        if ((index + last) % 2 == 1)    return true;
        int mid = (index + last) / 2;
        if (mid == 4)   return used[mid];
        if ((index % 3 != last % 3) && index / 3 != last / 3)   return true;
        return used[mid];
    }
private:
    bool used[9];
    
    ///@brief   计算合法的解锁图案数目
    int calPatterns(int last, int len) {
        if (len == 0)   return 1;
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (isValid(i, last)) {
                used[i] = true;
                sum += calPatterns(i, len - 1);
                used[i] = false;
            }
        }
        return sum;
    }
};

int main() {
    Solution slt;
    int rslt = slt.numberOfPatterns(1, 1);
    cout << "hello world.\n";
    return 0;
}