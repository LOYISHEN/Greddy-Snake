#ifndef START_H
#define START_H

extern void printMap();
//暂停游戏
void suspendGame()
{
	while (getch() != KEY_SUSPEND)
	{
		NULL;
	}
	return;
}

//开始游戏
void start()
{
	int t_speed = 10000000 / SPEED;
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
        	cleanInput();
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
		usleep(t_speed);
		
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

#endif