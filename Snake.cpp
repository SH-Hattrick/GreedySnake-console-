#include "Snake.h"
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<iomanip>
#include<conio.h>
#include<ctime>
#include<queue>
using namespace std;


Snake::Snake() {}
Snake::Snake(int x, int y) { _x = x; _y = y; }
Snake::Snake(const Snake* sn)
{
	_x = sn->_x;
	_y = sn->_y;
}


//将某一节定义为蛇头
void Snake::I_AM_HEAD()
{
	head = true;
}


//移动蛇的位置
void Snake::move_snake()
{
	_x += speed * x_dir;
	_y += speed * y_dir;
}


//改变方向
void Snake::change_dir(int dir)
{
	//上(0,-1),下(0,1),左(-1,0),右(1,0)
	if (!head)
		return;
	switch (dir)
	{
	case SNAKE_LEFT: if (x_dir != 1) { x_dir = -1; y_dir = 0; } break;//防止“调头”
	case SNAKE_RIGHT: if (x_dir != -1) { x_dir = 1; y_dir = 0; } break;
	case SNAKE_UP: if (y_dir != 1) { x_dir = 0; y_dir = -1; } break;
	case SNAKE_DOWN: if (y_dir != -1) { x_dir = 0; y_dir = 1; }break;
	default:
		break;
	}
}


//画蛇
void Snake::draw_snake()
{
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	fillcircle(_x, _y, radius);
}


//擦去蛇
void Snake::undraw_snake()
{
	setlinecolor(BKCOLOR);
	setfillcolor(BKCOLOR);
	fillcircle(_x, _y, radius);
}


//判断蛇头是否撞击到墙壁，x,y为边框大小
bool Snake::if_dead(int x, int y)
{
	if (!head)
		return false;
	else if (_x + radius <= 0 || _x + radius >= x)
		return true;
	else if (_y + radius <= 0 || _y + radius >= y)
		return true;
	else return false;
}

//我吃我自己
bool Snake::eat_myself(queue<Snake> s)//非引用
{
	Snake head = s.front();
	s.pop();
	while (!s.empty())
	{
		Snake tmp = s.front();
		if (head._x<tmp._x + tmp.radius && head._x>tmp._x - tmp.radius &&
			head._y<tmp._y + tmp.radius && head._y>tmp._y - tmp.radius)
			return true;
		s.pop();
	}
	return false;
}

//是否成功吞食，若成功则
bool Snake::I_EAT_IT(int &fx,int &fy)
{
	if (fx-FOODSIZE<_x + radius && fx+ FOODSIZE>_x - radius
		&& fy- FOODSIZE < _y + radius && fy+ FOODSIZE > _y - radius)
	{
		setlinecolor(BKCOLOR);
		setfillcolor(BKCOLOR);
		fillcircle(fx, fy, FOODSIZE + 2);
		fx = NONE_EXIST;
		return true;
	}
	else return false;
}


//生成新的一节，该节位置应与前一节的位置与运动方向有关
Snake Snake::next_snake()
{
	return Snake(_x - x_dir * DIAMETER, _y - y_dir * DIAMETER);
}


//增加长度
void add_length(queue<Snake>& snakes)
{
	snakes.push(snakes.back().next_snake());
}


//在蛇头改变方向之前，使其身后每一个蛇节copy前一个蛇节的方向
queue<Snake> copy_direction(queue<Snake> &snakes)
{
	queue<Snake> newsnake;
	Snake head = snakes.front();//记录头的信息
	int xd = head.x_dir, yd = head.y_dir;//得到蛇头的方向
	snakes.pop();//删除头
	newsnake.push(head);//将头插入新队列
	while (!snakes.empty())
	{
		Snake s = snakes.front();
		int tmp_x = s.x_dir, tmp_y = s.y_dir;
		s.x_dir =xd; s.y_dir = yd;//使该节蛇与上一节同方向
		xd = tmp_x; yd = tmp_y;
		snakes.pop();
		newsnake.push(s);
	}
	newsnake.front().I_AM_HEAD();
	return newsnake;
}


//创建蛇蛇队列，
queue<Snake> generate_snake(int x, int y)
{
	queue<Snake> snakes;
	//初始化四节
	Snake sHead(x, y);
	sHead.I_AM_HEAD();
	snakes.push(sHead);
	for (int i = 1; i <= 3; ++i)
	{
		Snake s(x - i * DIAMETER, y);
		snakes.push(s);
	}
	//使用front可返回蛇头，即第一个被置入的元素
	snakes.front().I_AM_HEAD();
	return snakes;
}


//移动整条蛇
queue<Snake> move_queue(queue<Snake> &snakes)
{
	queue<Snake> newsnake;
	queue<Snake> temp = snakes;
	while (!temp.empty())
	{
		Snake s = temp.front();
		s.undraw_snake();//清除原图像
		temp.pop();
	}
	while (!snakes.empty())
	{
		Snake s = snakes.front();
		s.move_snake();
		s.draw_snake();//绘制新图像
		newsnake.push(s);
		snakes.pop();
	}
	newsnake.front().I_AM_HEAD();
	return newsnake;
}

