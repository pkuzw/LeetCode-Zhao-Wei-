//
//  Arithmetic Slices.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/16/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Arithmetic Slices
///@author  Wei Zhao
///@date    Oct. 16, 2016
///@version 1.0

#include <vector>

using namespace std;

class Solution {
public:
    /*
     @note
     1. iteration
     2. enumerate all the elements in the array, find all the arithmetic slices and store their length. 
     3. for the length = n, the arithmetic slices' number is equal to (n - 1)(n - 2) / 2
     4. if a slice isn't arithmetic, the next slice should be judged at the last one of the previous slice, not the neighbor of the last element of previous slice. For example, {1,2,3,4,5,5,5}, the first slice is {1, 2, 3, 4, 5} and the second slice is {5, 5, 5}, not {5, 5}.
     */
    int numberOfArithmeticSlices(vector<int>& A) {
        if (A.empty())  return 0;
        vector<int> lens;
        int i = 0;
        int j = i + 2;
        int d = A[i + 1] - A[i];
        while (j < A.size()) {
            if (A[j] - A[j - 1] == d) {
                j++;
            }
            else {
                if (j - i > 2) {
                    lens.push_back(j - i);
                }
                i = j - 1;
                j = i + 2;
                d = A[i + 1] - A[i];
            }
        }
        if (j == A.size() && j - i > 2) {
            if (A[j] - A[j - 1] == d)
                lens.push_back(j - i + 1);
            else
                lens.push_back(j - i);
        }
        
        int rslt = 0;
        for (int k = 0; k < lens.size(); k++) {
            rslt += (lens[k] - 2) * (lens[k] - 1) / 2;
        }
        return rslt;
    }
};

int main() {
    vector<int> A = {1, 2, 3, 4, 6, 7, 8};
    Solution slt;
    int rslt = slt.numberOfArithmeticSlices(A);
    return 0;
}


/*
 A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
 
 For example, these are arithmetic sequence:
 
 1, 3, 5, 7, 9
 7, 7, 7, 7
 3, -1, -5, -9
 The following sequence is not arithmetic.
 
 1, 1, 2, 5, 7
 
 A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
 
 A slice (P, Q) of array A is called arithmetic if the sequence:
 A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
 
 The function should return the number of arithmetic slices in the array A.
 
 
 Example:
 
 A = [1, 2, 3, 4]
 
 return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/
