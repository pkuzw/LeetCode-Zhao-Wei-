///@file	Zigzag Iterator
///@author	zhaowei
///@date	2016.03.03
///@version	1.0

#include <vector>
#include <iostream>
using namespace std;

class ZigzagIterator {
public:
	///@note	1. 直接在构造函数中就将输出顺序整理为1维数组，到时候直接输出即可。
	//			2. 采用坐标访问的话会比较复杂，不如这种方法高效，省空间；
	//			3. 对于多个一维数组的情况也是一样处理就可以了，在转换为1维数组时会比较麻烦。
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		matrix.push_back(v1);
		matrix.push_back(v2);
		int len1 = v1.size(), len2 = v2.size();
		len = len1 + len2;
		cnt = 0;
		int short_len = min(len1, len2);
		for (int i = 0; i != short_len; i++)
			for (int j = 0; j != 2; j++)	buff.push_back(matrix[j][i]);
		if (len1 < len2)
			for (int i = len1; i != len2; i++)	buff.push_back(matrix[1][i]);
		else if (len2 < len1)
			for (int i = len2; i != len1; i++)	buff.push_back(matrix[0][i]);
    }

    int next() {		 
		return buff[cnt++];
    }

    bool hasNext() {
		if (cnt < len)	return true;		
		return false;
    }

	vector<vector<int>> matrix;
	vector<int> buff;
	int len;
	int cnt;
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
	vector<int> v1, v2;
	for (int i = 0; i != 1; i++)	v1.push_back(i+1);
	for (int i = 0; i != 3; i++)	v2.push_back(i+1);
	ZigzagIterator zi(v1, v2);
	vector<int> rslt;
	while (zi.hasNext())	
		rslt.push_back(zi.next());
	return 0;
}