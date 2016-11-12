//
//  HackerRank - Happy Ladybugs.cpp
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

bool isHappy(const string& a, const int& n) {
    unordered_map<char, int> ht;
    ht['_'] = 0;
    for (auto i : a) {
        ht[i]++;
    }
    if (ht['_'] == 0) {
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && a[i] == a[i+1])    continue;
            else if (i > 0 && a[i] == a[i-1])   continue;
            else    return false;
        }
    }
    else {
        for (unordered_map<char, int>::iterator i = ht.begin(); i != ht.end(); i++)
        {
            if (i->first != '_' && i->second == 1)  return false;
        }
    }
    return true;
}


int main(){
    int Q;
    cin >> Q;
    for(int a0 = 0; a0 < Q; a0++){
        int n;
        cin >> n;
        string b;
        cin >> b;
        bool isHap = isHappy(b, n);
        if (!isHap)  cout << "NO" << endl;
        else    cout << "YES" << endl;
    }
    return 0;
}
