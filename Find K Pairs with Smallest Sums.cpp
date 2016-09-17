>//
//  Find K Pairs with Smallest Sums.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/17/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Find K Pairs with Smallest Sums
///@author Wei Zhao
///@date    2016.09.17
///@version 1.0

#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
private:
    struct compare {
        bool operator()(pair<int, int>& a, pair<int, int>& b) {
            return a.first + a.second < b.first + b.second;
        }
    }mycmp;
public:
    ///@brief   A pair of numbers consists of two items, the first one is chosen from the Array1, and the second one is from Array2. At the same time, these arrays has been ordered ascendingly. Find the smallest k pairs.
    ///@param   nums1   Array1
    ///@param   nums2   Array2
    ///@param   k       k smallest sum of pairs
    ///@return  k smallest pairs
    ///@note    1. Priority Queue
    //          2. Maintain a max priority queue, at the front of the queue there is always the largest pair because if there appears a smaller pair, the largest pair could be eliminated from the queue.
    //          3. for the priority queue, when it was constructed, the compara parameter must be a type. So it is defined as struct.
    //          4. By the way, the result was in relevence with the order.
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> rslt;
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
        
        for (int i = 0; i != min((int)nums1.size(), k); i++) {
            for (int j = 0; j != min((int)nums2.size(), k); j++) {
                if (pq.size() < k) {
                    pq.push(make_pair(nums1[i], nums2[j]));
                }
                else if (nums1[i] + nums2[j] < pq.top().first + pq.top().second) {
                    pq.push(make_pair(nums1[i], nums2[j]));
                    pq.pop();
                }
            }
        }
        
        while (!pq.empty()) {
            rslt.push_back(pq.top());
            pq.pop();
        }
        return rslt;
    }
};

int main() {
    vector<int> nums1;
    vector<int> nums2;
    /*
    for (int i = 1; i != 5; i++) {
        nums1.push_back(i);
        nums2.push_back(2*i + 1);
    }
     */
    
    nums1.push_back(1);
    nums1.push_back(1);
    nums1.push_back(2);
    
    nums2.push_back(1);
    nums2.push_back(2);
    nums2.push_back(3);
    
    Solution slt;
    vector<pair<int, int>> rslt = slt.kSmallestPairs(nums1, nums2, 2);
    return 0;
}
