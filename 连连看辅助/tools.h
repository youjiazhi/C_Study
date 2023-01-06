#pragma once
#include <Windows.h>
#include <graphics.h>

IMAGE getScreen();

//�Ƚ�����ͼƬ�Ƿ���ͬ���ǳ����ƣ�
bool imgSame(IMAGE* img1, IMAGE* img2);

bool shuiPingConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool chuiZhiConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool oneTurnConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool twoTurnConnect(int* data, int rows, int cols, int row1, int col1, int row2, int col2);
//���ؾ�����һ�ε��ü����ʱ�䣨��λ��ms)����һ�ε���ʱ����0
int getDelay(); 

void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// ������ y <0 �Լ�y>0���κ����
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

// �ж����������Ƿ��ཻ
bool rectIntersect(int a1X, int a1Y, int a2X, int a2Y,
    int b1X, int b1Y, int b2X, int b2Y);

void  preLoadSound(const char* name);
void  playSound(const char* name);

void drawBloodBar(int x, int y, int width, int height, 
    int lineWidth, int boardColor, 
    int emptyColor, int fillColor, float percent);

