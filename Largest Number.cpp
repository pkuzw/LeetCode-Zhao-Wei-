///@file	Largest Number
/*
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.12
///@version	2.0

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一组非负正数，把它们组合起来，找出最大的组合数
	///@param	nums	数组
	///@return	返回最大的组合数
	/* @note	本题最关键的地方是如何对数进行排序，然后按照排号的顺序依次拼接起来就可以。我们可以利用STL中的sort自定义比较函数，对于两个
				子串A和B，它只有两种拼接方式，要么是AB，要么是BA，按照其中一种进行排序。然后在依次拼接即可。时间复杂度为O(nlog)，空间复杂度为O(n)。*/
	string largestNumber(vector<int>& nums) {
		string rslt;
		sort(nums.begin(), nums.end(), myCmp);

		if (nums[0] == 0)	return "0";	//	如果按照我们自定义的比较方法，最大的数是0的话，说明数组中全部都是0.则直接返回"0"，而非"00..0"

		for (int i = 0; i != nums.size(); i++)
			rslt += to_string(static_cast<long long>(nums[i]));	//	VS2010并不完全支持真正的C++11，to_string一共有三种重载函数（long long, unsigned long long, long double），将其强制转换成其中的一种就不会报错了。

		return rslt;
	}
private:
	struct myObj
	{
		bool operator() (const int& a, const int& b)
		{
			string s1 = to_string(static_cast<long long>(a));
			string s2 = to_string(static_cast<long long>(b));
			return s1 + s2 > s2 + s1;
		}
	}myCmp;
};

/*
精华在于自定义的比较函数。将两个整数转换成字符串，然后利用字符串之和的比较规则来定义排序规则，真是妙！
*/
class Solution {
public:
	string largestNumber(vector<int>& nums) {
		string rslt;
		sort(nums.begin(), nums.end(), myCmp);
		if (!nums.front())	return "0";
		for (int i = 0; i != nums.size(); i++)
			rslt += to_string(static_cast<long long>(nums[i]));
		return rslt;
	}

private:
	struct myClass{
		bool operator() (const int& a, const int& b)
		{
			string s1 = to_string(static_cast<long long>(a));
			string s2 = to_string(static_cast<long long>(b));
			return s1 + s2 > s2 + s1;
		}
	}myCmp;
};

int main()
{
	vector<int> nums;
	nums.push_back(0);
	nums.push_back(0);
 	nums.push_back(0);
 	nums.push_back(0);
 	nums.push_back(0);

	Solution slt;
	string rslt = slt.largestNumber(nums);
	return 0;
}
