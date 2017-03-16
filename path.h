//路径处理模块


#ifndef PATH_H
#define PATH_H


/*
函数Map.findMaxPath(): 计算两个位置间的最长路径

算法建立在DFS与贪心算法的基础上。每次遍历邻接点时，离目标位置最远（使用曼哈顿距离估计）的位置将会被优先遍历到。另外，为了使路径尽可能直，如果两个位置到目标位置的距离相等，在当前移动方向上的位置将被优先遍历到。这个问题是一个NP完全问题，此算法得出的结果路径只是一个近似最长路径。
*/


////////////////////////////////////////////
/*
贪吃蛇AI算法介绍


////////////////////////
函数Snake.decideNext():计算蛇S1的下一个移动方向D

1 . 计算从蛇S1的头部到达食物的最短路径P1。

2 . 派一条与蛇S1完全一样的虚拟蛇S2沿路径P1吃掉食物。

3 . 计算从蛇S2的头部到其尾部的最长路径P2。如果路径P2存在，将移动方向D设置为路径P1的第一个方向，否则进行步骤4。

4 . 计算从蛇S1的头部到达其尾部的最长路径P3。如果P3存在，将移动方向D设置为路径P3的第一个方向，否则进行步骤5。

5 . 将移动方向D设置为离食物最远的方向。




///////////////////////
函数Map.findMinPath(): 计算两个位置间的最短路径

算法建立在BFS的基础上。为了使路径尽可能直，每次遍历邻接点时，在当前移动方向上的位置会被优先遍历。




  //////////////////////
函数Map.findMaxPath():计算两个位置间的最长路径

算法建立在DFS与贪心算法的基础上。每次遍历邻接点时，离目标位置最远（使用曼哈顿距离估计）的位置将会被优先遍历到。另外，为了使路径尽可能直，如果两个位置到目标位置的距离相等，在当前移动方向上的位置将被优先遍历到。这个问题是一个NP完全问题，此算法得出的结果路径只是一个近似最长路径。

*/
////////////////////////////////////////////


////////////////////////////////////////////


//book 数组用于记录某个坐标的遍历情况
char book[HIGHT][WIDTH];

//判断两个点的方向
enum D gainDirection(int startX,
                     int startY, int endX, int endY)
{
	if (startX == endX)
	{
		if (startY < endY)
		{
			return DOWN;
			}
		else if (startY > endY)
		{
			return UP;
			}
		}
	else if (startY == endY)
	{
		if (startX > endX)
		{
			return LEFT;
			}
		else if (startX < endX)
		{
			return RIGHT;
			}
		}
	
	
	}

//返回 X 和 Y，让路径尽可能直
void returnNextDirection(int *x, int *y,
                                             int amount,
                                        enum D direction)
{
	amount += (int )direction;
	amount %= 4;
	switch (amount)
	{
		//UP
		case 0:
		    (*y)--;
		    break;
		//RIGHT
		case 1:
		    (*x)++;
		    break;
		//DOWN
		case 2:
		    (*y)++;
		    break;
		//LEFT
		case 3:
		    (*x)--;
		    break;
		    
		default:
		    printf("error! in returnNextDirection()\n");
		    assert(0);
		    break;
		}  //switch  end
	}

//把 book 数组的数据全部清除
void cleanBook()
{
	for (int y=0; y<HIGHT; y++)
	{
		for (int x=0; x<WIDTH; x++)
		{
			book[y][x] = ISEMPTY;
			
			}  //inside for  end
		
		}  //outside for  end
	}

//定义路径节点
typedef struct path
{
	char x;  //x 坐标
	char y;  //y 坐标
	char s;  //步数
	struct path *f;  //父路径节点
	struct path *next;  //下一路径节点
	enum D direction;  //下一节点方向
	}sPath;

sPath *tempPath;

const sPathSize = sizeof (sPath);

/*
函数Map.findMaxPath(): 计算两个位置间的最长路径

算法建立在DFS与贪心算法的基础上。每次遍历邻接点时，离目标位置最远（使用曼哈顿距离估计）的位置将会被优先遍历到。另外，为了使路径尽可能直，如果两个位置到目标位置的距离相等，在当前移动方向上的位置将被优先遍历到。这个问题是一个NP完全问题，此算法得出的结果路径只是一个近似最长路径。
*/


////////////////////////////////////////////
/*
贪吃蛇AI算法介绍


////////////////////////
函数Snake.decideNext():计算蛇S1的下一个移动方向D

1 . 计算从蛇S1的头部到达食物的最短路径P1。

2 . 派一条与蛇S1完全一样的虚拟蛇S2沿路径P1吃掉食物。

3 . 计算从蛇S2的头部到其尾部的最长路径P2。如果路径P2存在，将移动方向D设置为路径P1的第一个方向，否则进行步骤4。

4 . 计算从蛇S1的头部到达其尾部的最长路径P3。如果P3存在，将移动方向D设置为路径P3的第一个方向，否则进行步骤5。

5 . 将移动方向D设置为离食物最远的方向。




///////////////////////
函数Map.findMinPath(): 计算两个位置间的最短路径

算法建立在BFS的基础上。为了使路径尽可能直，每次遍历邻接点时，在当前移动方向上的位置会被优先遍历。


*/

//BFS找最短路径，不存在时返回 NULL
sPath *findMinPath(int startX, int startY,
                                    int goalX, int goalY,
                                    enum D direction)  
{
	int tx, ty, flag;
	sPath *t_head, *t_tail, *temp;
	t_tail = (sPath *)malloc(sPathSize);
	t_head = (sPath *)malloc(sPathSize);
	
	t_tail->x = startX;
	t_tail->y = startY;
	t_tail->s = 0;
	t_tail->f = NULL;
	t_tail->next = t_head;
	cleanBook();
	
	//BFS
	while (t_tail != t_head)
	{
		//让路径尽可能直（少拐弯）
		if (t_tail->f != NULL)
		{
			direction = gainDirection(t_tail->x,
		           	t_tail->y, temp->x, temp->y);
			}
		//枚举四个方向
		for (int t=0; t<4; t++)
		{
			tx = t_tail->x;
			ty = t_tail->y;
			returnNextDirection(&tx, &ty,
		                                       	t, direction);
			
			//判断边界
			if (tx < 1 || tx > (WIDTH - 2)
			     || ty < 1 || ty > (HIGHT - 2))
			{
				continue;
				}
			//把节点写入列表
			if ((map[ty][tx] == ISEMPTY 
			|| map[ty][tx] == ISFOOD)
			     && book[ty][tx] == ISEMPTY)
			{
				book[ty][tx] = ISBODY;
				
				t_head->x = tx;
				t_head->y = ty;
				t_head->s = t_tail->s + 1;
				t_head->f = t_tail;
				
				//调试命令start
				//printf("tx: %d ty: %d\n", tx, ty);
				//调试命令end
				
				temp = t_head;
				t_head = (sPath *)malloc(
				sPathSize);
				temp->next = t_head;
				}  //if  end
			
			if (tx == goalX && ty == goalY)
			{
				flag = ISBODY;
				break;
				}
			}  //for  end
		
		if (flag == ISBODY)
		{
			break;
			}
			
		t_tail = t_tail->next;
		}  //while  end
	free(t_head);
	t_head = temp;
	t_head->next = NULL;
	while (temp->f->f != NULL)
	{
		temp = temp->f;
		}
	free(temp->f);
	temp->f = NULL;
	//BFS 结束
	
	/*****7
	//调试语句start
	printf("\n");
	while (temp != NULL)
	{
		printf("%p: %d %d %p\n",
		temp, temp->x, temp->y, temp->f);
		temp = temp->next;
		}
	//调试语句end
	*******/
	
	//当路径存在时，用 temp 来找到路径
	//即把无关的 path 节点删掉，链接路径
	if (flag == ISBODY)
	{
	    temp = t_head->f;
    	//当 head 还在所有路径中时
    	//结束条件是开始节点的 f 为 NULL
    	while (temp != NULL)
    	{
    		//删除掉无用的节点
    		//结束条件是该节点的下一节点是\
    		//有用路径的节点
	    	temp = temp->next;
    		while (temp != t_head)
    		{
    			t_tail = temp->next;
			    free(temp);
			    temp = t_tail;
    			}  //inside while  end
    		//写入方向
    		t_tail = t_head->f;
    		t_head->direction = gainDirection(
    		t_tail->x, t_tail->y, t_head->x,
    		t_head->y);
    		
    		//仿双向链表
    		t_tail->next = t_head;
    		
    		//下一个有用节点
    		t_head = t_head->f;
    		temp = t_head->f;
    		}  //outside while  end
    	t_tail->direction = gainDirection(
    	startX, startY, t_tail->x, t_tail->y);
    	
    	//返回路径
    	return t_tail;
    	}  //if  end
    
    //找不到路，返回空指针
    return NULL;
	}  //function findMinPath()  end

//定义用于深度搜索的路径节点结构
typedef struct D_path
{
	struct D_path *last;
	int x;
	int y;
	int s;
	enum D direction;
	struct D_path *next;
	}sD_path;
	
const int sD_pathLength = sizeof (sD_path);

//用于记录多个深搜路径
typedef struct D_path_path
{
	struct D_path_path *last;
	sD_path *head;
	struct D_path_path *next;
	}sD_path_path;
	
const int sD_path_pathLength = sizeof (sD_path_path);

//清除深搜路径
void cleanD_path(sD_path *t_head)
{
	sD_path *temp;
	
	while (t_head != NULL)
	{
		temp = t_head->next;
		free(t_head);
		t_head = temp;
		}  //while  end
	}  //procedure cleanD_path()  end

//清除记录的所有 深搜 路径
void cleanD_path_path(sD_path_path *t_head)
{
	sD_path_path *temp;
	
	while (t_head != NULL)
	{
		temp = t_head->next;
		cleanD_path(t_head->head);
		free(t_head);
		t_head = temp;
		}  //while  end
	}  //procedure cleanD_path_path()  end

//复制一条深搜路径
sD_path *cloneD_path(sD_path *t_head)
{
	sD_path *clonehead, *temp;
	temp = NULL;
	while (t_head != NULL)
	{
		if (temp == NULL)
		{
			temp = (sD_path *)malloc(sD_pathLength);
			clonehead = temp;
			}
		else
		{
			temp->next = (sD_path *)malloc(sD_pathLength);
			temp = temp->next;
			}
		temp->x = t_head->x;
		temp->y = t_head->y;
		
		t_head = t_head->next;
		}  //while  end
	}  //function cloneD_path()  end

//用于记录最长路径的步数
int step = 0;

/*
深搜算法：
		先去找最长路径，如果当前最长路径与现最长路径的步数相同，就分析拐点少的路径，并以现最长路径替换当前最长路径！

*/

/*

这个可能用不到

//深搜并返回最长的路径的记录
sD_path_path *DFS(int currentX, int currentY, int goalX, int goalY, sD_path currentD_path)
{
	
	if (currentX == goalX && currentY == goalY)
	{
//		if (currentD_path->s-> step)
		}
	}
*/

//深度找最长路径
sPath findMaxPath(int startX, int startY,
                                 int goalX, int goalY,
                                 enum D direction)                            
{
	// DFS 开始
	sPath tempPath = {
										startX,
										startY,
										0,
										NULL,
										NULL,
										RIGHT
											};
	//定义一个数组，以便遍历每一个方向
	//右 下 左 上   eachDirection[num][y,x]
	char eachDirection[4][2] = {
													{0, 1},
													{1, 0},
													{0, -1},
													{-1, 0},
													};
													
	
	}

sPath *DFS(int startX, int startY, int endX, int endY)
{
	int tx, ty;
	tx = startX;
	ty = startY;
	
	//判断边界
	if (tx < 1 || tx > (WIDTH - 2) || ty < 1 || ty > (HIGHT - 2))
	{
		return NULL;
	}
	
	//尝试每一个方向
	for (register int i=0; i<4; i++)
	{
		
	}	//for  end
	
	
}

//释放路径
void cleanPath(sPath *t_tail)
{
	sPath *temp;
	while (t_tail != NULL)
	{
		temp = t_tail->next;
		free(t_tail);
		t_tail = temp;
		}  //while  end
	}


//处理方向，返回正确方向
enum D directionAnalyse(enum D direction)
{
		switch (direction)
	{
		case LEFT:
		case RIGHT:
		    if (tempD != LEFT 
		         && tempD != RIGHT)
		    {
		    	return direction;
		    	}
		    else
		    {
		    	return tempD;
		    	}
		    break;
		case UP:
		case DOWN:
		    if (tempD != UP
		         && tempD != DOWN)
		    {
		    	return direction;
		    	}
		    else
		    {
		    	return tempD;
		    	}
		    	break;
		default:
		    printf("error! in directionAnalyse()");
		    assert(0);
		    break;
		}  //switch  end
	}

//清除多余的输入
void cleanInput()
{
	while (kbhit())
	{
		getch();
		}
	}

extern void suspendGame();
//获取输入
enum D getDirection()
{
	while (kbhit())
	{
		switch (getch())
		{
			case KEY_UP:
			    cleanInput();
			    return UP;
			    break;
			case KEY_DOWN:
			    cleanInput();
			    return DOWN;
			    break;
			case KEY_LEFT:
			    cleanInput();
			    return LEFT;
			    break;
			case KEY_RIGHT:
			    cleanInput();
			    return RIGHT;
			    break;
			case KEY_SUSPEND:
			    cleanInput();
			    suspendGame();
			default:
			    break;
			}  //switch  end
		}  //while  end
	return tempD;
	}



#endif