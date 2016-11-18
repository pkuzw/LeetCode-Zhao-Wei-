//
//  Sort Practice.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 11/15/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

///@brief   get a random array whose elements are between 0 - k and number is n
vector<int> getRandomArray(const int& k, const int& n) {
    vector<int> rslt;
    srand(time(nullptr));
    int i = 0;
    while (i < n) {
        int a = rand() % k;
        rslt.push_back(a);
        i++;
    }
    return rslt;
}

///@brief   bubble sort
// time O(n^2), space O(1), stable
void bubbleSort(vector<int>& a, const int& n) {
    bool swapped = true;
    int j = 0;
    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < n - j; i++) {
            if (a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                swapped = true;
            }
        }
    }
}

///@brief   insertion sort
// time O(n^2), space O(1), stable
void insertionSort(vector<int>& a, const int& n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && a[j-1] > a[j]) {
            swap(a[j-1], a[j]);
            j--;
        }
    }
}

///@brief   selection sort
// time O(n^2), space O(1), not stable
void selectionSort(vector<int>& a, const int& n) {
    for (int i = 0; i < n; i++) {
        int minNum = INT_MAX;
        int minIndx = 0;
        for (int j = i; j < n; j++) {
            if (a[j] < minNum) {
                minNum = a[j];
                minIndx = j;
            }
        }
        swap(a[i], a[minIndx]);
    }
}

///@brief   merge sort
// time O(nlogn), space O(n), stable
void merge(vector<int>& a, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> b(a.begin() + p, a.begin() + q + 1);
    vector<int> c(a.begin() + q + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (b[i] < c[j])    a[p + k] = b[i++];
        else    a[p + k] = c[j++];
        k++;
    }
    while (i < n1) {
        a[p + k] = b[i++];
        k++;
    }
    while (j < n2) {
        a[p + k] = c[j++];
        k++;
    }
}

void mergeSort(vector<int>& a, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(a, p, q);
        mergeSort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

///@brief   quick sort
// time O(nlogn), space O(n), not stable
int partition(vector<int>& a, int p, int r) {
    int i = p - 1;
    int x = a[r];
    
    for (int j = p; j < r; j++) {
        if (a[j] <= x) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(vector<int>& a, int p, int r) {
    if (p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

///#brief   shell sort
// time complexity: depends, O(n^2) if interval = n / 2^k; O(n^3/2) if interval = 2^k - 1
// unstable and adaptive
void shellSort(vector<int>& a, const int& n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            for (int j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
                swap(a[j], a[j + gap]);
        }
    }
}

int main() {
    
    int k = 100, n = 10;
    vector<int> a = getRandomArray(k, n);
    shellSort(a, n);
//    quickSort(a, 0, n - 1);
//    mergeSort(a, 0, n - 1);
//    selectionSort(a, n);
//    insertSort(a, n);
//    bubbleSort(a, n);
    return 0;
}
