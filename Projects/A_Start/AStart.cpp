#include "stdafx.h" 
#include "AStart.h" 


AStart::AStart(int *mapInfo, int width, int height, int start, int goal) 
{ 
	Width  = width; 
	Height = height; 
	this->_startPoint  = start; 
	this->_targetPoint    = goal; 

	//把二维数组保存到一维数组中去，便于信息的处理 
	this->_mapInfo = new int[Width * Height]; 
	for (int i = 0; i < Width * Height; i++) 
	{ 
		//map[i] = mapInfo[i / width][i % width]; 
		this->_mapInfo[i] = mapInfo[i]; 
	} 

	//记录每一个节点的位置信息 
	this->_pointInfo = new Point[Width * Height]; 
	for (int i = 0; i < (Width * Height); i++) 
	{ 
		this->_pointInfo[i].x = i % Width; 
		this->_pointInfo[i].y = i / Width; 
	} 

	//初始化起点 
	this->_pointInfo[this->_startPoint].g_value = 0; 
	this->_pointInfo[this->_startPoint].h_value = get_h_value(this->_startPoint); 
	this->_pointInfo[this->_startPoint].parent = NULL; 

	//把起点加入open_list中 
	open_list.push_back(this->_startPoint); 
} 

AStart::~AStart() 
{ 
	if (this->_mapInfo != NULL) 
	{ 
		delete[] this->_mapInfo; 
	} 
	if (this->_pointInfo != NULL) 
	{ 
		delete[] this->_pointInfo; 
	} 
} 

int AStart::get_g_value(int pos) 
{ 
	//只允许玩家往上下左右四个方向行走，所以这里的g值只需要在父节点的g值上加10 
	return (this->_pointInfo[pos].parent->g_value + 10); 
} 

int AStart::get_h_value(int pos) 
{ 
	//返回该点到终点的Manhattan距离，乘以10是为了方便计算机计算 
	return (10 * (abs(this->_targetPoint / Width - pos / Width) + abs(this->_targetPoint % Width - pos % Width))); 
} 

void AStart::getResultPath() 
{ 
	Point *temp = &this->_pointInfo[this->_targetPoint]; 
	while (temp != NULL) 
	{ 
		result.push_back(*temp); 
		temp = temp->parent; 
	} 
	return; 
} 

bool AStart::isReachable(int pos) 
{ 
	if ((pos / Width < Height) && (pos / Width >= 0) && 
		(pos % Width < Width)  && (pos % Width >= 0)) 
	{ 
		return true; 
	} 
	else 
	{ 
		return false; 
	} 
} 

//如果pos不可达或者它在close_list中则跳过它，否则，进行如下操作 
//如果pos不在open_list中则加入open_list，并把当前方格设置为它的父亲 
//如果pos在open_list中则检查g的大小，如果更小则把它的父亲设置为当前方格 
bool AStart::testRoad(int point, int cur) 
{ 
	if (isReachable(point)) 
	{ 
		if (point == this->_targetPoint) 
		{ 
			this->_pointInfo[point].parent = &this->_pointInfo[cur]; 
			return true; 
		} 
		if (this->_mapInfo[point] != 1) //1代表障碍物，0则可通行 
		{ 
			if (close_list.end() == find(close_list.begin(), close_list.end(), point)) 
			{ 
				std::list<int>::iterator iter = find(open_list.begin(), open_list.end(), point); 
				if (iter == open_list.end()) 
				{ 
					open_list.push_back(point); 
					this->_pointInfo[point].parent = &this->_pointInfo[cur]; 
					this->_pointInfo[point].h_value = get_h_value(point); 
					this->_pointInfo[point].g_value = get_g_value(point); 
				} 
				else 
				{ 
					if ((this->_pointInfo[cur].g_value + 10) < this->_pointInfo[point].g_value) 
					{ 
						this->_pointInfo[point].parent = &this->_pointInfo[cur]; 
						this->_pointInfo[point].g_value = get_g_value(point); 
					} 
				} 
			} 
		} 
	} 
	return false; 
} 

bool AStart::Find() 
{ 
	//遍历open_list，查找F值最小的节点作为当前要处理的节点 
	//如果open_list为空，则表明没有解决方案 
	if (open_list.empty()) 
	{ 
		return false; 
	} 

	int f_value = 0; 
	int min_f_value = -1; 
	std::list<int>::iterator iter, save; 
	for (iter = open_list.begin(); iter != open_list.end(); iter++) 
	{ 
		f_value = this->_pointInfo[*iter].g_value + this->_pointInfo[*iter].h_value; 
		//这里的min==f也会重新给它赋值，导致open_list中靠后的元素具有更高的优先级 
		//不过无关紧要 
		if ((min_f_value == -1) || (min_f_value >= f_value)) 
		{ 
			min_f_value = f_value; 
			save = iter; 
		} 
	} 

	//把这个F值最小的节点移到close_list中 
	int cur = *save; 
	close_list.push_back(cur); 
	open_list.erase(save); 


	//对当前方格的上下左右相邻方格进行测试 
	//如果终点进入了open_list则结束 
	int up    = cur - Width; 
	int down  = cur + Width; 
	int left  = cur - 1; 
	int right = cur + 1; 
	if (true == testRoad(up, cur)) 
	{ 
		return true; 
	} 
	if (true == testRoad(down, cur)) 
	{ 
		return true; 
	} 
	if (true == testRoad(left, cur)) 
	{ 
		return true; 
	} 
	if (true == testRoad(right, cur)) 
	{ 
		return true; 
	} 

	return Find(); 
} 