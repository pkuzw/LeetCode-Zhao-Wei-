///@file	Bulb Switcher
///@author	zhaowei
///@date	2016.03.22
///@version	1.0
///@version	2.0

#include <vector>

using namespace std;

class Solution_v1 {
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

class Solution {
public:
	///@note	1. 计算小于等于n的正整数能够被多少个不重复的因子分解，这就是编号为k的灯泡的打开和关闭次数；
	//			2. 这个总次数为奇数，就是亮的，否则就是灭的；
	//			3. 时间复杂度为O(n^2)；
	//			4. TLE。
	int bulbSwitch(int n) {
		int light_bulbs = 0;
		for (int i = 1; i <= n; i++) {
			int toggle_cnt = 0;
			for (int j = 1; j * j <= i; j++) {
				if (i == 1)	{
					toggle_cnt = 1;
					continue;
				}
				else if (j * j == i) {
					toggle_cnt++;
					continue;
				}
				else if (!(i % j))	toggle_cnt += 2;
			}
			if (toggle_cnt % 2)	light_bulbs++;			
		}
		return light_bulbs;
	}
};

int main() {
	vector<int> rslt;
	Solution slt;
	for (int i = 0; i != 7; i++)
		rslt.push_back(slt.bulbSwitch(i));
	int r = slt.bulbSwitch(1000000);
	return 0;
}