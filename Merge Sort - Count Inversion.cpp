//
//  Merge Sort - Count Inversion.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/3/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <stdio.h>
#include <vector>
using namespace std;

///@param   b   sorted array
void merge(vector<int>& a, int left, int mid, int right) {
    int i = left;   //  index for left subarray
    int j = mid + 1;    //  index for right subarray
    vector<int> b;  //  auxillary array for the sorted result
    
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            b.push_back(a[i]);
            i++;
        }
        else {
            b.push_back(a[j]);
            j++;
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
    for (int p = left; p <= right; p++)
        a[p] = b[p-left];
    return;
}

///@param   left    the start index for a
///@param   right   the end index for a
void mergeSort(vector<int>& a, int left, int right) {
    if (left >= right)  return;
    int mid = (left + right) / 2;
    
    mergeSort(a, left, mid);
    mergeSort(a, mid+1, right);
    merge(a, left, mid, right);
    
    return;
}

int main() {
    vector<int> a = {10, 3, 4, 1, 8, 9, 6, 5, 7};
    int left = 0;
    int right = a.size() - 1;
    
    mergeSort(a, left, right);
    
    
    return 0;
}
