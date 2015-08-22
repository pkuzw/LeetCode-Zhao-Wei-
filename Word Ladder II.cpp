///@file	Word Ladder II
/*
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.22
///@version	2.0

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution_v1 {
public:
	typedef unordered_set<string>::iterator HashIter;	//	哈希表迭代器

	///@brief	计算所有可能的单词转换路径
	///@param	start	起始单词
	///@param	end		目标单词
	///@param	dict	词典
	///@return	返回所有可能的单词转换路径
	/* @note	利用BFS的思想来解题。将初始单词看做树的根节点，然后逐个变换单词中的字符，查着词典中是否有合适的单词与之相同。
				如果有，则将该单词记录下来，放入队列。它的父节点作为其前驱记录在pre_path中，便于后面重构路径。如果找到了一个合适的路径，
				则不必继续向后找，因为再向后找不可能比当前的转换步骤更少。此时直接退出循环。
				其中pre_path是unordered_map<string, vector<string>>类型，用来存放每个单词的前驱单词；
				hash_table是unordered_set<string>类型，记录已经寻找过哪些单词，不用再找。
				时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {		
		queue<string> que;
		que.push(start); 
		que.push("");

		bool has_found = false;	//	标记一个单词转换序列是否找到
		unordered_map<string,vector<string> >pre_path;//前驱路径
		unordered_set<string> hash_table;//保证bfs时插入队列的元素不存在重复
		while(que.empty() == false)	//	BFS
		{
			string str = que.front(), str_copy = str;
			que.pop();
			if(str != "")
			{				
				for(int i = 0; i < str.length(); i++)
				{
					char tmp = str[i];
					for(char c = 'a'; c <= 'z'; c++)
					{
						if(c == tmp)continue;
						str[i] = c;
						if(str == end)
						{
							has_found = true;
							pre_path[end].push_back(str_copy);
							//找到了一条最短路径，当前单词的其它转换就没必要
							goto END;
						}
						if(dict.find(str) != dict.end())
						{
							pre_path[str].push_back(str_copy);
							//保证bfs时插入队列的元素不存在重复
							if(hash_table.find(str) == hash_table.end())
							{
								que.push(str); 
								hash_table.insert(str);
							}
						}
					}
					str[i] = tmp;
				}
			}
			else if(que.empty() == false)//到当前层的结尾，且不是最后一层的结尾
			{
				if(has_found)	break;


				//避免进入死循环，把bfs上一层插入队列的元素从字典中删除
				for(HashIter ite = hash_table.begin(); ite != hash_table.end(); ite++)
					dict.erase(*ite);
				hash_table.clear();
				que.push("");
			}
END: ;
		}
		vector<vector<string>> res;
		if(pre_path.find(end) == pre_path.end())	return res;

		vector<string> tmpres;
		tmpres.push_back(end);
		ConstructResult(pre_path, res, tmpres, start, end);

		return res;
	}

private:
	///@brief	从前驱路径中回溯构造path
	///@param	pre_path	前驱路径
	///@param	res		路径数组
	///@param	tmpres	当前已经构造的路径
	///@param	start	起始单词
	///@param	end		终止单词
	///@return	无
	void ConstructResult(unordered_map<string,vector<string>> &pre_path, vector<vector<string>> &res, vector<string> &tmpres, string &start, string &end)
	{
		if(start == end)	//	如果已经构造好了一条路径
		{
			reverse(tmpres.begin(), tmpres.end());	//	颠倒次序后加入结果数组
			res.push_back(tmpres);
			reverse(tmpres.begin(), tmpres.end());	//	再颠倒回来，以便回溯继续构造
			return;
		}

		vector<string> &pre = pre_path[end];	//	递归的构造路径
		for(int i = 0; i < pre.size(); i++)
		{
			tmpres.push_back(pre[i]);
			ConstructResult(pre_path, res, tmpres, start, pre[i]);
			tmpres.pop_back();
		}
		return;
	}
};

/* @note	BFS. 队列用来保存宽度搜索的单词节点；
			哈希表用来保存已经有哪些节点已经搜索过，不必再次搜索，相当于剪枝；
			前驱路径表用来重构路径。
*/
class Solution {
public:	
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		queue<string> que;
		que.push(start);
		que.push("");
		bool has_found = false;
		unordered_map<string, vector<string>> pre_path;
		unordered_set<string> ht;
		while (!que.empty())
		{
			string frt = que.front();
			string cpy = frt;
			que.pop();
			if (frt != "")
			{
				string tmp = frt;
				for (int i = 0; i != frt.size(); i++)
				{
					for (char j = 'a'; j <= 'z'; j++)
					{
						if (frt[i] == j)	continue;
						frt[i] = j;
						if (frt == end)
						{
							has_found = true;
							pre_path[frt].push_back(cpy);
							goto END;
						}

						if (dict.find(frt) != dict.end())
						{
							pre_path[frt].push_back(cpy);
							if (ht.find(frt) == ht.end())
							{
								que.push(frt);
								ht.insert(frt);
							}
						}
					}
					frt = tmp;
				}
			}
			else
			{
				if (!que.empty())
				{
					if (has_found)	break;
					for (unordered_set<string>::iterator iter = ht.begin(); iter != ht.end(); iter++)
						dict.erase(*iter);
					ht.clear();
					que.push("");
				}
			}
			END:;
		}
		vector<vector<string>> rslt;
		vector<string> tmp_rslt;
		if (pre_path.find(end) == pre_path.end())	return rslt;
		tmp_rslt.push_back(end);
		constructPath(rslt, tmp_rslt, pre_path, start, end);
		return rslt;
	}
private:
	void constructPath(vector<vector<string>>& rslt, vector<string>& tmp_rslt, unordered_map<string, vector<string>>& pre_path, string start, string end)
	{
		if (start == end)
		{
			reverse(tmp_rslt.begin(), tmp_rslt.end());
			rslt.push_back(tmp_rslt);
			reverse(tmp_rslt.begin(), tmp_rslt.end());
			return;
		}
		vector<string>& pre = pre_path[end];
		for (int i = 0; i != pre.size(); i++)
		{
			tmp_rslt.push_back(pre[i]);
			constructPath(rslt, tmp_rslt, pre_path, start, pre[i]);
			tmp_rslt.pop_back();
		}
	}
};

int main()
{
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("lot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("log");

	Solution slt;
	vector<vector<string>> rslt = slt.findLadders("hit", "cog", dict);
	return 0;
}