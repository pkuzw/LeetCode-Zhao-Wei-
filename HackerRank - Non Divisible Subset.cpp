//
//  HackerRank - Non Divisible Subset.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/11/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

struct p {
    int occr;
    int rsd;
};

bool cmp(const p& a, const p& b) {
    return a.occr > b.occr;
}

int helper(const vector<int>& a, const int& k) {
    vector<vector<int>> ht(k, vector<int>(1, 0));
    for (int i = 0; i < a.size(); i++) {
        ht[a[i]%k][0]++;
    }
    vector<p> pvec;
    for (int i = 0; i < ht.size(); i++) {
        p pa;
        pa.rsd = i;
        pa.occr = ht[i][0];
        pvec.push_back(pa);
    }
    sort(pvec.begin(), pvec.end(), cmp);
    
    vector<int> res;
    int cnt = 0;
    for (int i = 0; i < pvec.size(); i++) {
        if (pvec[i].rsd * 2 % k != 0) {
            int j = 0;
            for (j = 0; j < res.size(); j++) {
                if (pvec[i].rsd + res[j] == k) {
                    
                    break;
                }
            }
            if (j == res.size()) {
                cnt += pvec[i].occr;
                res.push_back(pvec[i].rsd);
            }
        }
        else if (pvec[i].occr > 0){
            cnt++;
        }
    }
    return cnt == 0 ? 1 : cnt;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n = 0, k = 0;
    cin >> n >> k;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << helper(a, k) << endl;
    return 0;
}
