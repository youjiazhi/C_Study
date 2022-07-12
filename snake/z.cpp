#include <stdio.h>
#include <conio.h>
#include <easyx.h>
#include <stdlib.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*
    ��Ŀ���ݣ�̰����С��Ϸ
    ֪ʶ�㣺�ṹ��,ѭ��,����,easyx,����
*/

//������1������һ�����ڣ�ͼ�δ���
#define SNAKE_NUM 500//�ߵ�������
#define WEIGHT 500
#define HEIGHT 500

//�ߵýṹ
struct Snake
{
	int size; //�ߵĽ���
	int dir; //�ߵķ���
	int speed; //�ƶ��ٶ�
	POINT coor[SNAKE_NUM];//����
}snake;
//ʳ��ṹ
struct Food
{
	int x;			//ʳ��x����
	int y;			//ʳ��Y����
	int r;			//ʳ��뾶  ����ʳ��Ĵ�С
	bool flag;		//ʳ���Ƿ񱻳Ա��
	DWORD color;	//ʳ����ɫ
}food;
enum DIR//��ʾ�ߵķ���
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


static int speed = 100;

//���ݵĳ�ʼ��
void GameInit()
{
	//���ű�������
	mciSendString("open ./music/bgm.mp3 alias BGM", 0,0,0);
	mciSendString("play BGM repeat", 0,0,0);
	//init ��ʼ��graphͼ�δ���
    initgraph(WEIGHT, HEIGHT);
	//��ʼ����
	snake.size = 15;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i=0; i<snake.size; i++)
	{ 
		snake.coor[i].x = 160-10*i;
		snake.coor[i].y = 10;
	}
	//�������������
	srand(GetTickCount());//GetTickCount()��ȡϵͳ�����������������ĺ��룬ʱ�䲻�ϱ仯�����Կ���������
	//��ʼ��ʳ��
	food.x = rand() % WEIGHT;
	food.y = rand() % HEIGHT;
	food.color = RGB(rand()%255, rand()%255, rand()%255);
	food.r = rand() % 10 + 5;
	food.flag = true;


	
}



void GameDraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(25,115,119));
    cleardevice();
	//������
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
	//����ʳ��

	if(food.flag)
	{
		srand(GetTickCount());
		setfillcolor(food.color);
		solidcircle(food.x,food.y,food.r);
	}

	EndBatchDraw();
}
//�ƶ���
void snakeMove()
{
	//�ƶ������귢���ı�
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
//ͨ������ı��ߵ��ƶ�����
void keyControl()
{
	//�ж���û�а���
	if (_kbhit())
	{
		// �������Ҽ��ļ�ֵ��  72 80 75 77
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
		case ' '://��Ϸ��ͣ
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
	//ˢ��ʵ��
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