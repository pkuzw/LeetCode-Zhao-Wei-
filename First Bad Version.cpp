///@file	First Bad Version
///@author	zhaowei
///@date	2016.03.02
///@version	1.0

#include <vector>
using namespace std;

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
	///@brief	给出从1到n的一系列版本，其中i + 1版依赖于i版，前一个版本的损坏会导致后续版本的损坏。
	//			这n个版本中至少最后一个版本是坏的，找出第一个坏的版本。
	///@param	n	版本数目
	///@return	返回最早的坏版本号
	///@note	1. 二分查找；
	///			2. 注意中间值的溢出，用long long类型来保存中间变量。
	int firstBadVersion(int n) {
		if (n <= 0)	return 0;
		long long l = 1, r = n;
		while (l <= r) {
			long long mid = (l + r) / 2;
			if (isBadVersion(mid) && (mid == 1 || !isBadVersion(mid - 1)))	return mid;
			else if (!isBadVersion(mid)) l = mid + 1;			
			else	r = mid - 1;
		}
		return l;
	}
};

int main() {
	return 0;
}