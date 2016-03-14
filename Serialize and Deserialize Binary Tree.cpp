///@file	Serialize and Deserialize Binary Tree
///@author	zhaowei
///@date	2016.03.14
///@version	1.0

#include <string>
using namespace std;

/**
 * Definition for a binary tree node.
**/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

///@note	1. 要求不能使用类成员变量，全局变量和静态变量来保存序列；
//			2. 递归；
//			3. 前序遍历，然后再倒插回去；
//			4. string::find(char ch)是返回ch在string中第一次出现的位置；
//			5. 在deserialize函数中，参数应该是传引用，而接口又定义好了非引用的形参，可以通过再套一层函数来达到目的。
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {		
        if (!root)	return "#";
		return to_string(static_cast<long long>(root->val)) + "," + serialize(root->left) + "," + serialize(root->right);
    }


	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		return myDeserialize(data);
	}

    ///@brief	将一串前序遍历的二叉树序列字符串转换成二叉树
	///@param	data	字符串
	///@return	返回二叉树的根节点
    TreeNode* myDeserialize(string& data) {
		if (data[0] == '#') {
			if (data.size() > 1)	data = data.substr(2);			
			return nullptr;
		}
		TreeNode* node = new TreeNode(helper(data));
		node->left = myDeserialize(data);
		node->right = myDeserialize(data);
		return node;
    }

	///@brief	将data的第一个字符子串转换成数字，同时将data截短
	///@param	data	字符串
	///@return	返回data的第一个数字
	int helper(string& data) {
		int pos = data.find(',');
		int num = stoi(data.substr(0, pos));
		data = data.substr(pos + 1);
		return num;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {
	TreeNode* node[5];
	for (int i = 1; i <= 5; i++) {
		node[i-1] = new TreeNode(i);
	}
	node[0]->left = node[1];
	node[0]->right = node[2];
	node[1]->left = node[3];
	node[1]->right = node[4];

	Codec cd;
	string rslt = cd.serialize(node[0]);
	TreeNode* root = cd.deserialize(rslt);
	return 0;
}