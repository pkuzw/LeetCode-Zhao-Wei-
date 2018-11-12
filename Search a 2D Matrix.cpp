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

///@date	2015.12.05
///@version 3.0

///@date	2016.04.21
///@version	3.1

///@date    November 12, 2018
//@version  3.2

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
		return binarySearch(a, target, p, mid-1);
    }
};

class Solution_v2 {
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

class Solution_v3 {
public:
	///@brief	给定一个二维矩阵，每一行按照升序排序，且首元素比上一行的尾元素大，寻找是否存在指定值
	///@param	matrix	矩阵
	///@param	target	目标值
	///@return	如果存在，则返回true；否则返回false。
	///@note	1. 二分查找：首先确定出元素在哪一行，然后再在该行中进行查找。两次查找都用二分查找，区别是前者应该返回小于等于目标值的最大值；后者直接判断存在与否。
	//			2. 时间复杂度为O(logm + logn)，空间复杂度为O(1)。其中m和n为矩阵的行数和列数
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty() || matrix[0].empty())	return false;
		int m = matrix.size(), n = matrix[0].size();
		vector<int> col0;
		for (int i = 0; i != m; i++)	col0.push_back(matrix[i][0]);
		int row = binarySearchIndx(col0, target);
		if (row == -1)	return false;
		return binarySearchExist(matrix[row], target);
	}
private:
	///@brief	二分查找
	///@param	vec	排序数组
	///@param	target	目标值
	///@return	如果目标值存在，则返回目标值所在下标；否则返回比目标值小的最大元素下标。当目标值比最小元素还小时，返回-1.
	int binarySearchIndx(vector<int>& vec, int target) {
		int left = 0, right = vec.size()-1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (vec[mid] == target)	return mid;
			else if (vec[mid] < target)	left = mid + 1;
			else	right = mid - 1;
		}
		return right;	//	这里因为要取比目标值小的最大值，所以应该选择跳出循环后的right，因为跳出循环后left会比right更大。
	}

	///@brief	判断元素是否存在的二分查找
	///@param	vec	排序数组
	///@param	target	目标值
	///@return	如果目标值存在则返回true；否则返回false
	bool binarySearchExist(vector<int>& vec, int target) {
		int left = 0, right = vec.size()-1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (vec[mid] == target)	return true;
			else if (vec[mid] < target)	left = mid + 1;
			else	right = mid - 1;
		}
		return false;
	}
};

class Solution {
public:
    ///@brief   给定矩阵，其中每一行从左至右按照升序排列，并且每一行的最左侧首元素按照从上至下的顺序升序排列，找到指定元素；
    ///@param   matrix  排好序的矩阵；
    ///@param   target  目标元素；
    ///@return  如果矩阵中存在该元素，则返回true；否则返回false。
    ///@note    1. 二分查找；
    //          2. 首先，通过矩阵首列元素组成的数组，找到元素所在行。这里要注意，在二分查找时，返回右边界可以得到没有找到目标元素时的小于该目标值的最大元素；返回左边界可以找到大于该目标值的最小元素；
    //          3. 找到所在行后再在这一行查找是否存在该元素即可；
    //          4. 时间复杂度为O(logm + logn)，空间复杂度为O(1)，其中m为矩阵行数，n为矩阵列数。
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())    return false;
        vector<int> colZero;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; i++) colZero.push_back(matrix[i][0]);
        int row = searchColumn(colZero, target);
        if (row == -1)  return false;
        return searchRow(matrix[row], target);
    }
    
    ///@brief   查找目标值所在的行；
    ///@param   colZero 矩阵首列所组成的数组；
    ///@param   target  目标值；
    ///@return  返回目标值所在行的行号。
    ///@note    1. 注意，当目标值不等于中间值时，返回右边界r可以得到小于目标值的最大元素；返回左边界l可以得到大于目标值的最小元素。
    int searchColumn(vector<int>& colZero, int target) {
        int l = 0, r = colZero.size() - 1;
        while (l <= r) {
            int m = (l+r) / 2;
            if (colZero[m] == target)   return m;
            else if (colZero[m] < target)   l = m + 1;
            else r = m - 1;
        }
        return r;
    }
    
    ///@brief   查找该行元素中是否存在目标值；
    ///@param   row 矩阵的一行
    ///@param   target  目标值
    ///@return  如果目标值存在，返回true；否则返回false。
    bool searchRow(vector<int>& row, int target) {
        int l = 0, r = row.size() - 1;
        while (l <= r) {
            int m = (l+r) / 2;
            if (row[m] == target)   return true;
            else if (row[m] < target)   l = m + 1;
            else r = m - 1;
        }
        return false;
    }
};



int main()
{
    vector<vector<int>> matrix;
    vector<int> line;
	line.push_back(1);
	line.push_back(3);
	line.push_back(5);
	line.push_back(7);
	matrix.push_back(line);

	Solution_v1 slt_v1;
    int target = 0;
	bool rslt_v1 = slt_v1.searchMatrix_space_O_1(matrix, target);
	Solution slt;

    bool rslt = slt.searchMatrix(matrix, target);
	return 0;
}
