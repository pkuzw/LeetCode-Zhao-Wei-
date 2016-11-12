//
//  HackerRank - Jumping the Clouds.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/11/16.
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

int minStep(const vector<int>& c) {
    vector<int> onePos;
    for (int i = 0; i < c.size(); i++)
        if (c[i] == 1)  onePos.push_back(i);
    int start = 0;
    int cnt = 0;
    for (int i = 0; i < onePos.size(); i++) {
        int dist = onePos[i] - start - 1;
        if (dist % 2)   cnt += dist / 2 + 1;
        else    cnt += dist / 2;
        cnt++;
        start = onePos[i] + 1;
    }
    int dist = c.size() - 1 - start;
    if (dist % 2)   cnt += dist / 2 + 1;
    else    cnt += dist / 2;
    return cnt;
}


int main(){
    int n;
    cin >> n;
    vector<int> c(n);
    for(int c_i = 0;c_i < n;c_i++){
        cin >> c[c_i];
    }
    cout << minStep(c) << endl;
    
    return 0;
}
