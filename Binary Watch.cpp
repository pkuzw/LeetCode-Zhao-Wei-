//
//  Binary Watch.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/18/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

/*
 A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).
 
 Each LED represents a zero or one, with the least significant bit on the right.
 
 For example, the above binary watch reads "3:25".
 
 Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.
 
 Example:
 
 Input: n = 1
 Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
 Note:
 The order of output does not matter.
 The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
 The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
 Show Company Tags
 Show Tags
 Show Similar Problems

 */
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector<int> hours = {1, 2, 4, 8};
    vector<int> minutes = {1, 2, 4, 8, 16, 32};
public:
    ///@brief   transform all the possible time
    ///@param   num the number of lights are on
    ///@return  all the possible time
    ///@note    1. recurrence
    //          2. https://discuss.leetcode.com/topic/59373/0ms-c-back-tracking-solution-easy-to-understand/2
    vector<string> readBinaryWatch(int num) {
        vector<string> rslt;
        pair<int, int> time = make_pair(0, 0);
        helper(rslt, time, num, 0);
        return rslt;
    }
    
    ///@brief   calculate the possible time with different lights on
    ///@param   rslt    all the time it represents possibly
    ///@param   time    the time it could present
    ///@param   num   the number of lights
    ///@param   start_point the index of hours and minutes
    ///@return  void
    void helper(vector<string>& rslt, pair<int, int> time, int num, int start_point) {
        if (num == 0) {
            if (time.second < 10) {
                rslt.push_back(to_string(time.first) + ":0" + to_string(time.second));
            }
            else {
                rslt.push_back(to_string(time.first) + ":" + to_string(time.second));
            }
            return;
        }
        for (int i = start_point; i < hours.size() + minutes.size(); i++) {
            if (i < hours.size()) {
                time.first += hours[i];
                if (time.first < 12)    helper(rslt, time, num - 1, i + 1);
                time.first -= hours[i];
            }
            else {
                time.second += minutes[i - hours.size()];
                if (time.second < 60)   helper(rslt, time, num - 1, i + 1);
                time.second -= minutes[i - hours.size()];
            }
        }
        return;
    }
};

int main() {
    int num = 1;
    Solution slt;
    vector<string> rslt = slt.readBinaryWatch(num);
    return 0;
}
































