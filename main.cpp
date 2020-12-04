#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<iomanip>
#include<conio.h>
#include<ctime>
#include<queue>
#include<Windows.h>
#include<time.h>
#include<string>
#include<cstring>
#include<fstream>

#include"Snake.h"
using namespace std;
//GetStdHandle(STD_OUTPUT_HANDLE)


void starting_graph();
void game_on();
void ending_info();
void generate_food();
bool eater(Snake s);
void drawfood();
void fileEdit(int n);
void rankingViewing();


int main()
{

	initgraph(640, 480);
	setbkcolor(BKCOLOR);
	cleardevice();
	starting_graph();//图形界面初始化
	char c = _getch();
 	while (c != 27)
	{
		game_on();//游戏主函数
		ending_info();//结束画面
		FlushMouseMsgBuffer();
		c = _getch();
		if (c == 'y')
			rankingViewing();
	}
	closegraph();
	return 0;
}


struct food;
food myfood;
int final_length = 0;
IMAGE Start;


void starting_graph()
{
	loadimage(&Start, _T("Begin.jpg"), 640, 480);
	putimage(0, 0, &Start);
	settextcolor(DARKGRAY);
	outtextxy(240, 390, _T("Tap anywhere to continue..."));
}


void game_on()
{
	setbkcolor(BKCOLOR);
	cleardevice();
	queue<Snake> MySnake = generate_snake(100, 100);
	generate_food();
	drawfood();
	while (true)
	{
		MySnake = copy_direction(MySnake);
		if (MySnake.front().if_dead(640, 480) || MySnake.front().eat_myself(MySnake))
			break;
		if (_kbhit())
		{
			char Key = _getch();
			switch (Key)
			{
			case 'a': MySnake.front().change_dir(SNAKE_LEFT); break;
			case 'd': MySnake.front().change_dir(SNAKE_RIGHT); break;
			case 'w': MySnake.front().change_dir(SNAKE_UP); break;
			case 's': MySnake.front().change_dir(SNAKE_DOWN); break;
			case 'x': while (1) { if (_kbhit()) break; } break;
			}
		}
		MySnake = move_queue(MySnake);
		if (myfood.super)
		{
			if (eater(MySnake.front()))
			{
				for (int i = 1; i <= 3; ++i) add_length(MySnake);
			}
		}
		else if (eater(MySnake.front()))
			add_length(MySnake);
		final_length = MySnake.size();
		Sleep(52);
	}
	fileEdit(final_length);
}


void ending_info()
{
	Sleep(1000);
	cleardevice();
	settextcolor(BLACK);
	/*char s[100] = "Your length: ";
	str += final_length - '0';
	outtextxy(300, 100, (TCHAR)str);*/
	TCHAR s[100];
	swprintf_s(s, _T("Your final length: %d"), final_length);
	outtextxy(250, 200, s);
	//HWND hwnd = GetConsoleWindow();
	// 4MessageBoxW(hwnd, _T("Nicely Done"), _T("Game over"), 0);
	outtextxy(250, 250, _T("Press ESC to exit, and press y to see the ranking"));
	Sleep(2000);
}


void generate_food()
{
	if (myfood.x == NONE_EXIST)
	{
		srand((unsigned int)time(NULL));
		myfood.x = rand() % 620 + 10;
		myfood.y = rand() % 460 + 10;
		if (rand() % 6 == 0)
			myfood.super = true;
	}
	else return;
}


void drawfood()
{
	if (myfood.super == true)
	{
		setlinecolor(RGB(21, 234, 111));
		setfillcolor(RGB(21, 234, 111));
		fillcircle(myfood.x, myfood.y, myfood.r + 2);
	}
	else if(myfood.super == false)
	{
		setlinecolor(RED);
		setfillcolor(RED);
		fillcircle(myfood.x, myfood.y, myfood.r);
	}
}


bool eater(Snake s)
{
	if (s.I_EAT_IT(myfood.x,myfood.y))
	{
		myfood.x = NONE_EXIST;
		myfood.super = false;
		generate_food();
		drawfood();
		return true;
	}
	drawfood();
	return false;
}


void fileEdit(int n)
{
	fstream fopen("../ranks", ios::in | ios::binary);
	if (!fopen)
	{
		cerr << "File opening ERROR!\n";
		exit(-1);
	}
	int rank[10];
	memset(rank, 0, sizeof(rank));
	int i, index = 0;
	while (fopen.read((char*)&i, sizeof(int)))
	{
		rank[index] = i;
		++index;
	}
	for (int i = 0; i < 9; ++i)
		for (int j = i + 1; j < 10; ++j)
			if (rank[i] < rank[j])
				swap(rank[i], rank[j]);
	if (rank[9] < n)
		rank[9] = n;
	for (int i = 0; i < 9; ++i)
		for (int j = i + 1; j < 10; ++j)
			if (rank[i] < rank[j])
				swap(rank[i], rank[j]);
	fopen.close();

	fstream writef("../ranks", ios::out | ios::binary);
	writef.write((char*)&rank[0], sizeof(int));
	writef.write((char*)&rank[1], sizeof(int));
	writef.write((char*)&rank[2], sizeof(int));
	writef.write((char*)&rank[3], sizeof(int));
	writef.write((char*)&rank[4], sizeof(int));
	writef.write((char*)&rank[5], sizeof(int));
	writef.write((char*)&rank[6], sizeof(int));
	writef.write((char*)&rank[7], sizeof(int));
	writef.write((char*)&rank[8], sizeof(int));
	writef.write((char*)&rank[9], sizeof(int));
	writef.close();
}

void rankingViewing()
{
	setbkcolor(BKCOLOR);
	cleardevice();
	fstream readf("../ranks", ios::in | ios::binary);
	int rank[10];
	int index = 0;
	int i;
	while (readf.read((char*)&i, sizeof(int)))
	{
		rank[index] = i;
		index++;
	}
	TCHAR s[100];
	swprintf_s(s, _T("Your rankings: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d"), rank[0],
		rank[1], rank[2], rank[3], rank[4], rank[5], rank[6], rank[7], rank[8], rank[9]);
	outtextxy(150, 200, s);
	readf.close();
	Sleep(2000);
}



