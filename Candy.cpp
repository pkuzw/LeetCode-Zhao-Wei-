///@file	Candy
/*
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给每个孩子发糖，使得权值较邻居更高的孩子拿糖更多，计算最少要准备多少糖。每个孩子至少一颗。
	///@param	ratings	权值
	///@return	返回需要准备的最少糖果数
	/* @note	贪心法：从左向右先发一遍，给每个比他的左邻居权值高的孩子多发一颗糖；然后再从右向左遍历，给每个比他右邻居权值大且糖果数少的孩子多发一颗。
				时间复杂度为O(n)，空间复杂度为O(1)。*/
	int candy(vector<int>& ratings) {
		if (ratings.empty())		return 0;

		int child_cnt = ratings.size();
		vector<int> candys(child_cnt, 1);

		for (int i = 1; i < child_cnt; i++)
		{
			if (ratings[i] > ratings[i-1])
			{
				candys[i] = candys[i-1] + 1;
			}
		}
		for (int i = child_cnt-2; i >= 0; i--)
		{
			if (ratings[i] > ratings[i+1] && candys[i] <= candys[i+1])
			{
				candys[i] = candys[i+1] + 1;
			}
		}

		int sum = 0;
		for (int i = 0; i != candys.size(); i++)
			sum += candys[i];
		return sum;
	}
};

int main()
{
	int n[10] = {3,2,1,2,3,2,1,2,3,2};
	vector<int> ratings;
	for (int i = 0; i != 10; i++)
		ratings.push_back(n[i]);

	Solution slt;
	int rslt = slt.candy(ratings);
	return 0;
}