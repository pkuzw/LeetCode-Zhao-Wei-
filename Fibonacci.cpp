//
//  Fibonacci.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/18/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

void multiply(vector<vector<int>>& m1, vector<vector<int>>& m2) {
    int x = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0];
    int y = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1];
    int z = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0];
    int u = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1];
    
    m1[0][0] = x;
    m1[0][1] = y;
    m1[1][0] = z;
    m1[1][1] = u;
}

void power(vector<vector<int>>& m, int n) {
    if (n == 0 || n == 1)   return;
    vector<vector<int>> t = {{1, 1}, {1, 0}};
    power(m, n/2);
    multiply(m, m);
    
    if (n % 2)  multiply(m, t);
}

int fibonacci(int n) {
    if (n == 0) return 0;
    vector<vector<int>> m = {{1, 1}, {1, 0}};
    power(m, n - 1);
    return m[0][0];
}


int main() {
    int t = 0;
    cin >> t;
    while (t--) {
        int n = 1;
        cin >> n;
        int rslt = fibonacci(n);
        cout << rslt << endl;
    }
    return 0;
}
