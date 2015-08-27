///@file	Search a 2D Matrix
/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
Given target = 3, return true.
*/
///@author	zhaowei
///@date	2015.07.13
///@version	1.1

///@date	2015.08.27
///@version	2.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个m*n的二维矩阵，每一行按照升序排序，且每一列的首元素都大于上一列的尾元素。在其中查找给定值。
	///@param	matrix	二维矩阵
	///@param	target
	///@return	如果二维矩阵中存在target目标元素，则返回true；否则返回false
	///@note	比较直接的方法是直接将改二维矩阵转化成一维数组，然后应用二分查找即可。时间复杂度为O(log(mn))，空间复杂度为O(mn)。
	bool searchMatrix_space_O_mn(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())
		{
			return false;
		}
		int m = matrix.size();

		if (matrix[0].empty())
		{
			return false;
		}
		int n = matrix[0].size();

		vector<int> tmp;

		for (int i = 0; i != m; i++)
		{
			for (int j = 0; j != n; j++)
			{
				tmp.push_back(matrix[i][j]);
			}
		}

		return binary_search(tmp.begin(), tmp.end(), target);
	}

	///@brief	给定一个m*n的二维矩阵，每一行按照升序排序，且每一列的首元素都大于上一列的尾元素。在其中查找给定值。
	///@param	matrix	二维矩阵
	///@param	target
	///@return	如果二维矩阵中存在target目标元素，则返回true；否则返回false
	///@note	另外一种思路是在给定的二维矩阵上进行操作，先将每一行的首元素组成一个一维数组。然后在这个一维数组里找到目标值应该属于
	//			哪两位之间，然后去前者所在行再次进行二分查找。时间复杂度为O(logm + logn)，空间复杂度为O(1)。
	bool searchMatrix_space_O_1(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())
		{
			return false;
		}
		int m = matrix.size();	//	行数

		if (matrix[0].empty())
		{
			return false;
		}
		int n = matrix[0].size();	//	列数

		vector<int> first_col;
		for (int i = 0; i != m; i++)
		{
			first_col.push_back(matrix[i][0]);
		}

		int line_indx = binarySearch(first_col, target, 0, m-1);
		if (line_indx == -1)	return false;

		return binary_search(matrix[line_indx].begin(), matrix[line_indx].end(), target);
	}

private:
	///@brief	二分查找目标元素在已经排好序的一维数组中应该插入的位置
	///@param	a	排好序的一维数组
	///@param	target	目标元素
	///@param	p	搜索范围的起始下标
	///@param	r	搜索范围的终止下标
	///@return	返回目标元素应该插入位置的前一个元素下标，如果目标元素比第一个元素还小，则返回-1，比最后一个元素还大，则返回a.size()-1
	int	binarySearch(vector<int> a, const int target, int p, int r)
	{
		if (p > r)	//	超过前边界
		{
			return p-1;	
		}
		int mid = (p+r)/2;
		
		if (target >= a[mid])	
		{
			if (mid == r)	//	超过尾边界
			{
				return r;
			}
			else if (mid < r && target < a[mid+1])	//  保证a[mid+1]有效
				return mid;
			else if (mid < r && target >= a[mid+1])
				return binarySearch(a, target, mid+1, r);
		}
		else if (target < a[mid])
		{
			return binarySearch(a, target, p, mid-1);
		}
	}
};

class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty())	return false;
		int row = matrix.size();
		int col = matrix[0].size();
		vector<int> nums;
		for (int i = 0; i != row; i++)
			nums.insert(nums.end(), matrix[i].begin(), matrix[i].end());
		return binary_search(nums.begin(), nums.end(), target);
	}
};

int main()
{
	vector<int> line;
	vector<vector<int>> matrix;

	line.push_back(1);
	line.push_back(3);
	line.push_back(5);
	line.push_back(7);
	matrix.push_back(line);

	line.clear();
	line.push_back(10);
	line.push_back(11);
	line.push_back(16);
	line.push_back(20);
	matrix.push_back(line);

	line.clear();
	line.push_back(23);
	line.push_back(30);
	line.push_back(34);
	line.push_back(50);
	matrix.push_back(line);

// 	matrix.clear();
// 	line.clear();
// 	matrix.push_back(line);
// 	matrix.push_back(line);

	Solution_v1 slt_v1;
	bool rslt_v1 = slt_v1.searchMatrix_space_O_1(matrix, 34);
	Solution slt;
	bool rslt = slt.searchMatrix(matrix, 34);
	return 0;
}