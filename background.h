#ifndef BACKGROUND_H
#define BACKGROUND_H
//各种全局变量和全局常量


//定义地图的宽和高
#define WIDTH 26
#define HIGHT 20
//定义地图中节点类型
#define ISEMPTY 0
#define ISBODY 1
#define ISFOOD 2
#define ISWALL 3
//定义四个方向控制键
#define KEY_UP '2'
#define KEY_DOWN '8'
#define KEY_LEFT '4'
#define KEY_RIGHT '6'
#define KEY_SUSPEND '5'
//定义游戏速度
const int SPEED = 24;


//定义一个布尔类型
enum {FALSE, TRUE};

//定义转向的方向
enum D {UP, RIGHT, DOWN, LEFT};
//定义一个方向，用于移动转向时比较
enum D tempD = RIGHT;

typedef struct snake   //存储身体信息
{
	int x;  //身体节点 x 坐标
	int y;  //身体节点 y 坐标
	struct snake *last;  //上一身体节点地址
	}snake;

//地图数组
char map[HIGHT][WIDTH] = {};

//定义蛇和食物的指针
snake *tail, *body, *head, *food;

//定义一个尾巴临时指针
snake *t_tail;

int length = 3;  //蛇的长度，初始化为3


#endif