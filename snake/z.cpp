#include <stdio.h>
#include <conio.h>
#include <easyx.h>
#include <stdlib.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*
    项目内容：贪吃蛇小游戏
    知识点：结构体,循环,函数,easyx,数组
*/

//做界面1，创建一个窗口，图形窗口
#define SNAKE_NUM 500//蛇的最大节数
#define WEIGHT 500
#define HEIGHT 500

//蛇得结构
struct Snake
{
	int size; //蛇的节数
	int dir; //蛇的方向
	int speed; //移动速度
	POINT coor[SNAKE_NUM];//坐标
}snake;
//食物结构
struct Food
{
	int x;			//食物x坐标
	int y;			//食物Y坐标
	int r;			//食物半径  就是食物的大小
	bool flag;		//食物是否被吃标记
	DWORD color;	//食物颜色
}food;
enum DIR//表示蛇的方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


static int speed = 100;

//数据的初始化
void GameInit()
{
	//播放背景音乐
	mciSendString("open ./music/bgm.mp3 alias BGM", 0,0,0);
	mciSendString("play BGM repeat", 0,0,0);
	//init 初始化graph图形窗口
    initgraph(WEIGHT, HEIGHT);
	//初始化蛇
	snake.size = 15;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i=0; i<snake.size; i++)
	{ 
		snake.coor[i].x = 160-10*i;
		snake.coor[i].y = 10;
	}
	//设置随机数种子
	srand(GetTickCount());//GetTickCount()获取系统开机到现在所经过的毫秒，时间不断变化，所以可用作种子
	//初始化食物
	food.x = rand() % WEIGHT;
	food.y = rand() % HEIGHT;
	food.color = RGB(rand()%255, rand()%255, rand()%255);
	food.r = rand() % 10 + 5;
	food.flag = true;


	
}



void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(25,115,119));
    cleardevice();
	//绘制蛇
	static int radius = 8;
	if (_kbhit())
	{
		switch (_getch())
		{
		case '+':
			radius++;
			break;
			
		case '-':
			radius--;
			break;
		case '/':
			speed+=10;
			break;
		case '*':
			speed-=10;
			break;
			
		}
	}
	setfillcolor(RED);
	solidcircle(snake.coor[0].x, snake.coor[0].y, radius);
	setfillcolor(WHITE);
	for (int i=1; i<snake.size; i++)
	{
		
		setfillcolor(food.color);
		solidcircle(snake.coor[i].x, snake.coor[i].y, radius);
	}
	//绘制食物

	if(food.flag)
	{
		srand(GetTickCount());
		setfillcolor(food.color);
		solidcircle(food.x,food.y,food.r);
	}

	EndBatchDraw();
}
//移动蛇
void snakeMove()
{
	//移动是坐标发生改变
	for (int i=snake.size-1; i>0; i--)
	{
		snake.coor[i] = snake.coor[i-1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y + 10 <= 0)
		{
			snake.coor[0].y = HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y+=snake.speed;
		if (snake.coor[0].y - 10 >= HEIGHT)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-=snake.speed;
		if (snake.coor[0].x + 10 <= 0)
		{
			snake.coor[0].x = WEIGHT;
		}
		break;
	case RIGHT:
		snake.coor[0].x+=snake.speed;
		if (snake.coor[0].x - 10 >= WEIGHT)
		{
			snake.coor[0].x = 0;
		}
		break;
	}
	
}
//通过安检改变蛇的移动方向
void keyControl()
{
	//判断有没有安检
	if (_kbhit())
	{
		// 上下左右键的键值是  72 80 75 77
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if(snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if(snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if(snake.dir != RIGHT)
			{
				snake.dir = RIGHT;
			}
			snake.dir = LEFT;
			break;
		case 'd':
		case 'D':
		case 77:
			if(snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			
			break;
		case ' '://游戏暂停
			while(1)
			{
				if(_getch() == ' ')
					return;
			}
		}
	}
	
}

void EatFood()
{
	if(snake.coor[0].x >= food.x-food.r && snake.coor[0].x <= food.x+food.r &&
	   snake.coor[0].y >= food.y-food.r && snake.coor[0].y <= food.y+food.r &&
	   food.flag)
	{
		food.flag=false;
		snake.size++;
	}
	//刷新实物
	if(!food.flag)
	{
		food.x = rand() % WEIGHT;
		food.y = rand() % HEIGHT;
		food.color = RGB(rand()%256, rand()%256, rand()%256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}

}

void stop()
{}

int main()
{
	GameInit();
	GameDraw();
	
	while(1)
	{
		GameDraw();
		keyControl();
		snakeMove();
		EatFood();
		Sleep(speed);
	}

    
    return 0;
}