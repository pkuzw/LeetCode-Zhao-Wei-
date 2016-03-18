///@file	Range Sum Query - Mutable
///@author	zhaowei
///@date	2016.03.17
///@version	1.0

///@date	2016.03.18
///@version	2.0

#include <vector>
#include <numeric>

using namespace std;

///@note	1. 类似Range Sum Query - Immutable的算法，利用partial_sum，在update后及时更新psum的值。
//			2. TLE
class NumArray_v1 {
public:
	NumArray_v1(vector<int> &nums) {
		for (int i = 0; i <= nums.size(); i++)	psum.push_back(0);
		partial_sum(nums.begin(), nums.end(), psum.begin()+1);
	}

	void update(int i, int val) {
		int n_val = psum[i+1] - psum[i];
		for (int k = i + 1; k < psum.size(); k++)	psum[k] += val - n_val;
	}

	int sumRange(int i, int j) {
		return psum[j+1] - psum[i];
	}

	vector<int> psum;
};

///@note	1. 对于区间求和，求最值问题，采用线段树是一个在事件和空间两方面都比较优的选择；
//			2. 因为如果只是每次在查询的时候做操作，当数据量增大，查询频率高时，时间复杂度为O(nk)，其中n为数组大小，k为查询次数；
//			3. 如果是将区间内的和或者最值通过预处理已经存储好了，那么在空间复杂度方面又比较高，为O(n^2)；
//			4. 线段树是将数组按照区间的起止下标为界，保存该区间内的和或者最值，然后左右子树将区间对半分开；
//			线段树的叶子节点就是原数组的元素，那么在查询时，预处理需要O(n)的时间，查询时间为O(logn)，更新的复杂度也为O(logn)，空间复杂度为O(n)。

struct SegmentTreeNode {
	int sum;
	int start;
	int end;
	SegmentTreeNode* left;
	SegmentTreeNode* right;

	SegmentTreeNode(int a, int b) : start(a), end(b), sum(0), left(nullptr), right(nullptr) {}
};

class NumArray {
public:
	NumArray(vector<int> &nums) {
		root = buildTree(nums, 0, nums.size() - 1);
	}
		
	void update(int i, int val) {
		modifyTree(root, i, val);
	}

	int sumRange(int i, int j) {
		return queryTree(root, i, j);
	}

	SegmentTreeNode* buildTree(vector<int> nums, int start, int end) {
		if (start > end)	return nullptr;
		SegmentTreeNode* root = new SegmentTreeNode(start, end);
		if (start == end) {
			root->sum = nums[start];
			return root;
		}
		int mid = (start + end) / 2;
		root->left = buildTree(nums, start, mid);
		root->right = buildTree(nums, mid + 1, end);
		root->sum = root->left->sum + root->right->sum;
		return root;
	}

	int modifyTree(SegmentTreeNode* root, int indx, int val) {
		if (!root)	return 0;
		int diff = 0;
		if (root->start == indx && root->end == indx) {
			diff = val - root->sum;
			root->sum = val;
			return diff;
		}
		int mid = (root->start + root->end) / 2;
		if (indx <= mid)	diff = modifyTree(root->left, indx, val);
		else	diff = modifyTree(root->right, indx, val);
		root->sum += diff;
		return diff;
	}

	int queryTree(SegmentTreeNode* root, int start, int end) {
		if (!root)	return 0;
		if (root->start == start && root->end == end)	return root->sum;
		int mid = (root->start + root->end) / 2;
		if (end <= mid)	return queryTree(root->left, start, end);
		if (start > mid)	return queryTree(root->right, start, end);
		return queryTree(root->left, start, mid) + queryTree(root->right, mid + 1, end);
	}

	SegmentTreeNode* root;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);

int main() {
	int n[3] = {1, 3, 5};
	vector<int> nums;
	for (int i = 0; i < 3; i++)	nums.push_back(n[i]);
	NumArray numArray(nums);
	int rslt = numArray.sumRange(0, 1);
	numArray.update(1, 10);
	rslt = numArray.sumRange(1, 2);

	return 0;
}