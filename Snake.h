#pragma once
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<iomanip>
#include<conio.h>
#include<ctime>
#include<queue>
using namespace std;


#define SNAKE_LEFT 1
#define SNAKE_RIGHT 2
#define SNAKE_UP 3
#define SNAKE_DOWN 4
#define RADIUS 4
#define BKCOLOR WHITE
#define NONE_EXIST -1
#define FOODSIZE 3
#define DIAMETER 2*RADIUS


struct food
{
	int x = NONE_EXIST;
	int y = NONE_EXIST;
	int r = FOODSIZE;
	bool super = false;
};


class Snake
{
private:
	int _x = 0;
	int _y = 0;
	int speed = DIAMETER;//速度
	int x_dir = 1;
	int y_dir = 0;
	//只有四个方向(1,0)(0,1)(-1,0)(0,-1)
	int radius = RADIUS;//身体大小
	bool head = false;
	//其中某一节定义为蛇头，head置为true
	//此处定义的Snake为蛇的一节，蛇由一个个球组成
public:
	friend queue<Snake> copy_direction(queue<Snake> &snakes);
	friend food;
	Snake();
	Snake(int x, int y); 
	Snake(const Snake* sn);
	void I_AM_HEAD();
	void move_snake();//单节移动
	void change_dir(int dir);//只操作蛇头
	void draw_snake();//绘制蛇，在move_queue中调用
	void undraw_snake();//擦去蛇，在move_queue中调用
	bool I_EAT_IT(int &fx,int &fy);
	bool if_dead(int x, int y);
	bool eat_myself(queue<Snake> s);
	Snake next_snake();
};

//创建蛇头，四节，队列front元素为蛇头
//顺序：先copy_direction,再change_dir,然后move_queue,最后判断是否需要add_length
void add_length(queue<Snake>& snakes);
queue<Snake> generate_snake(int x, int y);
queue<Snake> copy_direction(queue<Snake> &snakes);
queue<Snake> move_queue(queue<Snake> &snakes);






