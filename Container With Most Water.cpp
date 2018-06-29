///@brief	Container With Most Water. 有n个第一象限内的的点，找出能装最多水的由(i, yi), (i, 0), (j, 0)和(j, yj)组成的桶。
///@note	因为木桶装水的量取决于最短的那块木板，所以我们要找的应该是矩形面积最大的两个点
///@author	zhaowei
///@date	2015.06.02
///@version 1.0

///@date    2015.09.07
///@version 1.1

///@date	2015.09.14
///@version	1.2

///@date	2016.04.02
///@version	1.3

///@date    June 29, 2018
///@version 1.4


#include <iostream>
#include <vector>
using namespace std;

class Solution_v1
{
public:
	///@brief	求最大矩形面积
	///@param	height	n个点的y坐标组成的数组
	///@return	返回最大的矩形面积
	///@author	zhaowei
	///@date	2015.06.02
	///@version 1.0
	///@note	贪心法，从两边向中间计算，遇到面积更大的矩形就替代之。时间复杂度O(n), 空间复杂度O(1).
	int maxArea(vector<int>& height) {
		int i = 0;					//	数组起始下标
		int j = height.size()-1;		//	数组末尾下标
		int rslt = INT_MIN;
		while (i < j)
		{
			int h = min(height[i], height[j]);	//	短边决定了木桶的容积
			rslt = max(rslt, h * (j-i));			//	比较当前木桶的面积和目前最大面积

			//	从两边向中间逐个遍历
			if (height[i] < height[j])
			{
				i++;
			}
			else
				j--;
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	给定一组高度数组，计算所围成的最大矩形面积
	///@param	height	高度数组
	///@return	返回最大面积
	///@note	1.贪心法。
    //          2. 将左端点置为0，右端点置为height[n-1]，n为height.size()。因为初始时容器的底最宽，为了使后续的容器体积更大，其边长应该更高。
    //             所以应该将两边更小的一端向中心移动，这样才能保证更大的边长被保留，后续可能遇到比现有边长更大的边，那么保留下较长边就使得有可能体积增大。
    //          3. 贪心法的正确性还有待进一步学习。
    //          4. 时间复杂度为O(n)，空间复杂度为O(1)，n为height的大小。
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1, rslt = 0;
        while (left < right) {
            int h = min(height[left], height[right]);
            int w = right - left;
            rslt = max(rslt, h * w);
            if (height[left] < height[right])   left++;
            else    right--;
        }
        return rslt;
    }
};

int main()
{
	return 0;
}
