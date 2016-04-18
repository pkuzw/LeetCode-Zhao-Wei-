///@file	Unique Paths
/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/
///@author	zhaowei
///@date	2015.07.08
///@version	1.0

///@date	2015.08.28
///@version	2.0

///@date	2015.11.29
///@version	2.1

///@date	2016.04.18
///@version	2.2

#include <iostream>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一个m*n的棋盘，计算从左上角出发，到右下角的路径数目。其间只能向右和向下移动。
	///@param	m	行号
	///@param	n	列号
	///@return	返回路径总数
	///@note	从左上角出发，到右下角，一共要走m+n-2步，其中向右移动n-1步，向下移动m-1步。问题就是转化为组合数计算。
	//			总的路径数就是C(m+n-2, n-1) * C(m-1, m-1)。即使是1*1的棋盘，也认为路径数目为1。时间复杂为O(n)，空间复杂度为O(1)。
	int uniquePaths(int m, int n) {
		//	计算C(m+n-2, m-1)
		int k = m+n-2;
		int t = m<n ? m-1 : n-1;		//	因为C(m, n) == C(m, m-n)，为减轻计算量，应该选取min(n, m-n)
		double path_nums = 1;	// 计算阶乘的时候有可能int型变量越界，用double来存储
		while (t != 0)
		{			
			path_nums *= k;
			k--;
			t--;
		}
		t = m<n ? m-1 : n-1;
		double tmp = 1;	//	同上
		while (t != 0)
		{
			tmp *= t;
			t--;
		}
		path_nums /= tmp;
		int rslt = path_nums;
		return rslt;
	}
};

class Solution_v2 {
public:
	///@brief	计算一个m*n的棋盘中从左上角到右下角的方法数
	///@param	m	棋盘的高度
	///@param	n	棋盘的宽度
	///@return	返回从棋盘左上角到右下角的方法数
	///@note	相当于计算组合数C(m + n - 2, m - 1)或者C(m + n - 2, n - 1)。
	int uniquePaths(int m, int n) {
		long long rslt = 1;
		if (m == 1 || n == 1)	return rslt;
		int k = m + n - 2;
		int p = m > n ? n - 1 : m - 1;
		int t = p;
		
		while (t--) {
			rslt *= k;
			k--;
		}
		while (p) {
			rslt /= p;
			p--;
		}
		return rslt;
	}
};

class Solution {
public:
	int uniquePaths(int m, int n) {
		long long rslt = 1;
		if (m == 1 || n == 1)	return rslt;
		int p = m > n ? n - 1 : m - 1;
		int k = m + n - 2;
		int t = p;
		while (t--) {
			rslt *= k;
			k--;
		}
		while (p) {
			rslt /= p;
			p--;
		}
		return rslt;
	}
};

int main()
{
	int m = 10, n = 10;
	Solution slt;
	int rslt = slt.uniquePaths(m, n);
	 
	Solution_v1 slt_v1;
	rslt = slt_v1.uniquePaths(m, n);
	return 0;
}