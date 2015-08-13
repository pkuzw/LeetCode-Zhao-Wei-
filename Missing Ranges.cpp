///@file	Missing Ranges
/*
Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
*/
///@author	zhaowei
///@date	2015.08.13
///@version	1.0

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	///@brief	计算缺失的数值范围
	///@param	nums	排好序的数组
	///@param	lower	下限
	///@param	upper	上限
	///@return	返回缺失的数组范围
	///@note	枚举法。利用左右两个指针来标定缺失的范围。从下限开始枚举，如果没有遇到已经存在的元素，则继续向后，直到遇到存在的元素，停止移动并转换为字符串压入结果数组；然后继续
	//			向后枚举直到上限。时间复杂度为O(k)，k为数组长度，空间复杂度为O(1)。	
	vector<string> findMissingRanges_tle(vector<int>& nums, int lower, int upper) {
		vector<string> rslt;
		if (nums.empty())	//	处理数组为空的情形
		{
			if (lower < upper)
				rslt.push_back(to_string(static_cast<long long>(lower)) + "->" + to_string(static_cast<long long>(upper)));
			else if (lower == upper)
				rslt.push_back(to_string(static_cast<long long>(lower)));
			return rslt;
		}
		
		int l = lower;
		int r = lower;
		int i = 0;
		while (r != upper+1)	//	要让r == upper，这样可以处理上界。
		{
			if (i < nums.size() && r == nums[i])
			{
				if (l == nums[i])
					l++;									
				else
				{
					if (l == nums[i]-1)
						rslt.push_back(to_string(static_cast<long long>(l)));					
					else
						rslt.push_back(to_string(static_cast<long long>(l)) + "->" + to_string(static_cast<long long>(nums[i]-1)));
					l = r + 1;
				}				
				i++;
			}
			if (i < nums.size())
				r = nums[i];
			else
				r = upper+1;	//	这里不能使r++，应该是r = nums[i]
		}
		if (nums.back() != upper)	//	处理上界。如果上界出现在数组里，那么就不需要单独处理。
		{
			if (l == upper)
				rslt.push_back(to_string(static_cast<long long>(l)));
			else
				rslt.push_back(to_string(static_cast<long long>(l)) + "->" + to_string(static_cast<long long>(upper)));
		}
		return rslt;
	}
};

int main()
{
	int n[10] = {-1000000000,-9999,0,1,2,10,100,1000,999999999,1000000000};
	//int n[5] = {0, 1, 3, 50, 75};
	vector<int> nums;
 	for (int i = 0; i != 10; i++)
 		nums.push_back(n[i]);
	Solution slt;
	vector<string> rslt = slt.findMissingRanges_tle(nums, -1000000000, 1000000000);
	return 0;
}