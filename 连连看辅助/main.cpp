#include <stdio.h>
#include <windows.h>
#include "tools.h"
//图片左上角坐标，也就是游戏中图片开始的位置
#define left_x 13
#define left_y 180
//每个小方块的长宽
#define block_x 31
#define block_y 35

void picture_process(IMAGE *src)
{
	IMAGE vec[11][19];
	memset(flagMap, 0, sizeof(flagMap));

	int x_pos = left_x;
	int y_pos = left_y;

	SetWorkingImage(src);

	//切割各个小方块图片
	for (int i=0; i<11; i++){
		for (int j=0; j<19; j++){
			getimage(&vec[i][j], x_pos+5, y_pos+5, block_x-10, block_y-10);
			x_pos += block_x;
		}
		x_pos = left_x;
		y_pos += block_y;
	}

	//吧图片数组转换为数字数组，相同的图片对应为一个最早出现这个图片的数组下标（下标加1）
	for (int i = 0; i<11; i++){
		for(int j = 0; j<19; j++){
			if(flagMap[i][j] != 0) continue;

			for(int m = 0; m<11; m++){
				for(int n = 0; n<19; n++){
					if(i == m && j==n) continue;
					if(flagMap[m][n] == 0 && imgSame(&vec[i][j], &vec[m][n])){
						flagMap[i][j] = i * 19 + j + 1;
						flagMap[m][n] = i * 19 + j + 1;
					}
				}
			}
		}
	}

	//取出空白方块
	IMAGE blankImg;
	loadimage(&blankImg, "empty.png");
	for (int i = 0; i<11; i++){
		for(int j=0; j<19; j++){
			if(imgSame(&vec[i][j], &blankImg)){
				int val = flagMap[i][j];
				for(int m = 0; m<11; m++){
					for(int n=0; n<19; n++){
						if(flagMap[m][n] == val){
							flagMap[m][n] = 0;
						}
					}
				}
				return;
			}
		}
	}



}

void printMap(){
	for(int i=0; i<11; i++){
		for(int j=0; j<19; j++){
			if(flagMap[i][j] == 0)
				printf("	");
			else
				printf("%4d", flagMap[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int flagMap[11][19] = {0,};

int main(){
	printf("准备好了吗");
	system("pause");

	//1. 找到游戏窗口
	HWND hq = FindWindow(NULL, "QQ游戏 - 连连看角色版");
	
	RECT rect;//定义一个RECT类型的变量  RECT就是表示位置和大小类型的变量
	GetWindowRect(hq, &rect);//获取位置并赋值给rect 用指针传递
	int w = rect.right - rect.left; //用最左边的位置减去最右边的位置，获取宽度
	int h = rect.bottom - rect.top; //用最下边的位置减去最上边的位置，获取高度
	
	//2. 移动窗口，方便截图
	MoveWindow(hq, 0, 0, w, h, false); //移动窗口的函数，参数分别为 ： 窗口， x位置，y位置， 宽度，高度， 是否重置？
	Sleep(2000);
	
	//3. 截图
	//IMAGE src = getScreen();

	//initgraph(800,600);
	//putimage(0,0,&src);
	//system("pause");
	
	
	Mat src = getScreen();
	picture_process(src);
	printMap();

	return 0;

}
