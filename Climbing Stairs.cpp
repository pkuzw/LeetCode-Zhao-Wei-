///@file	Climbing Stairs
/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
///@author	zhaowei
///@date	2015.07.10
///@version	1.0

///@date	2015.08.27
///@version	2.0

///@date	2015.12.04
///@version	3.0

///@date	2016.04.19
///@version	3.1

///@date    November 9, 2018
///@version 4.0

#include <iostream>
#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算到达梯子顶端的方法数
	///@param	n	梯子格数
	///@return	返回方法数
	///@note	通过观察发现f(0) = 1, f(1) = 1, f(2) = 2, f(3) = 3, f(4) = 5, f(6) = 8, f(7) = 13, f(8) = 21.
	//			推测f(k+2) = f(k)+f(k+1)。因为f(k) = C(k, 0) + C(k-1, 1) + ... + C(k-k/2, k/2). 这其中的每个组合数相当于在i个位置
	//			中放置j个'2'，其余位置放置'1'。递归法的递归方程为T(n) = T(n-1)+T(n-2)+O(1)。时间复杂度为O(k^n)，k为常数。空间复杂度为O(n)。
	int climbStairs_recursive(int n) {		
		if (n == 0 || n == 1) return 1;
		if (n > 1)
		{
			return climbStairs_recursive(n-1)+climbStairs(n-2);
		}
	}

	///@brief	计算到达梯子顶端的方法数
	///@param	n	梯子格数
	///@return	返回方法数
	///@note	采用递推的方法，将上述方法改进成O(n)的时间复杂度。
	int climbStairs(int n) {
		vector<int> climbing_numbers;
		climbing_numbers.push_back(1);
		climbing_numbers.push_back(1);

		int k = 2;
		while (k < n+1)
		{			
			int tmp = climbing_numbers[k-1]+climbing_numbers[k-2];
			climbing_numbers.push_back(tmp);
			k++;
		}
		return climbing_numbers[n];
	}
};

class Solution_v2 {
public:
	int climbStairs(int n) {
		vector<int> dp(n+1);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i != n + 1; i++)
			dp[i] = dp[i-1] + dp[i-2];
		return dp[n];
	}
};

class Solution_v3 {
public:
	///@brief	一个有n阶台阶的梯子，可以选择每次爬一格，或者一次爬两格。计算爬完n阶有多少种方法。变相的计算菲波那切数列的第n项
	///@param	n	台阶数目
	///@return	返回菲波那切数列的第n项
	///@note	1. 利用递推关系式f(n) = f(n-1) + f(n-2)来计算；2. 用两个临时变量来保存中间结果。时间复杂度为O(n)，空间复杂度为O(1)。
	int climbStairs(int n) {
		int a = 1;
		int b = 2;		
		if (n == 1 || n == 2)	return n;		
		
		int i = 3;
		int c = a + b;
		while (i <= n) {
			c = a + b;
			a = b;
			b = c;
			i++;
		}
		return c;
	}
};

class Solution {
public:
	int climbStairs(int n) {
		int a = 1, b = 2, c = 3, i = 3;
		if (n == 1 || n == 2)	return n;
		while (i <= n) {
			c = a + b;
			a = b;
			b = c;
			i++;
		}
		return c;
	}
};

int main()
{
	int n;
	Solution slt;
	cout << "Input Steps: ";
	while (cin >> n)
	{
		cout << "Methods' Number: ";
		cout << slt.climbStairs(n) << endl;
		cout << endl;
		cout << "Input Steps: ";
	}
	return 0;
}
