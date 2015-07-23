///@file	Pascal's Triangle
/*
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

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
///@versio	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	生成杨辉三角
	///@param	n	行数
	///@return	返回杨辉三角的前n行
	/* @note	杨辉三角的第i+1行的第j个元素相当于在第i行的首末各加1个0，然后将第i行的第j和第j+1求和的值。
				时间复杂度为O(n^2)，空间复杂度为O(n^2)。*/
	vector<vector<int>> generate(int numRows) {
		if (numRows == 0)	return pascal_tri;

		vector<int> line(1, 1);	//	vector的构造函数：初始化有1个1
		pascal_tri.push_back(line);
		for (int i = 1; i < numRows; i++)
		{
			line = pascal_tri.back();
			line.insert(line.begin(), 0);
			line.insert(line.end(), 0);
			vector<int> next_line;
			for (int i = 0; i != line.size()-1; i++)
				next_line.push_back(line[i]+line[i+1]);
			pascal_tri.push_back(next_line);
		}
		return pascal_tri;
	}

private:
	vector<vector<int>> pascal_tri;
};

int main()
{
	int n = 0;
	Solution slt;
	vector<vector<int>> rslt = slt.generate(n);
	return 0;
}