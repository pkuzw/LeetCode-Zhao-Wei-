///@file	Number of 1 Bits
/*
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer '11' has binary representation 00000000000000000000000000001011, so the function should return 3.
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.21
///@version	2.0
  
#include <cstdint>	//	uint32_t
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	统计一个unsigned int的二进制表示中有多少个'1'
	///@param	n	十进制的unsigned int参数
	///@return	返回n中的二进制'1'的个数
	///@note	开一个数组来保存2^k幂，然后用n来从高到低减这些幂，就能够统计出它其中有多少1.时间复杂度为O(logn)，空间复杂度为O(1)。
	int hammingWeight(uint32_t n) {
		uint32_t cnt[32];
		uint32_t k = 1;
		for (int i = 0; i != 32; i++)
			cnt[i] = k << i;
		
		int num_of_1 = 0;
		for (int i = 31; i >= 0; i--)
		{
			if (n >= cnt[i])
			{
				n -= cnt[i];
				num_of_1++;
			}
		}
		return num_of_1;
	}
};

class Solution_v1_1 {
public:
	int hammingWeight(uint32_t n) {
		vector<uint32_t> pow_of_2;
		for (int i = 0; i <= 31; i++)
			pow_of_2.push_back(1 << i);

		int bit_1_cnt = 0;
		for (int i = pow_of_2.size()-1; i >= 0; i--)
		{
			if (n >= pow_of_2[i])
			{
				n -= pow_of_2[i];
				bit_1_cnt++;
			}
		}
		return bit_1_cnt;
	}
};

class Solution {
public:
    ///@brief   计算32位整型变量中的1位数目
    ///@param   n   32位无符号变量
    ///@return  返回其中的1的数目
    ///@note    1. 位操作，将n不断的右移，以统计其中的1数目即可。
    int hammingWeight(uint32_t n) {
        if (!n) return 0;
        int k = 32;
        int rslt = 0;
        while (k--) {
            rslt += n & 1;
            n >>= 1;
        }
        return rslt;
    }
};

int main()
{
	uint32_t n = INT_MAX * 2 + 1;
	Solution slt;
	int rslt = slt.hammingWeight(n);
	return 0;
}