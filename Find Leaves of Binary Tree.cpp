//
//  Find Leaves of Binary Tree.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/30.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Find Leavees of Binary Tree
///@authro  zhaowei
///@date    2016.08.31
///@version 1.0

#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    ///@brief   自底向上的遍历所有叶子节点
    ///@param   root    根节点
    ///@return  返回每层叶子节点组成的二维数组
    ///@note    1. 前序遍历
    //          2. 通过前序遍历二叉树的每个节点，如果当前节点为叶子节点，则将其压入结果数组，并从二叉树中删除
    //          3. 调用d次获取叶子节点的方法，即可获取整个叶子节点的二维数组。其中d为二叉树深度
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> rslt;
        int depth = getDepth(root, 0);
        TreeNode* parent = new TreeNode(-1);
        parent->left = root;
        for (int i = 0; i != depth; i++) {
            vector<int> leaves;
            getLeaves(root, parent, leaves);
            rslt.push_back(leaves);
        }
        return rslt;
    }
    
    ///@brief   获取二叉树深度
    ///@param   root    二叉树树根节点
    ///@param   curDepth    当前深度
    ///@return  返回二叉树深度
    int getDepth(TreeNode* root, int curDepth) {
        if (!root)  return curDepth;
        int rslt = max(getDepth(root->left, curDepth + 1), getDepth(root->right, curDepth + 1));
        return rslt;
    }
    
    ///@brief   前序遍历二叉树，寻找当前二叉树的叶子节点，将其压入结果数组，并删除叶子节点
    ///@param   root    根节点
    ///@param   parent  当前节点的父节点
    ///@param   leaves   当前层的叶子节点
    void getLeaves(TreeNode* root, TreeNode* parent, vector<int>& leaves) {
        if (!root)  return;
        
        if (!root->left && !root->right) {
            leaves.push_back(root->val);
            if (parent->left == root)   parent->left = nullptr;
            else    parent->right = nullptr;
        }
        getLeaves(root->left, root, leaves);
        getLeaves(root->right, root, leaves);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    TreeNode* nodes[4];
    for (int i = 0; i != 4; i++) {
        nodes[i] = new TreeNode(i + 2);
    }
    root->left = nodes[0];
    root->right = nodes[1];
    nodes[0]->left = nodes[2];
    nodes[0]->right = nodes[3];
    
    Solution slt;
    
    int depth = slt.getDepth(root, 0);
    
    vector<vector<int>> rslt;
    rslt = slt.findLeaves(root);
    

    return 0;
}

