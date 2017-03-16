#ifndef SNAKE_H
#define SNAKE_H
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


#endif