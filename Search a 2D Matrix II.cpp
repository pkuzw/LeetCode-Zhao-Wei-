///@file	Search a 2D Matrix II
/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

For example,

Consider the following matrix:

[
[1,   4,  7, 11, 15],
[2,   5,  8, 12, 19],
[3,   6,  9, 16, 22],
[10, 13, 14, 17, 24],
[18, 21, 23, 26, 30]
]

Given target = 5, return true.

Given target = 20, return false.
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	///@brief	给定一个int型二维数组，其中每一行和每一列都按照从左往右，从上往下的顺序升序排列，在其中寻找指定值
	///@param	matrix	二维矩阵
	///@param	target	目标值
	///@return	如果矩阵中存在目标值，则返回true；否则返回false
	/* @note	在第一行中找到第一个比指定值大的元素下标i，在第一列中找到第一个比指定值大的元素下标j，然后我们的二分查找范围就缩小到
				matrix[0..i-1][0..j-1]，然后对每一行进行二分查找即可。时间复杂度为O(nlogn)，空间复杂度为O(1)。*/
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())	return false;

		bool flg = false;
		int row = matrix.size();
		int col = matrix[0].size();
		int right_bound = binarySearch(matrix[0], 0, col-1, target, flg);

		if (flg)	return true;

		vector<int> col_vec;
		for (int i = 0; i != row; i++)
			col_vec.push_back(matrix[i][0]);
		int bottom_bound = binarySearch(col_vec, 0, row-1, target, flg);

		if (flg)	return true;

		if (bottom_bound == -1 && right_bound == -1)		return false;

		for (int i = 0; i < bottom_bound; i++)
		{
			int k = binarySearch(matrix[i], 0, right_bound-1, target, flg);
			if (flg)	return true;
		}
		return flg;
	}

private:
	///@brief	二分查找。如果数组中存在该元素，则返回其下标，否则返回第一个比它大的元素下标
	///@param	ivec	数组
	///@param	p		起始下标
	///@param	r		终止下标		
	///@param	val		指定值
	///@param	flg		标记是否找到指定值
	///@return	如果数组中存在该元素，则返回其下标，否则返回第一个比它大的元素下标
	int binarySearch(vector<int>& ivec, int p, int r, const int val, bool &flg)
	{
		if (p > r)
		{	flg = false;
			return r+1;	//	如果没找到，则返回右边界的后一位
		}

		int q = (p+r)/2;
		if (ivec[q] == val)
		{
			flg = true;
			return q;
		}
		else if (ivec[q] < val)
		{
			if (q < ivec.size()-1 && val < ivec[q+1])
			{
				flg = false;
				return q+1;
			}
			return binarySearch(ivec, q+1, r, val, flg);
		}
		else 
		{
			if (q > 0 && ivec[q-1] < val)
			{
				flg = false;
				return q;
			}
			return binarySearch(ivec, p, q-1, val, flg);
		}
	}
};

int main()
{
	vector<int> nums;

	vector<vector<int>> matrix;
	nums.push_back(1);
	nums.push_back(4);
	nums.push_back(7);
	nums.push_back(11);
	nums.push_back(15);
	matrix.push_back(nums);
	nums.clear();

	nums.push_back(2);
	nums.push_back(5);
	nums.push_back(6);
	nums.push_back(12);
	nums.push_back(19);
	matrix.push_back(nums);
	nums.clear();

	nums.push_back(3);
	nums.push_back(6);
	nums.push_back(9);
	nums.push_back(16);
	nums.push_back(22);
	matrix.push_back(nums);
	nums.clear();

	nums.push_back(10);
	nums.push_back(13);
	nums.push_back(14);
	nums.push_back(17);
	nums.push_back(24);
	matrix.push_back(nums);
	nums.clear();

	nums.push_back(18);
	nums.push_back(21);
	nums.push_back(23);
	nums.push_back(26);
	nums.push_back(30);
	matrix.push_back(nums);
	nums.clear();
	bool flg = false;
	Solution slt;
	bool rslt = slt.searchMatrix(matrix, 30);

	return 0;
}