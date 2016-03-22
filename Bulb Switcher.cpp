///@file	Bulb Switcher
///@author	zhaowei
///@date	2016.03.22
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	打开或关闭灯泡。一共n盏灯，第i轮打开或关闭编号为第i的倍数的灯泡，问在n轮之后有多少盏灯是亮的。初始所有灯泡是熄灭的
	///@param	n	灯泡数目和开关的轮数
	///@return	返回剩余亮着的灯泡数目
	///@note	1. 模拟；
	//			2. 用一个数组来模拟灯泡的开关，模拟n轮，最后统计亮着的灯泡数目；
	//			3. 时间复杂度为O(n^2)，其中n为灯泡数目。
	//			4. TLE.
	int bulbSwitch(int n) {
		if (!n)	return 0;
		vector<bool> bulbs(n, false);
		for (int i = 1; i <= n; i++) {	//	一共n轮
			for (int j = i; j <= n; j += i) {
				bulbs[j-1] = bulbs[j-1] ? false : true;					
			}
		}
		int light_bulbs = 0;
		for (int i = 0; i != n; i++)
			if (bulbs[i])	light_bulbs++;
		return light_bulbs;
	}
};

int main() {
	Solution slt;
	for (int i = 0; i != 7; i++)
		int rslt = slt.bulbSwitch(i);
	return 0;
}