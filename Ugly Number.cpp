///@file	Ugly Number
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	�ж�һ���������Ƿ�Ϊ�����������Ķ���Ϊһ��������������ֻ��Ϊ2��3��5��
	///@param	num	������
	///@return	����һ���������Ƿ�Ϊ����
	///@note	1. �ݹ飻
	//			2. ��num�ܱ�2��3��5�������������ܱ�����3������ʱ��ֱ����Ϊ1ʱ������true��
	//			3. ע���ų��������������Ρ�
	bool isUgly(int num) {
		if (num <= 0)	return false;
		if (num == 1)	return true;
		return (!(num % 2) && isUgly(num / 2))
			|| (!(num % 3) && isUgly(num / 3))
			|| (!(num % 5) && isUgly(num / 5));
	}
};

int main() {
	Solution slt;
	bool rslt = slt.isUgly(8);
	return 0;
}