//
//  Valid Word Abbreviation.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/14/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Valid Word Abbreviation
///@author  Wei Zhao
///@date    Oct. 14, 2016
///@version 1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     @note:
     1. validate the abbr by extending it from digit bit, if the next character behind digit is the same as the word, then can move on.
     2. the abbreviation number can't contain leading zeros.
     */
    bool validWordAbbreviation(string word, string abbr) {
        if ((abbr.empty() && !word.empty()) || (!abbr.empty() && word.empty()))  return false;
        string digit_str;
        int abbr_digit_len = 0;
        int abbr_i = 0;
        int digit_i = 0;
        int word_i = 0;
        while (abbr_i < abbr.size()) {
            if (abbr[abbr_i] <= '9' && abbr[abbr_i] >= '0') {
                digit_i = abbr_i;
                while (abbr[digit_i] <= '9' && abbr[digit_i] >= '0') {
                    digit_i++;
                }
                digit_str = abbr.substr(abbr_i, digit_i - abbr_i);
                if (digit_str.front() == '0')   return false;   //  without leading zero
                abbr_digit_len = stoi(digit_str);
                if (word_i + abbr_digit_len < word.size() && word[word_i + abbr_digit_len] == abbr[digit_i]) {
                    word_i = word_i + abbr_digit_len;
                    abbr_i = digit_i;
                }
                else if (word_i + abbr_digit_len == word.size() && abbr_i == abbr.size() - 1)
                    return true;
                else
                    return false;
            }
            else {
                if (word[word_i] != abbr[abbr_i])   return false;
                else {
                    word_i++;
                    abbr_i++;
                }
            }
        }
        return word_i == word.size();
    }
};

int main() {
    string word, abbr;
    Solution slt;
    word = "internationalization";
    abbr = "i5a11o1";
    
    bool rslt = slt.validWordAbbreviation(word, abbr);
    
    return 0;
}
/*
 Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.
 
 A string such as "word" contains only the following valid abbreviations:
 
 ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid abbreviation of "word".
 
 Note:
 Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.
 
 Example 1:
 Given s = "internationalization", abbr = "i12iz4n":
 
 Return true.
 Example 2:
 Given s = "apple", abbr = "a2e":
 
 Return false.
 */
