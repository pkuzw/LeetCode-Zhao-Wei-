//
//  Frog Jump.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/8/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Frog Jump
///@author  Wei Zhao
///@data    10.08.2016
///@version 1.0

/*
 A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.
 
 Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.
 
 If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.
 
 Note:
 
 The number of stones is ≥ 2 and is < 1,100.
 Each stone's position will be a non-negative integer < 231.
 The first stone's position is always 0.
 Example 1:
 
 [0,1,3,5,6,8,12,17]
 
 There are a total of 8 stones.
 The first stone at the 0th unit, second stone at the 1st unit,
 third stone at the 3rd unit, and so on...
 The last stone at the 17th unit.
 
 Return true. The frog can jump to the last stone by jumping
 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 2 units to the 4th stone, then 3 units to the 6th stone,
 4 units to the 7th stone, and 5 units to the 8th stone.
 Example 2:
 
 [0,1,2,3,4,8,9,11]
 
 Return false. There is no way to jump to the last stone as
 the gap between the 5th and 6th stone is too large.
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
private:
    unordered_map<int, bool> dp;    // in this hash map, the last 11 bits are used to store the stone's index and the higher bits are the gaps for the jump starting at pos
public:
    /*
     @note
     1. use dfs to search the goal
     2. if gap < k - 1, then continue;
     3. if gap > k + 1, return false;
     4. use the unordered_map to store the result of the start position and the gap, because the problem has limited the size of stones is less than 1100 < 2^11 = 2048, and the valid k is also less than 1100 because the start position is 0 and 1, so the increment is 1 for each jump at most.
     5. https://discuss.leetcode.com/topic/59439/straight-forward-9ms-7-line-c-solution-with-explanation
     */
    bool canCross(vector<int>& stones) {
        return dfs(stones, 0, 0);
    }
    
    bool dfs(vector<int> &stones, int pos, int k) {
        int key = pos | (k << 11);
        if (dp.count(key) > 0)  return dp[key];
        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];
            if (gap < k - 1)    continue;
            if (gap > k + 1) {
                dp[key] = false;
                return dp[key];
            }
            if (dfs(stones, i, gap)) {
                dp[key] = true;
                return dp[key];
            }
        }
        dp[key] = pos == stones.size() - 1;
        return dp[key];
    }
};

int main() {
    vector<int> stones = {0,1,3,5,6,8,12,17};
    Solution slt;
    bool rslt = slt.canCross(stones);
    
    return 0;
}






















