///@file	Intersection of Two Arrays
///@author	zhaowei
///@date	2016.05.19
///@version	1.0

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> rslt;
		if (nums1.empty() && nums2.empty())	return rslt;
		unordered_set<int> hash_tbl;
		for (int i = 0; i != nums1.size(); i++) {
			if (hash_tbl.find(nums1[i]) == hash_tbl.end())	hash_tbl.insert(nums1[i]);
		}
		for (int i = 0; i != nums2.size(); i++) {
			if (hash_tbl.find(nums2[i]) != hash_tbl.end()) {
				rslt.push_back(nums2[i]);
				hash_tbl.erase(nums2[i]);
			}			
		}
		return rslt;
	}
};

int main() {
	return 0;
}