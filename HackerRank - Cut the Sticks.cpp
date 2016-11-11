//
//  HackerRank - Cut the Sticks.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/10/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

///@brief   check if all the length of sticks are all zero
int checkSticks (const vector<int>& a) {
    int cnt = 0;
    for (auto i : a) {
        if (i > 0)  cnt++;
    }
    return cnt;
}

///@brief   find the smallest length of sticks
int findSmallestStick(const vector<int>& a) {
    int minLen = 1000000000;
    for (auto i : a) {
        if (i > 0)
            minLen = min(i, minLen);
    }
    return minLen;
}

///@brief   cut sticks
void cutSticks(vector<int> a) {
    while(checkSticks(a) != 0) {
        cout << checkSticks(a) << endl;
        int minLen = findSmallestStick(a);
        for (auto& i : a)
            i -= minLen;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int arr_i = 0;arr_i < n;arr_i++){
        cin >> arr[arr_i];
    }
    cutSticks(arr);
    return 0;
}
