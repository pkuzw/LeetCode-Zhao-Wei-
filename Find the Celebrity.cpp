///@file	Find the Celebrity
///@author	zhaowei
///@date	2016.03.02
///@version	1.0

#include <set>
using namespace std;

///@brief	A是否认识B
bool knows(int a, int b);

class Solution {
public:
	///@brief	给定n个人，编号是0到n-1，其中有可能有一个名人。名人的定义是所有人都认识他，但是他不认识其他人。
	//			现在给出一个辅助函数knows(a, b)来帮助你判断a是否认识b，在尽可能少的询问情况下找到这个名人。
	///@param	n	人数
	///@return	返回名人的编号，如果不存在则返回-1
	///@note	1. 两重循环，先找到所有大家都认识的人，然后看他们是否满足不认识其他人的这个条件。
	//			2. 时间复杂度为O(n^2)。应该可以更优化一些。
	int findCelebrity(int n) {
		set<int> candidates;		
		for (int i = 0; i != n; i++) {
			int know_cnt = 0;
			for (int j = 0; j != n; j++) {
				if (i == j)	continue;
				if (!knows(j, i))	break;
				else	know_cnt++;
			}
			if (know_cnt == n-1)		candidates.insert(i);
		}
		for (set<int>::iterator i = candidates.begin(); i != candidates.end(); i++) {
			for (int j = 0; j != n; j++) {
				if (j == *i)	continue;
				if (knows(*i, j)) {
					candidates.erase(i);
					break;
				}
			}
		}
		return candidates.empty() ? -1 : *candidates.begin();
	}
};

int main() {
	return 0;
}