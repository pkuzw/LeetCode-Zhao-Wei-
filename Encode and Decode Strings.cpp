///@file	Encode and Decode Strings
///@author	zhaowei
///@date	2016.02.28
///@version	1.0

///@date	2016.03.02
///@version	1.1

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Codec_v1 {
public:

	///@note	给每一个字符串前面加上字符串长度和空格，然后在解析的时候也是根据空格来算出应该截取的长度即可。

	// Encodes a list of strings to a single string.
	string encode(vector<string>& strs) {
		string encoded_string;
		string str_len;
		for (int i = 0; i != strs.size(); i++) {
			int len = strs[i].size();
			str_len = to_string(static_cast<long long>(len));
			encoded_string += str_len + " " + strs[i];
		}
		return encoded_string;
	}

	// Decodes a single string to a list of strings.
	vector<string> decode(string s) {
		vector<string> decoded_string;
		int i = 0, j = 0;
		while (i != s.size()) {
			if (s[i] == ' '){
				int len = stoi(s.substr(j, i));
				decoded_string.push_back(s.substr(i+1, len));
				i += len + 1;
				j = i;
			}
			else i++;
		}
		return decoded_string;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));

class Codec {
public:

	// Encodes a list of strings to a single string.
	string encode(vector<string>& strs) {
		string ec_str;
		for (int i = 0; i != strs.size(); i++) ec_str += to_string(static_cast<long long>(strs[i].size())) + " " + strs[i];
		return ec_str;
	}

	// Decodes a single string to a list of strings.
	vector<string> decode(string s) {
		vector<string> dc_str;
		int i = 0, j = 0;
		while (i != s.size()) {
			while (s[i] != ' ') i++;
			int len = stoi(s.substr(j, i-j));			
			dc_str.push_back(s.substr(i + 1, len));
			i += len + 1;
			j = i;			
		}
		return dc_str;
	}
};

int main() {
	string str[3] = {"hello world", "world zhaowei", "pku sess eecs"};
	vector<string> strs;
	for (int i = 0; i != 3; i++)	strs.push_back(str[i]);
	Codec c;
	string encoded_str = c.encode(strs);
	vector<string> decoded_str = c.decode(encoded_str);
	return 0;
}