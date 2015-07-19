///@file	Maximal Rectangle
/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
*/
///@author	zhaowei
///@date	2015.07.19
///@version	1.0

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	给定一个二进制的二维矩阵，计算最大的全部都是1的矩形面积
	///@param	matrix	二维矩阵
	///@return	返回全部都是1的矩形的面积
	/* @note
	枚举+剪枝+动归：最简单的想法是枚举出所有矩形的大小（O(n^2)）和不同的位置（O(n^2)），时间复杂度为O(n^4)。
	以(0,0)为矩形的左上角为例：

	1 1 1 1 0 0

	1 1 1 0 1 1

	1 0 1 0 1 1

	0 1 1 1 1 1

	1 1 1 1 1 1

	矩形高度是1时，宽度为第一行中从第一个位置起连续的1的个数，为4，面积为4 * 1 = 4

	矩形高度是2时，第二行从第一个位置起连续1的个数是3，宽度为min(3,4) = 3，面积为3*2 = 6

	矩形高度为3时，第三行从第一个位置起连续1的个数是1，宽度为min(1,3) = 1，面积为1*3 = 3

	矩形高度为4时，第四行从第一个位置起连续1的个数是0，宽度为min(0,1) = 0，面积为0*4 = 0

	后面的行就不用计算了，因为上一行计算的宽度是0，下面所有宽度都是0

	因此以(0,0)为左上角的矩形的最大面积是6，计算以某一点为左上角的矩形的最大面积复杂度是O(n)。
	
	在枚举矩形时可以利用动态规划来寻找不同位置的连续个1的出现次数。
	
	用dp[i][j] = (matrix[i][j] == '1') ? 1 + dp[i][j+1] : 0；
	
	初始条件为dp[i][matrix.col-1] = (matrix[i][matrix.col-1] == 1) ? 1 : 0。
	
	然后通过剪枝，当枚举到以某一个位置为矩形的左上角时，该矩形的可能的最大面积比现有的全由1组成的矩形面积还要小时，可以不再往下枚举。
	
	动态规划得到所有位置连续1的长度（O(n)），然后再枚举不同的矩形左上角下标（O(n^2)），那么总的时间复杂度为O(n^3)，空间复杂度为O(n^2)
	*/
	int maximalRectangle(vector<vector<char>>& matrix) {
		int height = matrix.size(); 
		if (height == 0)
		{
			return 0;
		}
		int width = matrix[0].size();

		vector<vector<int>> dp;	//	以[i][j]为起始位置，向右连续的1的个数
		vector<int> line;
		for (int i = 0; i != width; i++)	//	初始化dp
		{
			line.push_back(0);
		}
		for (int i = 0; i != height; i++)
		{
			dp.push_back(line);
		}

		for (int i = 0; i != height; i++)
		{
			if (matrix[i][width-1] == '1')
				dp[i][width-1] = 1;
			else
				dp[i][width-1] = 0;
		}

		for (int i = 0; i != height; i++)
		{
			for (int j = width-2; j != -1; j--)
			{
				dp[i][j] = (matrix[i][j] == '1') ? 1 + dp[i][j+1] : 0;
			}
		}

		int max_area = 0;
		for (int i = 0; i != height; i++)
		{
			for (int j = 0; j != width; j++)
			{
				if ((height-i) * (width-j) <= max_area)	//	如果以当前元素作为矩形的左上角，其可能的最大面积都小于已找到的全由1组成的矩形，直接跳出循环
					break;

				int rect_width = dp[i][j];	//	矩形的宽度
				for (int k = i; k != height && rect_width > 0; k++)
				{
					if ((height-i) * rect_width <= max_area) break;	// 如果以当前元素作为矩形的左上角，其可能的最大面积都小于已找到的全由1组成的矩形，直接跳出循环
					
					if (rect_width > dp[k][j])
					{
						rect_width = dp[k][j];	//	矩形的宽度又最小值决定
					}
					max_area = max(max_area, rect_width * (k-i+1));
				}
			}
		}
		return max_area;
	}
};

int main()
{
	vector<vector<char>> matrix;
	int line_num = 6;
// 	cout << "input the matrix's line number: ";
// 	cin >> line_num;
	while (line_num)
	{
		cout << "rest number of lines: " << line_num << endl;
		vector<char> line;
		char k = ' ';
		while (cin >> k)
		{
			if (k == '2')
			{
				break;
			}
			line.push_back(k);
		}
		matrix.push_back(line);
		line_num--;
	}
	
	for (int i = 0; i != matrix.size(); i++)
	{
		for (int j = 0; j != matrix[0].size(); j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	/*
	1 1 0 1 1 0 2
	1 1 1 1 1 1 2
	1 1 1 1 0 1 2
	1 1 1 1 1 1 2
	1 1 1 0 0 1 2
	1 1 1 0 0 1 2
	*/
	Solution slt;
	cout << slt.maximalRectangle(matrix) << endl;

	return 0;
}