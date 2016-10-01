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
    //          3. if there is only a root node, it doesn't count as left leaf.
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        dfs(root, sum, false);
        return sum;
    }
    
    void dfs(TreeNode* root, int& sum, bool fromLeft) {
        if (!root)  return;
        if (root->left) dfs(root->left, sum, true);
        if (root->right)    dfs(root->right, sum, false);
        if (!root->left && !root->right && fromLeft)
            sum += root->val;
        return;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    
    TreeNode* n1 = new TreeNode(9);
    TreeNode* n2 = new TreeNode(20);
    TreeNode* n3 = new TreeNode(15);
    TreeNode* n4 = new TreeNode(7);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n6 = new TreeNode(27);
    
    root->left = n1;
    root->right = n2;
    n2->left = n3;
    n2->right = n4;
    n4->left = n5;
    n1->left = n6;
    
    Solution slt;
    
    int rslt = slt.sumOfLeftLeaves(root);

    return 0;
}






















