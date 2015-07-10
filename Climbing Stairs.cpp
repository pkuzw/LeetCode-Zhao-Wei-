///@file	Climbing Stairs
/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
///@author	zhaowei
///@date	2015.07.10
///@version	1.0

#include <iostream>
using namespace std;

class Solution {
public:
	///@brief	计算到达梯子顶端的方法数
	///@param	n	梯子格数
	///@return	返回方法数
	///@note	通过观察发现f(0) = 1, f(1) = 1, f(2) = 2, f(3) = 3, f(4) = 5, f(6) = 8, f(7) = 13, f(8) = 21.
	//			推测f(k+2) = f(k)+f(k+1)。因为f(k) = C(k, 0) + C(k-1, 1) + ... + C(k-k/2, k/2). 这其中的每个组合数相当于在i个位置
	//			中放置j个'2'，其余位置放置'1'。递归法的递归方程为T(n) = T(n-1)+T(n-2)+O(1)。时间复杂度为O(1.68^n)，空间复杂度为O(n)。
	int climbStairs(int n) {		
		if (n == 0 || n == 1) return 1;
		if (n > 1)
		{
			return climbStairs(n-1)+climbStairs(n-2);
		}
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