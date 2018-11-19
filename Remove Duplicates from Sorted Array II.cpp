///@file	Remove Duplicates from Sorted Array II 
/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. 
It doesn't matter what you leave beyond the new length.
*/
///@author	zhaowei
///@date	2015.07.15
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.07
///@version	3.0

///@date	2016.04.30
///@version	3.1

///@date    November 19, 2018
///@version 3.2

#include <iostream>
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	在一个已经排好序的数组中，如果只允许同一个元素出现两次，生成新数组并计算新数组的长度
	///@param	nums	已经排好序的数组
	///@return	新数组的长度
	///@note	设置一个统计重复元素出现次数的变量，每当重复元素出现的次数超过2，就将其后面的元素向前移动一位，此时重复元素的下标需要随之改变。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	int removeDuplicates(vector<int>& nums) {
		int len = nums.size();	//	数组的长度，随着重复元素被删除动态变化
		if (len <= 2)	//	当数组的长度小于等于2时，直接返回数组的长度
		{
			return len;
		}
				
		int dup_cnt = 1;
		for (int i = 0; i < len-1; i++)
		{
			int j = i+1;
			dup_cnt = 1;	//	统计元素重复出现的次数
			int delete_times = 0;	//	重复元素的总次数，即数组向前移动过多少次
			while (j-delete_times < len && nums[i] == nums[j-delete_times])	//	因为发现超过两次的重复元素后，都将后面的元素向前移动一位，故相应的j下标也需要减去移动的次数
			{
				dup_cnt++;
				j++;
				if (dup_cnt > 2)
				{
					deleteElement(nums, j-delete_times-1);
					len--;
					delete_times++;
				}
			}
			i = j-delete_times-1;
		}	
		return len;
	}

private:
	///@brief	将数组中指定下标后的所有元素向前移动一位
	///@param	nums	数组
	///@param	indx	指定下标
	///@return	无
	void deleteElement(vector<int> &nums, const int indx)
	{
		for (int i = indx+1; i != nums.size(); i++)
		{
			nums[i-1] = nums[i];
		}
		return;
	}
};

class Solution_v2 {
public:
	///@brief	删除数组中重复出现超过2次的元素的多余次数
	///@note	时间复杂度为O(n)，空间复杂度为O(n)。不符合题目对于空间复杂度的要求，应该降到O(1)
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())	return 0;
		int rslt = 0;
		vector<int> tmp;
		int i = 0, j = 0;
		for (i = 0; i < nums.size(); i = j)
		{
			int cnt = 0;
			j = i;
			while (j < nums.size() && nums[j] == nums[i])
			{
				if (cnt < 2)	tmp.push_back(nums[j]);
				cnt++;
				j++;
			}
			rslt += cnt > 2 ? 2 : cnt;
		}	
		nums = tmp;
		return rslt;
	}
};

class Solution_v3 {
public:
	///@brief	将排好序的数组去重，当有相同元素出现时，最多留下2个
	///@param	nums	排好序的数组
	///@return	返回新数组的长度
	///@note	1. 要求空间复杂度为O(1)；2. 设整个数组中应该被移除的多余元素总数为cnt；3. 因为每个重复元素不能超过两个，所以当超过两个时，就用
	//			后面的元素覆盖掉超出的元素；4. 时间复杂度为O(n)，空间复杂度为O(1)。
	int removeDuplicates(vector<int>& nums) {
		int n = nums.size(), cnt = 0;
		for (int i = 2; i < n; i++) {
			if (nums[i] == nums[i - 2 - cnt])	cnt++;
			else	nums[i - cnt] = nums[i];
		}
		return n - cnt;
	}
};

class Solution {
public:
    ///@brief   给定一个已经排好序的数组，里面可能会有重复元素，对于这些重复元素，相同的最多保留两个，删除剩余的。要求空间复杂度为O(1)。
    ///@param   nums    排好序的数组
    ///@return  返回删除多余重复元素后数组的长度。
    ///@note    1. 枚举法；
    //          2. 从前向后遍历数组，如果nums[i-2-cnt] == nums[i]，那么说明元素相同，自增cnt；否则，用nums[i]替换掉nums[i-cnt]，最后返回n - cnt即可。
    //          3. cnt应该是被删除的多余元素的累计值；
    //          4. 时间复杂度为O(n)，空间复杂度为O(1)。其中n为数组的长度。
	int removeDuplicates(vector<int>& nums) {
        if (nums.empty())   return 0;
        int len = nums.size(), cnt = 0; // cnt是整个数组中应该被删除的元素的累计总数。
        for (int i = 2; i < len; i++) {
            if (nums[i] == nums[i-2-cnt])   cnt++;
            else nums[i-cnt] = nums[i];
        }
        return len - cnt;
    }
};

int main()
{
	Solution slt;
	vector<int> test;
 	test.push_back(1);
 	test.push_back(2);
	test.push_back(2);
	test.push_back(3);
	test.push_back(3);
	test.push_back(4);
	test.push_back(4);
	test.push_back(4);
	int new_len = slt.removeDuplicates(test);

	return 0;
}
