//
//  Sum of Left Leaves.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/30/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Sum of Left Leaves
///@author  Wei Zhao
///@date    2016.09.30
///@version 1.0

/*
 Find the sum of all left leaves in a given binary tree.
 
 Example:
 
 3
 / \
 9  20
 /  \
 15   7
 
 There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
 */

#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    ///@note    1. preorder traversal
    //          2. find all the left leaves and use a global variable to sum them
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        
    }
    
    void dfs(TreeNode* root, int& sum) {
        if (!root)  return;
        if (root->left && )
    }
};

int main() {
    
    return 0;
}






















