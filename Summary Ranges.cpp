///@file	Summary Ranges
/*
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.07
///@version	2.1

#include <vector>
#include <string>

using namespace std;

class Solution_v1 {
public:
	///@brief	给定一组已经排好序的数组，计算它的连续整数范围
	///@param	nums	排好序的数组
	///@return	返回连续元素的范围
	/* @note	遍历数组，用两个变量记录下连续元素的范围，一个标定起始位置，一个标定终止位置。如果二者相等，则只输出起始位置，否则输出
				'start->end'。时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> rslt;
		if (nums.empty())	return rslt;

		int start = 0;
		int end = 0;
		string s;
		for (int i = 0; i != nums.size()-1; i++)
		{
			if (nums[i] != nums[i+1]-1)
			{
				s.clear();
				if (start == end)	s = intToStr(nums[i]);								
				else				s = intToStr(nums[start]) + "->" + intToStr(nums[end]);

				rslt.push_back(s);
				start = i+1;
				end = i+1;			
			}
			else
			{
				end++;
			}
		}
		if (start == end)	s = intToStr(nums[start]);								
		else				s = intToStr(nums[start]) + "->" + intToStr(nums[end]);
		rslt.push_back(s);

		return rslt;
	}

private:
	///@brief	将整数转换成字符串
	///@param	n	整数
	///@return	返回它对应的字符串
	string intToStr(int n)
	{
		if (n == 0)			return "0";
		if (n == INT_MIN)	return "-2147483648";
		string s;
		bool flg = false;
		if (n < 0)
		{
			flg = true;
			n *= -1;
		}
		vector<int> dec;
		for (int i = 0; i < 10; i++)
		{
			int k = 1;
			for (int j = 1; j <= i; j++)
			{
				k *= 10;
			}
			dec.push_back(k);
		}

		bool flg1 = false;
		for (int i = dec.size()-1; i >= 0; i--)
		{			
			int t = n;
			if (n >= dec[i])
			{
				s += char(n/dec[i]+'0');
				n %= dec[i];
				flg1 = true;
			}
			if (t < dec[i] && flg1)
				s += '0';
		}
		return flg ? "-" + s : s;
	}
};

class Solution {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> rslt;
		if (nums.empty())	return rslt;

		int start = 0, end = 0;
		string s;
		for (int i = 0; i < nums.size()-1; i++)
		{
			if (nums[i] == nums[i+1]-1)	end++;
			else
			{
				if (end == start)	s = to_string(static_cast<long long>(nums[i]));									
				else				s = to_string(static_cast<long long>(nums[start])) + "->" + to_string(static_cast<long long>(nums[end]));
				
				rslt.push_back(s);
				start = i+1;
				end = i+1;
			}
		}

		if (end == start)	s = to_string(static_cast<long long>(nums[start]));									
		else				s = to_string(static_cast<long long>(nums[start])) + "->" + to_string(static_cast<long long>(nums[end]));

		rslt.push_back(s);		
		return rslt;
	}
};

int main()
{
	int n[3] = {-2147483648, 2147483645, 2147483647};
	vector<int> nums;
	for (int i = 0; i != 3; i++)	nums.push_back(n[i]);

//	nums.push_back(1);

	Solution slt;
	vector<string> rslt = slt.summaryRanges(nums);
	return 0;
}