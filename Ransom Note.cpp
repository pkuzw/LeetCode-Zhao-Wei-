//
//  Ransom Note.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/18/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Ransom Note
///@author  Wei Zhao
///@date    2016.09.18
///@version 1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    ///@brief   Judge whether ransomNote can be constructed from magazine
    ///@param   ransomNote  string
    ///@param   magazine    string
    ///@return  if the ransom string could be assembled from magazine, return true. Or return false.
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size())    return false;
        int ht[26] = {0};
        for (int i = 0; i != magazine.length(); i++) {
            ht[magazine[i] - 'a']++;
        }
        for (int i = 0; i != ransomNote.length(); i++) {
            ht[ransomNote[i] - 'a']--;
            if (ht[ransomNote[i] - 'a'] < 0)    return false;
        }
        return true;
    }
};

int main() {
    Solution slt;
    string ransomNote = "aa", magazine = "aab";
    bool rslt = slt.canConstruct(ransomNote, magazine);
    return 0;
}
