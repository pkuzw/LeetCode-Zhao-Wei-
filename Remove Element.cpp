///@file	Remove Element 
//			Given an array and a value, remove all instances of that value in place and return the new length.

//			The order of elements can be changed. It doesn't matter what you leave beyond the new length.
///@author	zhaowei
///@date	2015.06.11
///@version 1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date    2016.04.07
///@version 2.2

///@date    September 9, 2018
///@version 3.0
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

class Solution_v2 {
public:
	///@brief	移除数组中的指定元素
	///@param	nums	数组，元素未排序
	///@param	val		指定值
	///@return	返回新数组的长度
	///@note	用一个变量保存新数组的长度，初始化为0。遍历数组，如果遇到和指定值相同的元素，则继续向后遍历，否则就将该元素赋值给新数组长度下标处，并将长度自增1.
	//			时间复杂度为O(n)，空间复杂度为O(1)。
    //          如果原始数组中val的重复元素比较少的话，性能会不如v3版本；相反，如果val的重复次数比较多的话，v2相对性能更好一些。
    int removeElement(vector<int>& nums, int val) {
		int j = 0;
		for (int i = 0; i != nums.size(); i++) {
			if (nums[i] != val) {
				nums[j] = nums[i];
				j++;
			}
		}
		return j;
    }
};

class Solution_v2_2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int j = 0;
        for (int i = 0; i != nums.size(); i++)
            if (nums[i] != val) nums[j++] = nums[i];
        return j;
    }
};

class Solution {
public:
    ///@brief   将包含有重复元素的数组的指定元素去除掉，将其放置在数组的末尾即可。
    ///@param   nums    数组
    ///@param   val     指定元素
    ///@return  返回去重后数组的长度
    ///@note    1. 设置两个循环变量i, j，其中i用于逆序遍历整个数组， j用来逆序标记准备和重复元素置换的合法元素的下标
    //          2. 逆序遍历整个数组，如果待去重元素已经排在数组末尾，则跳过；否则就用最末尾的合法元素和待去重元素进行置换。
    //          3. 时间复杂度为O(n)，空间复杂度为O(1)。其中n为数组的长度.
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty())   return 0;
        int j = nums.size() - 1;    //  tag the last element not equal to val
        while (j >= 0 && nums[j] == val) j--;
        int i = j;    //  tag the element equal to val
        while (i >= 0) {
            if (nums[i] != val) {
                i--;
                continue;
            }
            swap(nums[i--], nums[j--]);
            while (nums[j] == val && j >= 0) j--;
        }
        return j + 1;
    }
};

int main()
{
	vector<int> ivec;
// 	for (int i = 0; i < 10; i++)
//  {
// 		for (int j = 0; j != 4; j++)
//			ivec.push_back(j);
// 	}
    ivec.push_back(3);
    ivec.push_back(2);
    ivec.push_back(2);
    ivec.push_back(3);
	Solution slt;
	int newLength = slt.removeElement(ivec, 3);
    cout << "length: " << newLength << endl;
	for (int i = 0; i < newLength; i++)
	{
		cout << ivec[i] << ' ';
	}
	cout << endl;
	return 0;
}
