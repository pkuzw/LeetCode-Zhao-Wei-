//
//  Logger Rate Limiter.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/22.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

///@note    1. 哈希表存储每条信息和上一次打印的时间戳；
//          2. 判断当前信息是否距离上次打印超过10s，如果超过则打印，并更新哈希表，否则返回false。
class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
     If this method returns false, the message will not be printed.
     The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        if (hash_tbl.find(message) == hash_tbl.end()) {
            hash_tbl[message] = timestamp;
            return true;
        }
        else {
            if (timestamp - hash_tbl[message] < 10) return false;
            else {
                hash_tbl[message] = timestamp;
                return true;
            }
        }
    }
    
private:
    unordered_map<string, int> hash_tbl;
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */

int main() {
    return 0;
}
