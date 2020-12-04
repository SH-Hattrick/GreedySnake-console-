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


//��ĳһ�ڶ���Ϊ��ͷ
void Snake::I_AM_HEAD()
{
	head = true;
}


//�ƶ��ߵ�λ��
void Snake::move_snake()
{
	_x += speed * x_dir;
	_y += speed * y_dir;
}


//�ı䷽��
void Snake::change_dir(int dir)
{
	//��(0,-1),��(0,1),��(-1,0),��(1,0)
	if (!head)
		return;
	switch (dir)
	{
	case SNAKE_LEFT: if (x_dir != 1) { x_dir = -1; y_dir = 0; } break;//��ֹ����ͷ��
	case SNAKE_RIGHT: if (x_dir != -1) { x_dir = 1; y_dir = 0; } break;
	case SNAKE_UP: if (y_dir != 1) { x_dir = 0; y_dir = -1; } break;
	case SNAKE_DOWN: if (y_dir != -1) { x_dir = 0; y_dir = 1; }break;
	default:
		break;
	}
}


//����
void Snake::draw_snake()
{
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	fillcircle(_x, _y, radius);
}


//��ȥ��
void Snake::undraw_snake()
{
	setlinecolor(BKCOLOR);
	setfillcolor(BKCOLOR);
	fillcircle(_x, _y, radius);
}


//�ж���ͷ�Ƿ�ײ����ǽ�ڣ�x,yΪ�߿��С
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

//�ҳ����Լ�
bool Snake::eat_myself(queue<Snake> s)//������
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

//�Ƿ�ɹ���ʳ�����ɹ���
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


//�����µ�һ�ڣ��ý�λ��Ӧ��ǰһ�ڵ�λ�����˶������й�
Snake Snake::next_snake()
{
	return Snake(_x - x_dir * DIAMETER, _y - y_dir * DIAMETER);
}


//���ӳ���
void add_length(queue<Snake>& snakes)
{
	snakes.push(snakes.back().next_snake());
}


//����ͷ�ı䷽��֮ǰ��ʹ�����ÿһ���߽�copyǰһ���߽ڵķ���
queue<Snake> copy_direction(queue<Snake> &snakes)
{
	queue<Snake> newsnake;
	Snake head = snakes.front();//��¼ͷ����Ϣ
	int xd = head.x_dir, yd = head.y_dir;//�õ���ͷ�ķ���
	snakes.pop();//ɾ��ͷ
	newsnake.push(head);//��ͷ�����¶���
	while (!snakes.empty())
	{
		Snake s = snakes.front();
		int tmp_x = s.x_dir, tmp_y = s.y_dir;
		s.x_dir =xd; s.y_dir = yd;//ʹ�ý�������һ��ͬ����
		xd = tmp_x; yd = tmp_y;
		snakes.pop();
		newsnake.push(s);
	}
	newsnake.front().I_AM_HEAD();
	return newsnake;
}


//�������߶��У�
queue<Snake> generate_snake(int x, int y)
{
	queue<Snake> snakes;
	//��ʼ���Ľ�
	Snake sHead(x, y);
	sHead.I_AM_HEAD();
	snakes.push(sHead);
	for (int i = 1; i <= 3; ++i)
	{
		Snake s(x - i * DIAMETER, y);
		snakes.push(s);
	}
	//ʹ��front�ɷ�����ͷ������һ���������Ԫ��
	snakes.front().I_AM_HEAD();
	return snakes;
}


//�ƶ�������
queue<Snake> move_queue(queue<Snake> &snakes)
{
	queue<Snake> newsnake;
	queue<Snake> temp = snakes;
	while (!temp.empty())
	{
		Snake s = temp.front();
		s.undraw_snake();//���ԭͼ��
		temp.pop();
	}
	while (!snakes.empty())
	{
		Snake s = snakes.front();
		s.move_snake();
		s.draw_snake();//������ͼ��
		newsnake.push(s);
		snakes.pop();
	}
	newsnake.front().I_AM_HEAD();
	return newsnake;
}

