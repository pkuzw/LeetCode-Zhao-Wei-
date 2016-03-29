///@file	Self Crossing
///@author	zhaowei
///@date	2016.03.29
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	给定一个n元组，分别依次表示向北，西，南，东四个方向的位移。判断这个路线是否会自交。
	///@param	x	4个方向的位移
	///@return	如果路线会自交，则返回true；否则返回false
	///@note	1. 分类讨论；
	//			2. 相交分成三种情况，第一种是第i条线和第i-3条线相交；
	//			3. 第二种情况是第i条线和第i-4条线相交；
	//			4. 第三种情况是第i条线和第i-5条线相交；
	//			5. 其余情况均可以对应到上面三种情况；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	bool isSelfCrossing(vector<int>& x) {
		if (x.size() < 4)	return false;
		for (int i = 3; i != x.size(); i++) {
			if (x[i] >= x[i-2] && x[i-1] <= x[i-3])	return true;
			if (i >= 4) {
				if (x[i-1] == x[i-3] && x[i-2] >= x[i-4] && x[i] + x[i-4] >= x[i-2])		return true;
			}
			if (i >= 5) {
				if (x[i-1] + x[i-5] >= x[i-3] && x[i] + x[i-4] >= x[i-2] && x[i-2] >= x[i-4] && x[i-3] >= x[i-1])	return true;
			}
		}
		return false;
	}
};

int main() {
	int n[] = {1, 1, 1, 1};
	vector<int> x;
	for (int i = 0; i != 4; i++)	x.push_back(n[i]);
	Solution slt;
	bool rslt = slt.isSelfCrossing(x);
	return 0;
}