///@file Rectangle Area
/*
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Assume that the total area is never beyond the maximum possible value of int.
*/
///@author	zhaowei
///@date	2015.07.28
///#version	1.0

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	计算两个矩形的总面积
	///@param	A,B,C,D,E,F,G,H	四对坐标，分别表示两个矩形的左下角和右上角
	///@return	返回矩形的总面积，重叠部分只计算一次
	/* @note	枚举：两个矩形相交、包含与相离，分三种情况讨论。时间复杂度为O(1)，空间复杂度为O(1)。*/
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		//	包含
		if (A >= E && B >= F && C <= G && D <= H)	return (G-E)*(H-F);		
		if (A <= E && B <= F && C >= G && D >= H)	return (C-A)*(D-B);

		//	相离
		if (F >= D || E >= C || H <= B || G <= A)	return (C-A)*(D-B) + (G-E)*(H-F);
		
		//	相交
		//	两条平行边在另一个矩形内
		if (A >= E && C <= G)
		{
			if (D > H && B >= F && B <= H)	return	(G-E)*(H-F) + (D-H)*(C-A);
			if (D > H && B < F)				return	(G-E)*(H-F) + ((D-H)+(F-B))*(C-A);
			if (D <= H && D >= F && B < F)	return	(G-E)*(H-F) + (F-B)*(C-A);
		}
		if (E >= A && G <= C)
		{
			if (H > D && F >= B && F <= D)	return	(C-A)*(D-B) + (H-D)*(G-E);
			if (H > D && F < B)				return	(C-A)*(D-B) + ((H-D)+(B-F))*(G-E);
			if (H <= D && H >= B && F < B)	return	(C-A)*(D-B) + (B-F)*(G-E);
		}
		if (D <= H && B >= F)
		{
			if (A < E && C >= E && C <= G)	return	(G-E)*(H-F) + (E-A)*(D-B);
			if (A < E && C > G)				return	(G-E)*(H-F) + ((E-A)+(C-G))*(D-B);
			if (A >= E && A <= G && C > G)	return	(G-E)*(H-F) + (C-G)*(D-B);
		}
		if (H <= D && F >= B)
		{
			if (E < A && G >= A && G <= C)	return	(C-A)*(D-B) + (A-E)*(H-F);
			if (E < A && G > C)				return  (C-A)*(D-B) + ((A-E)+(G-C))*(H-F);
			if (E <= C && E >= A && G > C)	return  (C-A)*(D-B) + (G-C)*(H-F);
		}
		//	两条呈直角的边在一个矩形内
		if (A <= G && A >= E && D <= H && D >= F)	return (G-E)*(H-F) + (G-A)*(F-B) + (C-G)*(D-B);
		if (A <= G && A >= E && B <= H && B >= F)	return (G-E)*(H-F) + (G-A)*(D-H) + (C-G)*(D-B);
		if (C <= G && C >= E && B <= H && B >= F)	return (G-E)*(H-F) + (C-E)*(D-H) + (D-B)*(E-A); 
		if (C <= G && C >= E && D <= H && D >= F)	return (G-E)*(H-F) + (C-E)*(F-B) + (D-B)*(E-A);
	}
};

int main()
{
	Solution slt;
	int rslt = slt.computeArea(-3,0,3,4,0,-1,9,2);
	return 0;
}