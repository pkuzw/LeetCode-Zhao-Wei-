﻿///@file	Pascal's Triangle II
/*
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]
*/
///@author	zhaowei
///@date	2015.07.23
///@versio	1.1

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	生成杨辉三角的第k行
	///@param	rowIndex	行号
	///@return	返回杨辉三角的第n行
	/* @note	杨辉三角的第i+1行的第j个元素相当于在第i行的首末各加1个0，然后将第i行的第j和第j+1求和的值。
				时间复杂度为O(n^2)，空间复杂度为O(k)。*/
	vector<int> getRow(int rowIndex) {
		vector<int> line(1, 1);	//	vector的构造函数：初始化有1个1
		
		for (int i = 1; i <= rowIndex; i++)
		{			
			line.insert(line.begin(), 0);
			line.insert(line.end(), 0);
			vector<int> next_line;
			for (int i = 0; i != line.size()-1; i++)
				next_line.push_back(line[i]+line[i+1]);
			line = next_line;
		}
		return line;
	}
};

int main()
{
	int n = 5;
	Solution slt;
	vector<int> rslt = slt.getRow(n);
	return 0;
}