//
//  Insert Delete GetRandom O(1).cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/21/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Insert Delete GetRandom O(1)
///@author  Wei Zhao
///@date    2016.09.21
///@version 1.0

/*
 Design a data structure that supports all following operations in average O(1) time.
 
 insert(val): Inserts an item val to the set if not already present.
 remove(val): Removes an item val from the set if present.
 getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
 Example:
 
 // Init an empty set.
 RandomizedSet randomSet = new RandomizedSet();
 
 // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 randomSet.insert(1);
 
 // Returns false as 2 does not exist in the set.
 randomSet.remove(2);
 
 // Inserts 2 to the set, returns true. Set now contains [1,2].
 randomSet.insert(2);
 
 // getRandom should return either 1 or 2 randomly.
 randomSet.getRandom();
 
 // Removes 1 from the set, returns true. Set now contains [2].
 randomSet.remove(1);
 
 // 2 was already in the set, so return false.
 randomSet.insert(2);
 
 // Since 1 is the only number in the set, getRandom always return 1.
 randomSet.getRandom();
 */

#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <cstdlib>

using namespace std;

/*
 note:  1. using num array to store the elements and unordered_map ht to store each element's index
        2. when delete the element, we should store the tail element in the num and ht, then erase it.
        3. https://discuss.leetcode.com/topic/53286/ac-c-solution-unordered_map-vector/2
 */

class RandomizedSet {
private:
    vector<int> num;
    unordered_map<int, int> hash_tbl;
    
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (hash_tbl.find(val) != hash_tbl.end())   return false;
        num.push_back(val);
        hash_tbl[val] = int(num.size() - 1);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (hash_tbl.find(val) == hash_tbl.end())   return false;
        int last = num.back();  //  the element will be popped
        
        //  because the variable last will be popped out, so it should be stored in another place, where the value will be erased.
        //  in the hash table, the value will be erased, so it should be stored at the index of last.
        num[hash_tbl[val]] = last;
        hash_tbl[last] = hash_tbl[val];
        
        num.pop_back();
        hash_tbl.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return num[rand() % num.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() {
    return 0;
}









































