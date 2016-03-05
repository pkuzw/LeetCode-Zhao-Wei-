///@file	Expression Add Operators
///@author	zhaowei
///@date	2016.03.03
///@version	1.0

///@date	2016.03.05
///@version	1.1
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	// cur: {string} expression generated so far.
	// pos: {int}    current visiting position of num.
	// cv:  {long}   cumulative value so far.
	// pv:  {long}   previous operand value.
	// op:  {char}   previous operator used.
	void dfs(std::vector<string>& rslt, const string& num, const int target, string cur, int pos, const long cv, const long pv, const char op) {
		if (pos == num.size() && cv == target) {
			rslt.push_back(cur);
			return;
		}
		for (int i = pos + 1; i <= num.size(); i++) {
			string t = num.substr(pos, i - pos);
			long now = stol(t);
			if (to_string(static_cast<long long>(now)).size() != t.size())	continue;
			dfs(rslt, num, target, cur + "+" + t, i, cv + now, now, '+');
			dfs(rslt, num, target, cur + "-" + t, i, cv - now, now, '-');
			dfs(rslt, num, target, cur + "*" + t, i, op == '+' ? cv - pv + pv * now : op == '-' ? cv + pv - pv * now : pv * now, pv * now, op);
		}
	}

 	vector<string> addOperators(string num, int target) {
		vector<string> rslt;
		if (num.empty())	return rslt;
		for (int i = 1; i <= num.size(); i++) {
			string s = num.substr(0, i);
			long cur = stol(s);
			if (to_string(static_cast<long long>(cur)).size() != s.size())	continue;
			dfs(rslt, num, target, s, i, cur, cur, '#');
		}
		return rslt;
 	}
};

int main() {
	Solution slt;
	vector<string> rslt = slt.addOperators("2147483648", -2147483648);
	return 0;
}