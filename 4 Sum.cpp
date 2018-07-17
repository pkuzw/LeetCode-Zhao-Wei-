/* @file

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? 

Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)

The solution set must not contain duplicate quadruplets.

For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

A solution set is:
(-1,  0, 0, 1)
(-2, -1, 1, 2)
(-2,  0, 0, 2)
*/
///@author	zhaowei
///@date	2015.06.06
///@version 1.0
///@note	先通过快速排序将原有数组排序，然后将其转换成不包括重复元素的数组，再然后就是通过二分查找找到4个数和为指定值的组合。
//			时间复杂度为	O(nlgn+n^3lgn)，空间复杂度是O(3n).OJ报TLE

///@date	2015.06.08
///@version 1.1
///@note	

///@date	2015.07.29
///@version	1.2

///@date    2015.09.07
///@version 2.0

///@date	2015.09.17
///@version	2.1

///@date	2016.04.05
///@version	2.2

///@date    July 17, 2018
///@version 2.3S

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <set>

using namespace std;

class Solution_v1
{
public:
	///@brief	成功AC，时间复杂度为O(n^3)
	vector<vector<int> > fourSum(vector<int> &nums, int target) {
		set<vector<int> > res;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < int(nums.size() - 3); ++i) {
			for (int j = i + 1; j < int(nums.size() - 2); ++j) {
				int left = j + 1, right = nums.size() - 1;
				while (left < right) {
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target) {
						vector<int> out;
						out.push_back(nums[i]);
						out.push_back(nums[j]);
						out.push_back(nums[left]);
						out.push_back(nums[right]);
						res.insert(out);
						++left; --right;
					} else if (sum < target) ++left;
					else --right;
				}
			}
		}
		return vector<vector<int> > (res.begin(), res.end());
	}


	///@brief	求4个数之和为指定值的所有组合
	///@param	nums	待处理的数组
	///@return	返回所有可能的组合，在每一个4元组答案中按照非降序排列元素
	///@author	zhaowei
	///@date	2015.06.06
	// @note	先通过快速排序将原有数组排序，然后将其转换成不包括重复元素的数组，再然后就是通过二分查找找到4个数和为指定值的组合。
	//			时间复杂度为	O(nlgn+n^3lgn)，空间复杂度是O(3n)
	//
	vector<vector<int>> fourSum_tle(vector<int>& nums, int target) {

		QuickSort(nums, 0, nums.size()-1);	// 快排

		vector<int> nr_nums;	// 将nums中重复出现的元素抽成只出现一次
		vector<int> rt_nums;	// 记录重复出现元素的个数数组
		int cnt = 1;			// 记录重复出现的元素个数

		vector<vector<int>> ivvec;	//三元组为元素组成的向量

		if (nums.empty())	//如果nums为空向量，直接返回空向量
		{
			return ivvec;
		}

		for (int i = 0; i != nums.size(); i++)	// 将原有数组转换成没有重复元素的数组
		{	
			// 因为i+1有可能越界，所以要单独拿出来判断。循环里的变量边界需要设成num.size()-1，这样不会漏掉最后一个数
			if (i < nums.size()-1 && nums[i] == nums[i+1])	
			{
				cnt++;
				continue;
			}
			nr_nums.push_back(nums[i]);
			rt_nums.push_back(cnt);
			cnt = 1;
		}
		
		int l = 0, r = nr_nums.size()-1;	

		int a = 0, b = 0, c = 0, d = 0;
		for (int i = 0; i <= r; i++)
		{				
			a = nr_nums[i];

			for (int j = r; j >= i; j--)	
			{								
				b = nr_nums[j];

				if (a == b && rt_nums[i] < 2)	// 如果没有两个重复元素，则跳过
				{
					continue;
				}

				for (int k = r; k >= j; k--)
				{
					vector<int> four_elem;
					c = nr_nums[k];
					if ((b == c && rt_nums[j] < 2) 
						|| (b == c && a == b && rt_nums[j] < 3))
					{
						continue;
					}
					d = target-a-b-c;
					int e = BinarySearch(nr_nums, k, r, d); // d的二分查找范围只能是在c的下标k和r之间
					
					if (e == -1
						|| (e == k && rt_nums[k] < 2)
						|| (e == k && c == b && rt_nums[k] < 3) 
						|| (e == k && c == b && b == a && rt_nums[k] < 4))
					{
						continue;
					}
					
					four_elem.push_back(a);
					four_elem.push_back(b);
					four_elem.push_back(c);
					four_elem.push_back(d);

					ivvec.push_back(four_elem);
				}			
			}				
		}
		return ivvec;
	}

	///@brief 交换两个整型变量
	///@param a, b 待交换的两个元素
	///@author zhaowei
	///@date 2014.07.15
	void swap(int& a, int& b)
	{
		int t = a;
		a = b;
		b = t;
		return;
	}

	///@brief	将数组分割，使其左半部分的元素都比返回值小，右半部分的元素都比返回值大。
	///@param	arr	数组指针
	///@param	p	起始下标
	///@param	r	终止下标
	///@return	返回分割后数组的中轴值
	///@author	zhaowei
	///@date	2014.07.15	
	int Partition(vector<int>& arr, const int p, const int r)
	{		
		int x = arr[r];
		int i = p-1;
		for(int j = p; j < r; j++)
		{
			if(arr[j] <= x)
			{
				i++;
				swap(arr[j], arr[i]);
			}		
		}
		swap(arr[i+1], arr[r]);
		return i+1;
	}

	///@brief	用递归实现快速排序
	///@param	arr	数组指针。这里应该是引用，否则无法进行递归
	///@param	p	数组起始下标
	///@param	r	数组终止下标
	///@author	zhaowei
	///@date	2014.07.15
	void QuickSort(vector<int>& arr, const int p, const int r)
	{
		if(p < r)
		{
			int q = Partition(arr, p, r);
			QuickSort(arr, p, q-1);
			QuickSort(arr, q+1, r);
		}
		return;
	}

	///@brief	二分查找函数
	///@param	&array_int	 排好序的数组，这里应该是引用，否则无法进行递归
	///@param	p			 数组的起始下标
	///@param	r	 数组的终止下标
	///@param	v	 待查找的值
	///@return	如果在数组中找到v值，则返回该值所在下标；否则返回-1
	int BinarySearch(vector<int>& array_int, int p, int r, int v)
	{
		if(p > r)  // || v < array_int[p] || v > array_int[r])
			return -1;
		int q = (p + r) / 2;
		if(v == array_int[q])
			return q;
		else if(v < array_int[q])
			return BinarySearch(array_int, p, q-1, v);
		else 
			return BinarySearch(array_int, q+1, r, v);
	}

	///@brief	利用<multimap>作为缓冲，时间复杂度O(n^2),空间复杂度O(n^2)
	///@author	zhaowei
	///@date	2015.06.08
	///@note	也报TLE
	vector<vector<int> > fourSum_tle2(vector<int>& nums, int target)
	{
		vector<vector<int> > rslt;
		if (nums.size() < 4) return rslt;

		sort(nums.begin(), nums.end());	// 排序

		unordered_multimap<int, pair<int, int> > cache;	// 转换成两个数之和组成的缓冲区
		for (int i = 0; i != nums.size()-1; i++)
		{
			for (int j = i+1; j != nums.size(); j++)
			{
				cache.insert(make_pair(nums[i] + nums[j], make_pair(i, j)));
			}
		}

		for (auto i = cache.begin(); i != cache.end(); i++)
		{
			auto x = target - i->first;
			auto range = cache.equal_range(x);	//	找出等于x的范围
			for (auto j = range.first; j != range.second; j++)
			{
				auto a = i->second.first;
				auto b = i->second.second;
				auto c = j->second.first;
				auto d = j->second.second;

				if (a != c && b != d && a != d && b != c)
				{
					vector<int> ivec;
					ivec.push_back(nums[a]);
					ivec.push_back(nums[b]);
					ivec.push_back(nums[c]);
					ivec.push_back(nums[d]);
					sort(ivec.begin(), ivec.end());
					rslt.push_back(ivec);
				}
			}
		}
		sort(rslt.begin(), rslt.end());
		rslt.erase(unique(rslt.begin(), rslt.end()), rslt.end());
		return rslt;
	}

	///@brief	利用<map>来作为缓冲区。时间复杂度在最坏情况下是O(n^4)，最好情况下是O(n^2)，空间复杂度是O(n^2)
	///@author	zhaowei
	///@date	2015.06.08
	///@note	也是TLE
	vector<vector<int> > fourSum_tle3(vector<int> &num, int target) {
		vector<vector<int>> result;
		if (num.size() < 4) return result;
		sort(num.begin(), num.end());
		unordered_map<int, vector<pair<int, int> > > cache;
		for (size_t a = 0; a < num.size(); ++a) {
			for (size_t b = a + 1; b < num.size(); ++b) {
				cache[num[a] + num[b]].push_back(pair<int, int>(a, b));
			}
		}
		for (int c = 0; c < num.size(); ++c) {
			for (size_t d = c + 1; d < num.size(); ++d) {
				const int key = target - num[c] - num[d];
				if (cache.find(key) == cache.end()) continue;
				const auto& vec = cache[key];
				for (size_t k = 0; k < vec.size(); ++k) {
					if (c <= vec[k].second)
						continue; // 有重叠
					vector<int> ivec;
					ivec.push_back(num[vec[k].first]);
					ivec.push_back(num[vec[k].second]);
					ivec.push_back(num[c]);
					ivec.push_back(num[d]);
					result.push_back(ivec);
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}

	///@brief	求4个数之和为指定值的所有组合
	///@author  zhaowei
	///@date	2015.06.08  
	/* @note	O（n^2）的算法，先对数组排序。先枚举出所有二个数的和存放在哈希map中，其中map的key对应的是二个数的和，因为多对元素求和可能是相同的值，
				故哈希map的value是一个链表（下面的代码中用数组代替），链表每个节点存的是这两个数在数组的下标；这个预处理的时间复杂度是O（n^2）。
				接着枚举第一个和第二个元素，假设分别为v1,v2, 然后在哈希map中查找和为target-v1-v2的所有二元对（在对应的链表中），查找的时间为O（1），
				为了保证不重复计算，我们只保留两个数下标都大于V2的二元对，即使是这样也有可能重复：比如排好序后数组为-9 -4 -2 0 2 4 4，target = 0，
				当第一个和第二个元素分别是-4，-2时，我们要得到和为0-（-2）-（-4） = 6的二元对，这样的二元对有两个,都是(2,4)，且他们在数组中的下标都
				大于-4和-2，如果都加入结果，则(-4,-2,2,4)会出现两次，因此在加入二元对时，要判断是否和已经加入的二元对重复（由于过早二元对之前数组已
				经排过序，所以两个元素都相同的二元对可以保证在链表中是相邻的，链表不会出现(2,4)->(1,5)->(2,4)的情况，因此只要判断新加入的二元对和上
				一个加入的二元对是否重复即可），因为同一个链表中的二元对两个元素的和都是相同的，因此只要二元对的一个元素不同，则这个二元对就不同。
				我们可以认为哈希map中key对应的链表长度为常数，那么算法总的复杂度为O（n^2）
				同样报TLE
	*/
	vector<vector<int> > fourSum_tle4(vector<int> &num, int target) {
		int n = num.size();
		vector<vector<int> > res;
		unordered_map<int, vector<pair<int, int> > >pairs;
		
		sort(num.begin(), num.end());

		for(int i = 0; i < n; i++)
			for(int j = i+1 ; j < n; j++)
				pairs[num[i]+num[j]].push_back(make_pair(i,j));

		for(int i = 0; i < n - 3; i++)
		{
			if(i != 0 && num[i] == num[i-1])continue;//防止第一个元素重复
			for(int j = i+1; j < n - 2; j++)
			{
				if(j != i+1 && num[j] == num[j-1])continue;//防止第二个元素重复
				if(pairs.find(target - num[i] - num[j]) != pairs.end())
				{
					vector<pair<int, int>> &sum2 = pairs[target - num[i] - num[j]];
					bool isFirstPush = true;
					for(int k = 0; k < sum2.size(); k++)
					{
						if(sum2[k].first <= j)continue;//保证所求的四元组的数组下标是递增的
						if(isFirstPush || (res.back())[2] != num[sum2[k].first])
						{
							vector<int> ivec;
							ivec.push_back(num[i]);
							ivec.push_back(num[j]);
							ivec.push_back(num[sum2[k].first]);
							ivec.push_back(num[sum2[k].second]);
							res.push_back(ivec);
							isFirstPush = false;
						}
					}
				}
			}
		}

		return res;
	}
}; 

// O(n^3)
class Solution_v2 {
public:
	///@brief	计算给定数组中所有和为指定值的四元组
	///@param	nums	数组
	///@param	target	指定值
	///@return	返回所有可能的四元组
	///@note	利用set<vector<int>>来保存结果，这样能够避免重复元素的出现。在外层用两层循环来进行枚举，剩下的两个元素用左右两个指针从两侧向
	//			中间收，直到找到指定值。时间复杂度为O(n^3)，空间复杂度为O(k)。k为结果数组的大小。
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
		if (nums.size() < 4)	return vector<vector<int>>(0);
		set<vector<int>> rslt;
		sort(nums.begin(), nums.end());
		for (int i = 0; i != nums.size() - 3; i++) {
			for (int j = i + 1; j != nums.size() - 2; j++) {
				int left = j + 1, right = nums.size() - 1, sum = target - (nums[i] + nums[j]);
				while (left < right) {
					if (nums[left] + nums[right] == sum) {
						vector<int> ivec;
						ivec.push_back(nums[i]);
						ivec.push_back(nums[j]);
						ivec.push_back(nums[left]);
						ivec.push_back(nums[right]);
						rslt.insert(ivec);
						left++;
						right--;
					}
					else if (nums[left] + nums[right] < sum) left++;
					else	right--;
				}
			}
		}
		vector<vector<int>> ret(rslt.begin(), rslt.end());
		return ret;
	}
};

class Solution {
public:
    ///@brief   给定一个整型数组，计算其中的所有四元组，其和为给定值。
    ///@param   nums    整型数组
    ///@param   target  指定的和
    ///@return  返回所有满足和为指定值的四元组。要求四元组之间没有重复。
    ///@note    1. 思路类似3 sum。两层循环遍历前两个元素，剩下的设置左右指针，从两头向中间移动，如果求和满足条件，那么就将结果保存。
    //          2. 不过略有不同的地方是使用set<vector<int>>作为中间结果的数据结构，这样就排除了重复的四元组。
    //          这个思路也可是在3 sum上试一试。
    //          3. set是一个C++的容器模板，其中的元素不能有重复，通过key值按照一定顺序排列，实现方式为BST(二叉搜索树)。
    //          4. 算法的时间复杂度为O(n^3)，空间复杂度为O(m)，其中m为符合条件的四元组个数。
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ret_em;
        int len = nums.size();
        if (len < 4)    return  ret_em;
        sort(nums.begin(), nums.end());
        set<vector<int>> rslt;
        for (int i = 0; i < len - 3; i++) {
            for (int j = i + 1; j < len - 2; j++) {
                int l = j + 1, r = len - 1;
                while (l < r) {
                    if (nums[i] + nums[j] + nums[l] + nums[r] == target) {
                        vector<int> vec_t;
                        vec_t.push_back(nums[i]);
                        vec_t.push_back(nums[j]);
                        vec_t.push_back(nums[l]);
                        vec_t.push_back(nums[r]);
                        rslt.insert(vec_t);
                        l++, r--;
                    }
                    else if (nums[i] + nums[j] + nums[l] + nums[r] < target)
                        l++;
                    else
                        r--;
                }
            }
        }
        vector<vector<int>> ret(rslt.begin(), rslt.end());
        return ret;
    }
};

int main()
{
	vector<int> ivec;	
	int n[201] = {91277418,66271374,38763793,4092006,11415077,60468277,1122637,72398035,-62267800,22082642,60359529,-16540633,92671879,-64462734,-55855043,-40899846,88007957,-57387813,-49552230,-96789394,18318594,-3246760,-44346548,-21370279,42493875,25185969,83216261,-70078020,-53687927,-76072023,-65863359,-61708176,-29175835,85675811,-80575807,-92211746,44755622,-23368379,23619674,-749263,-40707953,-68966953,72694581,-52328726,-78618474,40958224,-2921736,-55902268,-74278762,63342010,29076029,58781716,56045007,-67966567,-79405127,-45778231,-47167435,1586413,-58822903,-51277270,87348634,-86955956,-47418266,74884315,-36952674,-29067969,-98812826,-44893101,-22516153,-34522513,34091871,-79583480,47562301,6154068,87601405,-48859327,-2183204,17736781,31189878,-23814871,-35880166,39204002,93248899,-42067196,-49473145,-75235452,-61923200,64824322,-88505198,20903451,-80926102,56089387,-58094433,37743524,-71480010,-14975982,19473982,47085913,-90793462,-33520678,70775566,-76347995,-16091435,94700640,17183454,85735982,90399615,-86251609,-68167910,-95327478,90586275,-99524469,16999817,27815883,-88279865,53092631,75125438,44270568,-23129316,-846252,-59608044,90938699,80923976,3534451,6218186,41256179,-9165388,-11897463,92423776,-38991231,-6082654,92275443,74040861,77457712,-80549965,-42515693,69918944,-95198414,15677446,-52451179,-50111167,-23732840,39520751,-90474508,-27860023,65164540,26582346,-20183515,99018741,-2826130,-28461563,-24759460,-83828963,-1739800,71207113,26434787,52931083,-33111208,38314304,-29429107,-5567826,-5149750,9582750,85289753,75490866,-93202942,-85974081,7365682,-42953023,21825824,68329208,-87994788,3460985,18744871,-49724457,-12982362,-47800372,39958829,-95981751,-71017359,-18397211,27941418,-34699076,74174334,96928957,44328607,49293516,-39034828,5945763,-47046163,10986423,63478877,30677010,-21202664,-86235407,3164123,8956697,-9003909,-18929014,-73824245, -236727523};
	string s = "91277418,66271374,38763793,4092006,11415077,60468277,1122637,72398035,-62267800,22082642,60359529,-16540633,92671879,-64462734,-55855043,-40899846,88007957,-57387813,-49552230,-96789394,18318594,-3246760,-44346548,-21370279,42493875,25185969,83216261,-70078020,-53687927,-76072023,-65863359,-61708176,-29175835,85675811,-80575807,-92211746,44755622,-23368379,23619674,-749263,-40707953,-68966953,72694581,-52328726,-78618474,40958224,-2921736,-55902268,-74278762,63342010,29076029,58781716,56045007,-67966567,-79405127,-45778231,-47167435,1586413,-58822903,-51277270,87348634,-86955956,-47418266,74884315,-36952674,-29067969,-98812826,-44893101,-22516153,-34522513,34091871,-79583480,47562301,6154068,87601405,-48859327,-2183204,17736781,31189878,-23814871,-35880166,39204002,93248899,-42067196,-49473145,-75235452,-61923200,64824322,-88505198,20903451,-80926102,56089387,-58094433,37743524,-71480010,-14975982,19473982,47085913,-90793462,-33520678,70775566,-76347995,-16091435,94700640,17183454,85735982,90399615,-86251609,-68167910,-95327478,90586275,-99524469,16999817,27815883,-88279865,53092631,75125438,44270568,-23129316,-846252,-59608044,90938699,80923976,3534451,6218186,41256179,-9165388,-11897463,92423776,-38991231,-6082654,92275443,74040861,77457712,-80549965,-42515693,69918944,-95198414,15677446,-52451179,-50111167,-23732840,39520751,-90474508,-27860023,65164540,26582346,-20183515,99018741,-2826130,-28461563,-24759460,-83828963,-1739800,71207113,26434787,52931083,-33111208,38314304,-29429107,-5567826,-5149750,9582750,85289753,75490866,-93202942,-85974081,7365682,-42953023,21825824,68329208,-87994788,3460985,18744871,-49724457,-12982362,-47800372,39958829,-95981751,-71017359,-18397211,27941418,-34699076,74174334,96928957,44328607,49293516,-39034828,5945763,-47046163,10986423,63478877,30677010,-21202664,-86235407,3164123,8956697,-9003909,-18929014,-73824245, -236727523";
 	
 	int cnt = 0;
 	for (int i = 0; i < s.length(); i++)
 	{
 		if (s[i] == ',')
 		{
 			cnt ++;
 		}
 	}
 	for (int i = 0; i < 201; i++)
 	{
 		ivec.push_back(n[i]);
 	}

	int n2[] = {1,0,-1,0,-2,2};
 	
	vector<int> ivec2;
	for (int i = 0; i != 6; i++)	ivec2.push_back(n2[i]);
	vector<int> ivec3;

	Solution slt;
	vector<vector<int>> ivvec;
	ivvec = slt.fourSum(ivec2, 0);
	
	Solution_v2 s2;
	vector<vector<int>> ivvec2 = s2.fourSum(ivec2, 0);
	return 0;
}
