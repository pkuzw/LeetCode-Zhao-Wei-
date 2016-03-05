///@file	Zigzag Iterator
///@author	zhaowei
///@date	2016.03.03
///@version	1.0

///@date	2016.03.05
///@version	2.0

#include <vector>
#include <iostream>
using namespace std;

class ZigzagIterator_v1 {
public:
	///@note	1. 直接在构造函数中就将输出顺序整理为1维数组，到时候直接输出即可。
	//			2. 采用坐标访问的话会比较复杂，不如这种方法高效，省空间；
	//			3. 对于多个一维数组的情况也是一样处理就可以了，在转换为1维数组时会比较麻烦。
    ZigzagIterator_v1(vector<int>& v1, vector<int>& v2) {
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

class ZigzagIterator {
public:
	///@note	1. 把输入的一维数组先压入成员数据中的二维数组，然后利用成员变量中的行列号进行访问；
	//			2. 可以处理k个一维数组的情况。
	ZigzagIterator(vector<vector<int>> v) {
		total_cnt = 0;
		for (int i = 0; i != v.size(); i++) {
			matrix.push_back(v[i]);
			total_cnt += v[i].size();
		}		
		cur_cnt = 0;
		row_indx = 0;
		col_indx = 0;
	}

	int next() {
		int nxt_val = 0;
		if (col_indx < matrix[row_indx].size()) {
			if (row_indx < matrix.size()) {				
				nxt_val = matrix[row_indx][col_indx];
				if (row_indx == matrix.size() - 1) {
					row_indx = 0;
					col_indx++;
				}
				else	row_indx++;
				return nxt_val;				
			}
		}
		while (row_indx < matrix.size() && col_indx >= matrix[row_indx].size()) {
			if (row_indx == matrix.size() - 1) {
				row_indx = 0;
				col_indx++;
			}
			else	row_indx++;
		}

		nxt_val = matrix[row_indx][col_indx];
		if (row_indx == matrix.size() - 1) {
			row_indx = 0;
			col_indx++;
		}
		else	row_indx++;
		return nxt_val;
	}

	bool hasNext() {
		if (cur_cnt++ != total_cnt)	return true;
		return false;
	}

	vector<vector<int>>	matrix;
	int total_cnt;
	int cur_cnt;
	int row_indx;
	int col_indx;
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
	vector<vector<int>> v;
	vector<int> v1[6];
	for (int i = 0; i != 6; i++) {
		for (int j = 0; j != 2; j++) {
			if (i % 2)	v1[i].push_back((i+1)*(j+1));
			else {
				v1[i].push_back(3*(i+1)*(j+1));
				v1[i].push_back(4*(i+1)*(j+1));
			}
		}
		v.push_back(v1[i]);
	}	
	
	ZigzagIterator zi(v);
	vector<int> rslt;
	while (zi.hasNext())	
		rslt.push_back(zi.next());
	return 0;
}