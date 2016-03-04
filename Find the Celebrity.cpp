///@file	Find the Celebrity
///@author	zhaowei
///@date	2016.03.02
///@version	1.0

///@date	2016.03.04
///@version	1.1
///@version	2.0

#include <set>
#include <stack>
using namespace std;

///@brief	A是否认识B
bool knows(int a, int b);

class Solution_v1 {
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

class Solution_v1_1 {
public:
	///@note	1. 通过两重循环找出一个不认识其他人但是其他人都认识他的人；
	//			2. 时间复杂度为O(n^2)。
	int findCelebrity(int n) {
		int i, j;
		for (i = 0; i != n; i++) {
			for (j = 0; j != n; j++) {
				if (i != j && knows(i, j))	break;
				if (i != j && !knows(j, i))	break;
			}
			if (j == n)	return i;
		}
		return -1;
	}
};

class Solution {
public:
	///@note	1. 利用栈结构，在一次遍历的情况下找到可能的名人候选；
	//			2. 然后再根据这个候选来确认其是否为名人；
	//			3. 时间复杂度为O(n)? 应该比O(n)大，空间复杂度为O(n)
	int findCelebrity(int n) {
		if (n <= 0)	return -1;
		if (n == 1)	return 0;
		stack<int> stk;
		for (int i = 0; i != n; i++)	stk.push(i);
		while (stk.size() > 1) {
			int a = stk.top();stk.pop();
			int b = stk.top();stk.pop();
			if (knows(a, b))	stk.push(b);
			else	stk.push(a);
		}
		int c = stk.top();	//	可能的候选者，进行确认
		for (int i = 0; i != n; i++)
			if (i != c && (knows(c, i) || !knows(i, c)))	return -1;
		return c;
	}
};



int main() {
	return 0;
}