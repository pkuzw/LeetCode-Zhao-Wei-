///@file	Encode and Decode Strings
///@author	zhaowei
///@date	2016.02.28
///@version	1.0

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Codec {
public:

	///@note	给每一个字符串前面加上字符串长度和空格，然后在解析的时候也是根据空格来算出应该截取的长度即可。

	// Encodes a list of strings to a single string.
	string encode(vector<string>& strs) {
		string str_len;
		for (int i = 0; i != strs.size(); i++) {
			int len = strs[i].size();
			str_len = to_string(static_cast<long long>(len));
		}
	}

	// Decodes a single string to a list of strings.
	vector<string> decode(string s) {

	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));

int main() {
	string str[3] = {"hello", "world", "pku"};
	vector<string> strs;
	for (int i = 0; i != 3; i++)	strs.push_back(str[i]);
	Codec c;
	string encoded_str = c.encode(strs);
	vector<string> decoded_str = c.decode(encoded_str);
	return 0;
}