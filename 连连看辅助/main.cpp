#include <stdio.h>
#include <windows.h>
#include "tools.h"
//ͼƬ���Ͻ����꣬Ҳ������Ϸ��ͼƬ��ʼ��λ��
#define left_x 13
#define left_y 180
//ÿ��С����ĳ���
#define block_x 31
#define block_y 35

void picture_process(IMAGE *src)
{
	IMAGE vec[11][19];
	memset(flagMap, 0, sizeof(flagMap));

	int x_pos = left_x;
	int y_pos = left_y;

	SetWorkingImage(src);

	//�и����С����ͼƬ
	for (int i=0; i<11; i++){
		for (int j=0; j<19; j++){
			getimage(&vec[i][j], x_pos+5, y_pos+5, block_x-10, block_y-10);
			x_pos += block_x;
		}
		x_pos = left_x;
		y_pos += block_y;
	}

	//��ͼƬ����ת��Ϊ�������飬��ͬ��ͼƬ��ӦΪһ������������ͼƬ�������±꣨�±��1��
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

	//ȡ���հ׷���
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
	printf("׼��������");
	system("pause");

	//1. �ҵ���Ϸ����
	HWND hq = FindWindow(NULL, "QQ��Ϸ - ��������ɫ��");
	
	RECT rect;//����һ��RECT���͵ı���  RECT���Ǳ�ʾλ�úʹ�С���͵ı���
	GetWindowRect(hq, &rect);//��ȡλ�ò���ֵ��rect ��ָ�봫��
	int w = rect.right - rect.left; //������ߵ�λ�ü�ȥ���ұߵ�λ�ã���ȡ���
	int h = rect.bottom - rect.top; //�����±ߵ�λ�ü�ȥ���ϱߵ�λ�ã���ȡ�߶�
	
	//2. �ƶ����ڣ������ͼ
	MoveWindow(hq, 0, 0, w, h, false); //�ƶ����ڵĺ����������ֱ�Ϊ �� ���ڣ� xλ�ã�yλ�ã� ��ȣ��߶ȣ� �Ƿ����ã�
	Sleep(2000);
	
	//3. ��ͼ
	//IMAGE src = getScreen();

	//initgraph(800,600);
	//putimage(0,0,&src);
	//system("pause");
	
	
	Mat src = getScreen();
	picture_process(src);
	printMap();

	return 0;

}
