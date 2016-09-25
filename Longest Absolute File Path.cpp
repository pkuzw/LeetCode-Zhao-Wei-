//
//  Longest Absolute File Path.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/24/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Longest Absolute File Path
///@author  Wei Zhao
///@date    2016.09.24
///@version 1.0

/*
 Suppose we abstract our file system by a string in the following manner:
 
 The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
 
 dir
 subdir1
 subdir2
 file.ext
 The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.
 
 The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:
 
 dir
 subdir1
 file1.ext
 subsubdir1
 subdir2
 subsubdir2
 file2.ext
 The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.
 
 We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).
 
 Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.
 
 Note:
 The name of a file contains at least a . and an extension.
 The name of a directory or sub-directory will not contain a ..
 Time complexity required: O(n) where n is the size of the input string.
 
 Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.
 
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    ///@brief   calculate the longest directory path length
    ///@param   input   the directory
    ///@return  the longest directory path length
    ///@note    1. iteration
    ///         2. use switch statement to process different characters apprear in the string
    //          3. if there is a '\n', we should count the length of this subdirectory and update it
    //          4. if there is a '\t', we should increase the depth of directory
    //          5. if there is a '.', we could find that it isn't a subdirectory
    //          6. others is just increment the subdirectory's counter
    //          7. https://discuss.leetcode.com/topic/59968/very-concise-c-solution-0ms
    int lengthLongestPath(string input) {
        if (input.empty())  return 0;
        int rslt = 0;
        
        vector<int> depth_len;  //  the different length in different depth of directory
        int count = 0;  //  the subdirectory or file name's length
        int isDir = 1;  //  the flag to mark whether this layer is directory or not
        int depth = 0;  //  the current depth of subdirectory
        
        for (int i = 0; i <= input.length(); i++) {
            switch(input[i]) {
                case '\0':
                case '\n': {
                    //  get the current subdirectory or file's length
                    count = depth == 0 ? count + isDir : depth_len[depth - 1] + count + isDir;
                    
                    //  update the depth_len
                    if (depth < depth_len.size())   depth_len[depth] = count;
                    else    depth_len.push_back(count);
                    
                    //  update the result
                    if (!isDir) rslt = max(rslt, count);
                    
                    //  reset
                    count = 0;
                    depth = 0;
                    isDir = 1;break;
                }
                case '\t' : {
                    depth++;break;
                }
                case '.' : {
                    isDir = 0;
                }
                default: {
                    count++;
                }
            }
        }
        return rslt;
    }
};

int main() {
    string input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
    Solution slt;
    int rslt = slt.lengthLongestPath(input);
    return 0;
}
