///@file	Remove Duplicate Letters
///@author	zhaowei
///@date	2016.03.21
///@version	1.0

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	�Ƴ��ַ����еĶ����ַ���ʹ���ַ�������������п�������ַ����а�����ĸ˳�������ǰ����һ����
	///@param	s	�ַ���
	///@return	���ؽ���ַ���
	///@note	1. ������
	//			2. ά���������飬һ���������ڱ����ַ������ַ��ĳ��ִ�������һ������������ַ��Ƿ��Ѿ������ڽ�������У�
	//			3. �����ǰ�ַ��Ƚ���ַ�����ĩβ�ַ�С�������ĳ��ִ�����Ϊ0����һֱ������ַ�����β��������Ȼ��ѹ�뵱ǰ�ַ���
	//			4. ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(k)��kΪ�ַ���������Ŀ��
	string removeDuplicateLetters(string s) {
		vector<int> count(26, 0);
		vector<bool> visited(26, false);
		string rslt = "";
		if (s.empty())	return rslt;
		for (int i = 0; i != s.size(); i++)	count[s[i]-'a']++;
		for (int i = 0; i != s.size(); i++) {
			count[s[i]-'a']--;
			if (visited[s[i]-'a'])	continue;
			while (!rslt.empty() && rslt.back() > s[i] && count[rslt.back()-'a'] > 0) {
				visited[rslt.back()-'a'] = false;
				rslt.pop_back();				
			}
			rslt.push_back(s[i]);
			visited[s[i]-'a'] = true;
		}
		return rslt;
	}
};

int main() {
	string rslt;
	Solution slt;
	string s = "cbacdcbc";
	rslt = slt.removeDuplicateLetters(s);
	return 0;	
}