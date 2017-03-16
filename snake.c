//贪吃蛇（数组法）
#include "background.h"
#include <stdio.h>
#include <assert.h>
#include <conio.h>  //get kbhit()


//复制一条蛇
snake *cloneSnake(snake *t_tail)
{
	if (t_tail == NULL)
	{
		return NULL;
		}
	else
	{
		snake *temp, *clonetail;
		temp = NULL;
		
		while (t_tail != NULL)
		{
			if (temp == NULL)
			{
			    temp = (snake *)malloc(sizeof (snake));
			    clonetail = temp;
				}
			else
			{
				temp->last = (snake *)malloc(sizeof (snake));
				temp = temp->last;
				}
				
			temp->x = t_tail->x;
			temp->y = t_tail->y;
			
			t_tail = t_tail->last;
			}  //while  end
			
		return clonetail;
		}  //else  end
	}  //function cloneSnake()  end



//初始化墙
void initWall()
{
	for (int y=0; y<HIGHT; y++)
	{
	    for (int x=0; x<WIDTH; x++)
	    {
	        if (x == 0 || x == (WIDTH - 1)
	             || y == 0 || y == (HIGHT - 1))
	            {
	            	map[y][x] = ISWALL;
	                }
	        }  //inside for  end
	    }  //outside for  end
	}

//把蛇的信息写到地图中
void writeSnake()
{
	body = tail;
	while (body != NULL)
	{
		map[body->y][body->x] = ISBODY;
		body = body->last;
		}  //while  end
	}

//放一个食物
void initFood()
{
	int tx, ty;
	food = (snake *)malloc(sizeof (snake));
	do
	{
		tx = random() % (WIDTH - 2) + 1;
		ty = random() % (HIGHT - 2) + 1;
		}while (map[ty][tx] != ISEMPTY
		             || tx == 0 || ty == 0
		             || tx == (WIDTH - 1)
		             || ty == (HIGHT - 1));
	food->x = tx;
	food->y = ty;
	food->last = NULL;
	map[ty][tx] = ISFOOD;
	}

void initSnake()  //初始化蛇
{
	int x, y;
	x = 2;
	y = 1;
	tail = (snake *)malloc(sizeof (snake));
	body = (snake *)malloc(sizeof (snake));
	head = (snake *)malloc(sizeof (snake));
	tail->x = x - 1;
	tail->y = y;
	tail->last = body;
	body->x = x;
	body->y = y;
	body->last = head;
	head->x = x + 1;
	head->y = y;
	head->last = NULL;
	writeSnake();
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

//移动蛇     （此时不能让蛇向后走）
void moveSnake(enum D direction)
{
	int tx, ty;
	
	tempD = directionAnalyse(direction);
	//printf("\ntempD = %d\n", tempD);
	
	//尾推法移动蛇
	body = tail;
	while (body->last != NULL)
	{
		body = body->last;
		}  //while  end
    //重复利用空间，别浪费了！
	head->last = tail;
	tail = tail->last;
	head = head->last;
	head->last = NULL;
	
	/*下面只需要根据方向
	设置蛇头的位置就行了*/
	 tx = body->x;
	 ty = body->y;
	switch (tempD)
	{
		case UP:
		    ty--;
		    break;
		case DOWN:
		    ty++;
		    break;
		case LEFT:
		    tx--;
		    break;
		case RIGHT:
		    tx++;
		    break;
		default:
		    printf("error! in moveSnake()");
		    assert(0);
		    break;
		}  //switch  end
	head->x = tx;
	head->y = ty;
	
    writeSnake();
	}

//清除地图上蛇的身体
void cleanSnake()
{
	body = tail;
	while (body != NULL)
	{
		map[body->y][body->x] = ISEMPTY;
		body = body->last;
		}  //while  end
	}

//把map数组的数据显示出来
void printMap()
{
	for (int y=0; y<HIGHT; y++)
	{
	    for (int x=0; x<WIDTH; x++)
	    {
	    	switch (map[y][x])
	    	{
	    		case ISWALL:
	    		    printf("##");
	    		    break;
	    		case ISEMPTY:
	    		    printf("  ");
	    		    break;
	    		case ISBODY:
	    		    if (y == head->y 
	    		         && x == head->x)
	    		    {
	    		    	printf("@@");
	    		    	}
	    		    else if (y == tail->y
	    		          && x == tail->x)
	    		    {
	    		    	printf("oo");
	    		    	}
	    		    else
	    		    {
	    		    	printf("OO");
	    		    	}
	    		    break;
	    		case ISFOOD:
	    		    printf("$$");
	    		    break;
	    		}
	    	}  //inside for  end
	    printf("\n");
	    }  //outside for  end
	}

//判断有没有吃到食物，吃到了就增加长度
//吃到食物返回 TRUE，否则返回 FALSE
int addSnake(enum D direction)
{
	enum D t_dire = direction; //directionAnalyse(direction);
	int tx, ty;
	tx = head->x;
	ty = head->y;
	switch (t_dire)
	{
		case UP:
		    ty--;
		    break;
		case DOWN:
		    ty++;
		    break;
		case LEFT:
		    tx--;
		    break;
		case RIGHT:
		    tx++;
		    break;
		default:
		    printf("error! in addSnake()");
		    assert(0);
		    break;
		}  //switch end
		
		if (food->x == tx
		     && food->y == ty)
		{
			head->last = food;
			head = head->last;
			return TRUE;
			//printf("\nadd\n");
			}
		return FALSE;
	}

//清除多余的输入
void cleanInput()
{
	while (kbhit())
	{
		getch();
		}
	}

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
			/*default:
			    printf("error! in getDirection()");
			    assert(0);
			    break;
			    */
			}  //switch  end
		}  //while  end
	return tempD;
	}

//检测有没有撞到墙
int knockWall()
{
	int tx = head->x, ty = head->y;
	if (tx == 0 || tx == (WIDTH - 1)
	     || ty == 0 || ty == (HIGHT - 1))
	{
		return TRUE;
		}
	else
	{
		return FALSE;
		}
	}

//检测有没有撞到自己的身体
int biteSelf()
{
	int tx = head->x, ty = head->y;
	body = tail;
	while (body->last != NULL)
	{
		if (body->x == tx && body->y == ty)
		{
			return TRUE;
			}
		body = body->last;
		}  //while  end
	return FALSE;
	}

//释放蛇的内存
void freeSnake()
{
	body = tail;
	while (body->last != NULL)
	{
		tail = tail->last;
		free(body);
		body = tail;
		}  //while  end
	free(tail);
	tail = NULL;
	body = NULL;
	head = NULL;
	}

//开始游戏
void start()
{
	int size = (WIDTH - 2) * (HIGHT - 2);
	//enum D t_D;
	initSnake();
	initFood();
	while (1)
	{
		clrscr();
		initWall();
		cleanSnake();
		tempD = directionAnalyse(getDirection());
		if (addSnake(tempD) != FALSE)
		{
			writeSnake();
			length++;
			
			if (length >= size)
		    {
		    printMap();
			break;
			    }
			    
		    initFood();
			}
		else
		{
			
			//在这里控制蛇的走向
			moveSnake(tempD);
			
			}
		printMap();

        if (knockWall() || biteSelf())
        {
        	printf("\nYou lose!!");
        	getch();
        	clrscr();
        	cleanSnake();
        	freeSnake();
        	map[food->y][food->x] = ISEMPTY;
        	free(food);
        	initSnake();
        	initFood();
        	tempD = RIGHT;
        	length = 3;
        	}  //if  end
		usleep(10000000 / SPEED);
		
		/********
		
		//调试命令start
		if ((tempPath = 
		    findMinPath(head->x, head->y,
		    food->x, food->y, tempD) )
		    != NULL)
		{
			printf("findMinPath successful ");
			printf("\n");
			while (tempPath != NULL)
			{
				printf("%d,%d  %d\n", tempPath->x, tempPath->y, tempPath->direction);
				map[tempPath->y][tempPath->x] = 5;
				tempPath = tempPath->next;
				}  //while  end
			printf("head: %d, %d\n"
			       "food: %d, %d\n",
			       head->x, head->y,
			       food->x, food->y);
			printMap();
			}
		getch();
		//调试命令end
		********/
		
		}  //while  end
	//clrscr();
	printf("WoW!!\nYou win!!");
	}

int main()
{
	start();
	
	return 0;
	}