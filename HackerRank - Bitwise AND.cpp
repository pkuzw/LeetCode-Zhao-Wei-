//
//  HackerRank - Bitwise AND.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/10/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int helper(const int& n, int k) {
    int rslt = k - 1;
    while (rslt > 0) {
        int i = 32;
        int tmp = rslt;
        int t3 = rslt;
        while (i--) {
            int lastBit = t3 & 1;
            t3 >>= 1;
            if (lastBit == 0)   break;
        }
        int c = (1 << (31 - i));
        int t2 = tmp | c;
        if (t2 <= n)   return tmp;
        rslt--;
    }
    return rslt;
}


int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int k;
        cin >> n >> k;
        int rslt = helper(n, k);
        cout << rslt << endl;
    }
    return 0;
}
