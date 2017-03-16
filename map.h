#ifndef MAP_H
#define MAP_H

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
	    		    printf("\033[7m  \033[0m");
	    		    break;
	    		case ISEMPTY:
	    		    printf("  ");
	    		    break;
	    		case ISBODY:
	    		    if (y == head->y 
	    		         && x == head->x)
	    		    {
	    		    	printf("\033[31;7m  \033[0m");
	    		    	}
	    		    else if (y == tail->y
	    		          && x == tail->x)
	    		    {
	    		    	printf("\033[34;7m  \033[0m");
	    		    	}
	    		    else
	    		    {
	    		    	printf("\033[32;7m  \033[0m");
	    		    	}
	    		    break;
	    		case ISFOOD:
	    		    printf("\033[35;7m  \033[0m");
	    		    break;
	    		}
	    	}  //inside for  end
	    printf("\n");
	    }  //outside for  end
	}


#endif