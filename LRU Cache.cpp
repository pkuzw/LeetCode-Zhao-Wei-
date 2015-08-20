///@file	LRU Cache
/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/
///@author	zhaowei
///@date	2015.07.30
///@versio	1.0

///@date	2015.08.20
///@version	2.0

#include <unordered_map>
#include <list>

using namespace std;

/*
为了保持cache的性能，使查找，插入，删除都有较高的性能，我们使用双向链表（std::list）和哈希表（std::unordered_map）作为cache的数据结构，

因为：
双向链表插入删除效率高（单向链表插入和删除时，还要查找节点的前节点）
哈希表保存每个节点的地址，可以基本保证在O(1)时间内查找节点

具体实现细节：
越靠近链表头部，表示节点上次访问距离现在时间最短，尾部的节点表示最近访问最少
查询或者访问节点时，如果节点存在，把该节点交换到链表头部，同时更新hash表中该节点的地址
插入节点时，如果cache的size达到了上限，则删除尾部节点，同时要在hash表中删除对应的项。新节点都插入链表头部。    
*/

class LRUCache_v1{
private:
	struct CacheNode
	{
		int key;
		int value;
		CacheNode(int k, int v):key(k), value(v){}
	};

	list<CacheNode> cacheList;
	unordered_map<int, list<CacheNode>::iterator>cacheMap;
	int size;

public:
	///@brief	设置缓存大小
	LRUCache_v1(int capacity) {
		size = capacity;
	}

	///@brief	访问缓存中元素
	int get(int key) {
		if(cacheMap.find(key) == cacheMap.end())
			return -1;
		else
		{
			//把当前访问的节点移到链表头部,并且更新map中该节点的地址
			cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);	//list::splice实现list拼接的功能。将源list的内容部分或全部元素删除，拼插入到目的list。目的list的大小会增加，增加的大小为插入元素的大小。x的大小相应的会减少同样的大小。
			cacheMap[key] = cacheList.begin();
			return cacheMap[key]->value;
		}
	}

	///@brief	设置LRU中的值
	void set(int key, int value) {
		if(cacheMap.find(key) == cacheMap.end())
		{
			if(cacheList.size() == size)
			{//删除链表尾部节点（最少访问的节点）
				cacheMap.erase(cacheList.back().key);
				cacheList.pop_back();
			}
			//插入新节点到链表头部,并且更新map中增加该节点
			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();
		}
		else
		{//更新节点的值，把当前访问的节点移到链表头部,并且更新map中该节点的地址
			cacheMap[key]->value = value;
			cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
			cacheMap[key] = cacheList.begin();
		}
	}
};

class LRUCache{
public:
	LRUCache(int capacity) {
		size = capacity;
	}

	int get(int key) {
		if (cache_map.find(key) == cache_map.end())	return -1;
		cache_list.splice(cache_list.begin(), cache_list, cache_map[key]);
		cache_map[key] = cache_list.begin();
		return cache_map[key]->val;
	}

	void set(int key, int value) {
		if (cache_map.find(key) == cache_map.end())
		{			
			if (size == cache_list.size())
			{
				cache_map.erase(cache_map.find(cache_list.back().key));
				cache_list.pop_back();				
			}
			CacheNode new_node(key, value);
			cache_list.push_front(new_node);
			cache_map[key] = cache_list.begin();

		}
		else
		{
			cache_map[key]->val = value;
			cache_list.splice(cache_list.begin(), cache_list, cache_map[key]);
			cache_map[key] = cache_list.begin();
		}
	}

private:
	struct CacheNode
	{
		int key;
		int val;
		CacheNode (int k, int v)
		{
			key = k;
			val = v;
		}
	};

	int size;
	list<CacheNode> cache_list;
	unordered_map<int, list<CacheNode>::iterator> cache_map;
};

int main()
{
	return 0;
}