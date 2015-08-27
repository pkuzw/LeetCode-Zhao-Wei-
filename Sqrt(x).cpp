///@file	Sqrt(x)
/*
Implement int sqrt(int x).

Compute and return the square root of x.
*/
///@author	zhaowei
///@date	2015.07.10
///@version	1.0

///@date	2015.08.27
///@version	2.0

#include <iostream>

using namespace std;

class Solution_v1 {
public:
	///@brief	求整型变量x的平方根
	///@param	x	被开平方的非负整数
	///@return	返回其非负平方根
	///@note	牛顿迭代法：R(k+1) = (R(k)+x/R(k))/2，迭代若干次直到R(k+1)^2与x的差的绝对值能够符合要求为止。因为本题只求整型变量的
	//			平方根，结果要只要求到整型变量。故精确度要求不高。
	int mySqrt(int x) {
		double x_d = x;	//	先将整型变量转换为双精度浮点型
		double rslt = 1;	//	设置初始值R(0)
		while (abs(rslt*rslt-x_d) > 0.01)	//	如果求得的平方根的平方与原整型变量的差小于0.01则退出迭代
		{
			double t = x_d/rslt;
			rslt = (rslt + t)/2;
		}
		return rslt;
	}
};

/*
二分查找平方根。为了防止溢出，中间结果用long long型保存。
*/
class Solution {
public:
	int mySqrt(int x) {
		long long left = 1, right = x / 2 + 1;
		while (left <= right)
		{
			long long mid = (left + right ) / 2;
			if (mid * mid == x)	return mid;
			else if (mid * mid < x) left = mid + 1;
			else right = mid - 1;
		}
		return right;
	}
};

int main()
{
	Solution slt;
	int x = 0;
	while (cin >> x){		
		cout << slt.mySqrt(x) << endl;
	}
	return 0;
}