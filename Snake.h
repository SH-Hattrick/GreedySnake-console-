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
	int speed = DIAMETER;//�ٶ�
	int x_dir = 1;
	int y_dir = 0;
	//ֻ���ĸ�����(1,0)(0,1)(-1,0)(0,-1)
	int radius = RADIUS;//�����С
	bool head = false;
	//����ĳһ�ڶ���Ϊ��ͷ��head��Ϊtrue
	//�˴������SnakeΪ�ߵ�һ�ڣ�����һ���������
public:
	friend queue<Snake> copy_direction(queue<Snake> &snakes);
	friend food;
	Snake();
	Snake(int x, int y); 
	Snake(const Snake* sn);
	void I_AM_HEAD();
	void move_snake();//�����ƶ�
	void change_dir(int dir);//ֻ������ͷ
	void draw_snake();//�����ߣ���move_queue�е���
	void undraw_snake();//��ȥ�ߣ���move_queue�е���
	bool I_EAT_IT(int &fx,int &fy);
	bool if_dead(int x, int y);
	bool eat_myself(queue<Snake> s);
	Snake next_snake();
};

//������ͷ���Ľڣ�����frontԪ��Ϊ��ͷ
//˳����copy_direction,��change_dir,Ȼ��move_queue,����ж��Ƿ���Ҫadd_length
void add_length(queue<Snake>& snakes);
queue<Snake> generate_snake(int x, int y);
queue<Snake> copy_direction(queue<Snake> &snakes);
queue<Snake> move_queue(queue<Snake> &snakes);






