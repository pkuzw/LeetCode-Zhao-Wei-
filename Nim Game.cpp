///@file	Nim Game
///@author	zhaowei
///@date	2016.03.09
///@version	1.0
///@version	2.0

#include <vector>
using namespace std;

class Solution_v1 {
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

class Solution_v2 {
public:
	///@note	1. 递归法超时，考虑用动态规划
	//			2. 设dp[i]表示石子为i个时，先手能否获胜。初始条件为dp[1] = dp[2] = dp[3] = 1；
	//			3. 递推关系式为dp[i] = dp[i-3] && dp[i-2] && dp[i-1] ? 0 : 1;
	//			4. 时间复杂度为O(n)，空间复杂度为O(n)，后续可以改进到O(1)。
	//			5. 还是报tle
	bool canWinNim(int n) {
		if (n < 4)	return true;
		vector<bool> dp(n+1, false);
		dp[1] = dp[2] = dp[3] = true;
		for (int i = 4; i <= n; i++)	dp[i] = dp[i-1] && dp[i-2] && dp[i-3] ? false : true;
		return dp[n];
	}
};

int main() {
	Solution slt;
	bool rslt[101];
	for (int i = 1; i <= 100; i++)
		rslt[i] = slt.canWinNim(i);
	return 0;
}