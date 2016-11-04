//
//  Merge Sort - Count Inversion.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/3/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@source: https://www.hackerrank.com/challenges/ctci-merge-sort

#include <stdio.h>
#include <vector>
using namespace std;


long long merge(vector<int>& a, int left, int mid, int right) {
    int i = left;   //  index for left subarray
    int j = mid + 1;    //  index for right subarray
    vector<int> b;  //  auxillary array for the sorted result
    long long inversionCnt = 0; //  the inversion counter
    
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            b.push_back(a[i]);
            i++;
        }
        else {
            b.push_back(a[j]);
            j++;
            inversionCnt += mid - i + 1;    //  inversion appears. count all the inversions from i to mid in the left subarray.
        }
    }
    while (i <= mid) {
        b.push_back(a[i]);
        i++;
    }
    while (j <= right) {
        b.push_back(a[j]);
        j++;
    }
    for (int p = left; p <= right; p++)     //  copy the sorted array to a
        a[p] = b[p-left];
    return inversionCnt;
}

///@param   left    the start index for a
///@param   right   the end index for a
long long mergeSort(vector<int>& a, int left, int right) {
    if (left >= right)  return 0;
    int mid = (left + right) / 2;
    long long inversionCnt = 0;
    
    inversionCnt += mergeSort(a, left, mid);
    inversionCnt += mergeSort(a, mid+1, right);
    inversionCnt += merge(a, left, mid, right);
    
    return inversionCnt;
}

long long count_inversions(vector<int>& a) {
    int left = 0;
    int right = a.size() - 1;
    return mergeSort(a, left, right);
}

int main() {
    vector<int> a = {10, 3, 4, 1, 8, 9, 6, 5, 7};
    int left = 0;
    int right = a.size() - 1;
    
    long long rslt = count_inversions(a);
    
    
    return 0;
}
