//
//  Fizz Buzz.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/14/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Fizz Buzz
///@author  Wei Zhao
///@date    Oct. 14, 2016
///@version 1.0

/*
 Write a program that outputs the string representation of numbers from 1 to n.
 
 But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
 
 Example:
 
 n = 15,
 
 Return:
 [
 "1",
 "2",
 "Fizz",
 "4",
 "Buzz",
 "Fizz",
 "7",
 "8",
 "Fizz",
 "Buzz",
 "11",
 "Fizz",
 "13",
 "14",
 "FizzBuzz"
 ]
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     @note:
     1. if the number is the multiple of 3, print Fizz
     2. if the number is the multiple of 5, print Buzz
     3. if the number is the common multiple of 3 and 5, print FizzBuzz
     */
    vector<string> fizzBuzz(int n) {
        vector<string> rslt;
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5) rslt.push_back("Fizz");
            else if (i % 5 == 0 && i % 3)   rslt.push_back("Buzz");
            else if (i % 3 == 0 && i % 5 == 0)  rslt.push_back("FizzBuzz");
            else    rslt.push_back(to_string(i));
        }
        return rslt;
    }
};

int main() {
    
    return 0;
}

































