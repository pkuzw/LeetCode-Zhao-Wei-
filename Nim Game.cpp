///@file	Nim Game
///@author	zhaowei
///@date	2016.03.09
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	取石子游戏，一次能取1-3枚石子，问给定石子数，判定在先手情况下是否必胜
	///@param	n	石子数
	///@return	如果必胜，返回true；否则返回false。
	///@note	1. 递归法，TLE。
	bool canWinNim(int n) {
		int turn_cnt = 0;	//	记录该谁出手
		return helper(n, turn_cnt);
	}

	bool helper(int n, int turn_cnt) {
		if (n <= 3) {
			if (!(turn_cnt % 2))	return true;
			else {
				if (helper(n-1, turn_cnt+1) || helper(n-2, turn_cnt+1) || helper(n-3, turn_cnt+1))	return true;
			}
		}
		else {
			if (!helper(n-1, turn_cnt+1) || !helper(n-2, turn_cnt+1) || !helper(n-3, turn_cnt+1))	return true;
		}
		return false;		
	}
};

int main() {
	Solution slt;
	bool rslt[11];
	for (int i = 1; i <= 100; i++)
		rslt[i] = slt.canWinNim(i);
	return 0;
}