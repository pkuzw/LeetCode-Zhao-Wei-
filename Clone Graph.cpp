///@file	Clone Graph
/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

///@date	2015.08.21
///@version	1.1

///@date	2016.01.10
///@version	1.2

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

class Solution_v1 {
public:
	///@brief	拷贝一个无向图
	///@param	node	无向图的一个节点
	///@return	返回拷贝后的无向图的某个节点
	/* @note	图的所有算法都跟遍历算法有关。这道题考察的是图的遍历算法。既可以用DFS，也可以用BFS。DFS既可以用递归实现，也可以用栈实现，
				BFS在实现的时候要用到队列。这里我们用递归的DFS来实现图的遍历。因为图中的每个节点的label值不一样，
				所以可以用unordered_map来保存不同的值对应的拷贝节点的指针。时间复杂度为O(V+E)，空间复杂度为O(V+E).*/
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        unordered_map<int, UndirectedGraphNode*> hash_table;
		return cloneGraph_Recur(node, hash_table);
    }

private:
	///@brief	递归DFS遍历图
	///@param	node	节点
	///@param	hash_table	保存有节点值和复制的指针的哈希表
	///@return	返回拷贝后的新节点
	UndirectedGraphNode* cloneGraph_Recur(UndirectedGraphNode* node, unordered_map<int, UndirectedGraphNode*>& hash_table)
	{
		if (!node)	return node;
		if (hash_table.find(node->label) != hash_table.end())	return hash_table[node->label];

		UndirectedGraphNode* new_node = new UndirectedGraphNode(node->label);	//	对图中没有遍历过的节点，拷贝一份
		hash_table[node->label] = new_node;										//	并在哈希表中存储一份
		for (int i = 0; i != node->neighbors.size(); i++)
		{
			new_node->neighbors.push_back(cloneGraph_Recur(node->neighbors[i], hash_table));	//	DFS，递归
		}
		return new_node;
	}
};

///@note	图遍历算法的DFS递归实现。利用hash table来保存已经遍历过的元素。
class Solution {
public:
	///@brief	拷贝一个无向图
	///@param	node	无向图的一个节点
	///@return	返回拷贝后的无向图的某个节点
	///@note	1. dfs；2. 用unordered_map<int, UndirectedGraphNode*>来保存dfs过程中已经复制（遍历）过的节点；
	//			3. 在递归时，如果这个节点已经复制过，直接取哈希表中的对应节点；否则就复制一个节点，并把它放回哈希表，然后递归的寻找该节点的邻居节点。
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		  unordered_map<int, UndirectedGraphNode*> hash_tbl;
		  return helper(node, hash_tbl);
	}
	///@brief	dfs递归辅助函数
	///@param	node		当前节点
	///@paramt	hash_tbl	哈希表
	///@return	返回拷贝的新节点
	UndirectedGraphNode* helper(UndirectedGraphNode* node, unordered_map<int, UndirectedGraphNode*>& hash_tbl) {
		if (!node)	return nullptr;
		if (hash_tbl.find(node->label) != hash_tbl.end())	return hash_tbl[node->label];		
		UndirectedGraphNode* cpy_node = new UndirectedGraphNode(node->label);
		hash_tbl[node->label] = cpy_node;
		for (int i = 0; i != node->neighbors.size(); i++) 
			cpy_node->neighbors.push_back(helper(node->neighbors[i], hash_tbl));
		return cpy_node;
	}
};

int main()
{
	return 0;
}