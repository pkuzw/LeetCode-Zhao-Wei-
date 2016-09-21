//
//  Design Phone Directory.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/21/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Design Phone Directory
///@author  Wei Zhao
///@date    2016.09.21
///@version 1.0

/*
 Design a Phone Directory which supports the following operations:
 
 get: Provide a number which is not assigned to anyone.
 check: Check if a number is available or not.
 release: Recycle or release a number.
 Example:
 
 // Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
 PhoneDirectory directory = new PhoneDirectory(3);
 
 // It can return any available phone number. Here we assume it returns 0.
 directory.get();
 
 // Assume it returns 1.
 directory.get();
 
 // The number 2 is available, so return true.
 directory.check(2);
 
 // It returns 2, the only number that is left.
 directory.get();
 
 // The number 2 is no longer available, so return false.
 directory.check(2);
 
 // Release number 2 back to the pool.
 directory.release(2);
 
 // Number 2 is available again, return true.
 directory.check(2);
 */

#include <unordered_map>
#include <vector>

using namespace std;

class PhoneDirectory_tle {
private:
    vector<bool> phone_dict;
public:
    /** Initialize your data structure here
     @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        int i = 0;
        while (i < maxNumbers) {
            phone_dict.push_back(true);
            i++;
        }
    }
    
    /** Provide a number which is not assigned to anyone.
     @return - Return an available number. Return -1 if none is available. */
    int get() {
        for (int i = 0; i < phone_dict.size(); i++) {
            if (phone_dict[i]) {
                phone_dict[i] = false;
                return i;
            }
        }
        return -1;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        if (number >= phone_dict.size()) return false;
        return phone_dict[number];
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if (number >= phone_dict.size()) return;
        phone_dict[number] = true;
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */































