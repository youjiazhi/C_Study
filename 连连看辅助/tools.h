#pragma once
#include <Windows.h>
#include <graphics.h>

IMAGE getScreen();

//比较两个图片是否相同（非常相似）
bool imgSame(IMAGE* img1, IMAGE* img2);

bool shuiPingConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool chuiZhiConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool oneTurnConnect(int* data, int cols, int row1, int col1, int row2, int col2);
bool twoTurnConnect(int* data, int rows, int cols, int row1, int col1, int row2, int col2);
//返回距离上一次调用间隔的时间（单位：ms)，第一次调用时返回0
int getDelay(); 

void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// 适用于 y <0 以及y>0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

// 判断两个矩形是否相交
bool rectIntersect(int a1X, int a1Y, int a2X, int a2Y,
    int b1X, int b1Y, int b2X, int b2Y);

void  preLoadSound(const char* name);
void  playSound(const char* name);

void drawBloodBar(int x, int y, int width, int height, 
    int lineWidth, int boardColor, 
    int emptyColor, int fillColor, float percent);

