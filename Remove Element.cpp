///@file	Remove Element 
//			Given an array and a value, remove all instances of that value in place and return the new length.

//			The order of elements can be changed. It doesn't matter what you leave beyond the new length.
///@author	zhaowei
///@date	2015.06.11
///@version 1.0

///@date    2015.09.07
///@version 2.0

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution_v1
{
public:

	///@brief	移除数组中的指定元素
	///@param	nums	数组
	///@param	val		需要移除的值
	///@return	返回数组中剩余元素的长度
	///@note	先排序，然后将指定元素覆盖掉
	///@author	zhaowei
	///@date	2015.06.11
	int removeElement(vector<int>& nums, int val) {
	
		sort(nums.begin(), nums.end());	//	sort()只能用于能够进行随机访问的容器中，比如vector和deque，list就不可以

		int cnt = 0;	//	指定元素的重复次数
		vector<int>::iterator j = nums.begin();	//	标记指定元素的起始下标
		for (vector<int>::iterator i = nums.begin(); i != nums.end(); i++)
		{
			if (*i == val)
			{
				if (cnt == 0)	j = i;

				cnt++;
			}

			if (*i != val && cnt != 0)
				break;			
		}

		//	覆盖掉指定元素
		for (vector<int>::iterator i = j; i != nums.end()-cnt; i++)
		{
			int t = *i;
			*i = *(i+cnt);
			*(i+cnt) = t;
		}

		return nums.size()-cnt;
	}
};

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int rslt = 0;
        for (int i = 0; i != nums.size(); i++)
            if (nums[i] != val) nums[rslt++] = nums[i];
        return rslt;
    }
};

int main()
{
	vector<int> ivec;
 	for (int i = 0; i < 10; i++)
 	{
 		for (int j = i; j < 10; j++)
 		{
 			ivec.push_back(10-i);
 		}
 	}
	ivec.push_back(2);
	Solution slt;
	int newLength = slt.removeElement(ivec, 3);
	for (int i = 0; i < newLength; i++)
	{
		cout << ivec[i] << ' ';
	}
	cout << endl;
	return 0;
}