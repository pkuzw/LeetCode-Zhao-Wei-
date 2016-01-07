///@file	Pascal's Triangle II
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
///@version	1.0
///@version	1.1

///@date	2015.08.23
///@version	1.2

///@date	2016.01.07
///@version	1.3

#include <vector>
#include <deque>

using namespace std;

class Solution_v1 {
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

class Solution_v1_1 {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> pascal_triangle(1, 1);
		for (int i = 0; i != rowIndex; i++)
		{
			pascal_triangle.insert(pascal_triangle.begin(), 0);
			pascal_triangle.push_back(0);
			for (int j = 0; j != pascal_triangle.size()-1; j++)
				pascal_triangle[j] = pascal_triangle[j] + pascal_triangle[j+1];
			pascal_triangle.pop_back();
		}
		return pascal_triangle;
	}
};

class Solution {
public:
	///@brief	生成杨辉三角的第k行
	///@param	rowIndex	行号
	///@return	返回杨辉三角的第n行
	///@note	1. 与"Pascal's Triangle"类似，只不过是不保存前n行，直接求第n行。
	vector<int> getRow(int rowIndex) {
		vector<int> rslt;
		if (rowIndex < 0)	return rslt;
		rslt.push_back(1);
		for (int i = 1; i <= rowIndex; i++) {
			rslt.push_back(0);
			rslt.insert(rslt.begin(), 0);
			for (int j = 0; j < rslt.size() - 1; j++)
				rslt[j] += rslt[j + 1];
			rslt.pop_back();
		}
		return rslt;
	}
};

int main()
{
	int n = 3;
	Solution slt;
	vector<int> rslt = slt.getRow(n);
	return 0;
}