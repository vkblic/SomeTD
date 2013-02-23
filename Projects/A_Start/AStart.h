////////////////////////////////////////////////////////////////////////////////////// 
// 
//  FileName    :   A.h 
//  Version     :   1.0 
//  Creater     :   Ranger Cai 
//  Date        :   2012-2-27 09:44:49 
//  Comment     :   A* algorithm header file 
// 
////////////////////////////////////////////////////////////////////////////////////// 
#ifndef _A_FINDPATH_H 
#define _A_FINDPATH_H 

#include <list> 
#include <algorithm> 

//记录地图上每个节点的位置信息以及估值信息的结构体堆栈 
typedef struct _Point 
{ 
	int x; 
	int y; 
	int h_value;  //h值为节点到终点的Manhattan距离 
	int g_value;  //g值为起点到该点的移动代价 
	struct _Point *parent;  //指向父节点 
}Point; 

class AStart 
{ 
public: 
	//初始化传入地图二维数组、地图宽、长，起始及终点在数组中的序号 
	AStart(int *mapInfo, int width, int height, int start, int end); 
	~AStart(); 

	//A*查找，查找成功返回true，否则返回false 
	bool Find(); 
	//如果Find()函数成功，则可以调用此函数把结果路径存入到result中 
	void getResultPath(); 

	//计算pos节点的g值 
	int get_g_value(int pos); 
	//计算pos节点的h值 
	int get_h_value(int pos); 
	//判断pos节点是否在地图内 
	bool isReachable(int pos); 
	//测试节点是否更好并判断是否已经找到路径 
	bool testRoad(int pos, int cur); 

	int  *_mapInfo;  //地图信息 
	Point *_pointInfo; //父子节点关系链 
	std::list<Point> result;  //查找成功后的结果路径保存在此 

private: 
	int Width; 
	int Height; 
	int _startPoint; 
	int _targetPoint; 

	std::list<int> open_list;   //open表中的节点为待检查的节点 
	std::list<int> close_list;  //close表中的节点为暂时不关注的节点 
}; 

#endif //_A_FINDPATH_H 