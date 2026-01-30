#include <stdlib.h>
#include<graphics.h>
#include<math.h>
#include<easyx.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
void jim();
void quan();
void renji();
int panduan1();
int panduan2();
void restartGame();
int A = 1, M = 0;
int a[20][20] = { 0 }; //全局变量
long long score[16][16] = { 0 };
int t=0;
int stack[2] = {0};
int shunxu = 0;
int one, two;
//HWND hwnd = GetHWnd();
void weizhi(int& qx, int& qy, int& X, int& Y)
{
	MOUSEMSG Msg = GetMouseMsg();
	for (int i = 0; i < 20; i++)//行y
	{
		for (int p =0; p < 20; p++)//列x
		{
			if (abs(Msg.x - p * 40) < 20 && abs(Msg.y - i * 40) < 20)//优化鼠标位置
			{
				qx = p * 40; qy = i * 40;
				X = p; Y = i;//i  p
			}
		}
	}
}
typedef struct
{
	int xx;
	int yx;
}move;
move his[16 * 16];
void push(int x, int y)
{
	his[t].xx = x;
	his[t].yx = y;
}
void Line()
{
	setlinecolor(BLACK);
	for (int i = 1; i < 16; i++)
	{
		line(40, i * 40, 600, i * 40);//横线//每个格子距离为40	   680
	}
	for (int i = 1; i < 16; i++)
	{
		line(i * 40, 40, i * 40, 600);//竖线720
	}
	setlinestyle(PS_SOLID, 2);//边界线
	line(600, 40, 600, 600); line(40, 40, 600, 40);
	line(40, 40, 40, 600); line(40, 600, 600, 600);
}
void beij()//制作背景
{
	initgraph(800, 650);
	IMAGE img;
	loadimage(&img, "bj.jpg", 800, 650);
	putimage(0, 0, &img);
	setlinecolor(BLACK);
	Line();
	setbkmode(0);//背景透明
	setfillcolor(BLACK);    //画棋盘上的五个点
	setfillstyle(BS_SOLID);
	fillcircle(320, 320, 5);fillcircle(80, 80, 5);
	fillcircle(560, 80, 5);fillcircle(80, 560, 5);
	fillcircle(560, 560, 5);//边框
	line(680, 280, 730, 280);line(730, 280, 730, 310);line(680, 280, 680, 310);line(680, 310, 730, 310);
	line(680, 400, 730, 400);line(730, 400, 730, 430);line(680, 400, 680, 430);line(680, 430, 730, 430);
	settextcolor(MAGENTA);
	outtextxy(690, 290, "悔棋");
	outtextxy(690, 410, "返回");
}
void Return(int qx, int qy)//返回函数
{
	HWND hwnd = GetHWnd();
	if (qx < 730 && qy < 430 && qy >= 400 && qx >= 680)
	{
		int D = MessageBox(hwnd, "是否返回菜单？", "Game Over？", MB_YESNO | MB_SYSTEMMODAL);
		if (D == IDYES)
		{
			A = 1;
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
					a[i][j] = 0;
			}
			//t = 0;
			shunxu = 0;
			jim();
		}
	}
}
void hui(int qx,int qy)//悔棋函数
{
	HWND hwnd = GetHWnd();
	if (qx < 740 && qy < 320 && qy >= 280 && qx >= 680)
	{
		int C = MessageBox(hwnd, "是否悔棋?", "", MB_YESNO | MB_SYSTEMMODAL);
		if (C == IDYES)
		{
			if (M==1)
			{
				t--;
				int ax = his[t].xx;
				int ay = his[t].yx;
				a[ax][ay] = 0;
			}
			t--;
			int ax = his[t].xx;
			int ay = his[t].yx;
			a[ax][ay] = 0;
			beij();
			for (int U = 1; U < 17; U++)
			{
				for (int j = 1; j < 17; j++)
				{
					if (a[U][j] == 1)
					{
						setfillcolor(one);//黑棋
						solidcircle(U* 40, j * 40, 20);
					}
					if (a[U][j] == 2)
					{
						setfillcolor(two);
						solidcircle(U * 40, j * 40, 20);
					}
				}
			}
		}
	}
}
void white(int qx, int qy)//下白棋
{
	HWND hwnd = GetHWnd();
	int X = qx / 40;
	int Y = qy / 40;
	if (qx <= 620 && qy <= 620 && qy >= 40 && qx >= 40)
	{
		if (a[X][Y] == 0)
		{
			setfillcolor(two);
			solidcircle(qx, qy, 20);
			a[X][Y] = 2;
			push(X, Y);
			printf("玩家落子\n");
			if (panduan2() == 2)
			{
				MessageBox(hwnd, "玩家胜利！", "Game Over！", MB_OK | MB_SYSTEMMODAL);
				restartGame();
			}
			else
			{
				t++;
				printf("t+\n");
				printf("t=%d\n ", t);
			}
		}
	}
}
void shubiao()//鼠标点击
{
	settextcolor(BLACK);
	outtextxy(680, 160, "玩家一：黑棋");
	outtextxy(680, 190, "玩家二：白棋");//边框
	MOUSEMSG Msg;
	int qx = 0, qy = 0, i, p;//记录棋子坐标
	int X = 0, Y = 0;//记录地图下标
	HWND hwnd = GetHWnd();
	while (1)
	{
		Msg = GetMouseMsg();
		for (i = 0; i < 20; i++)//行y
		{
			for (p = 0; p < 20; p++)//列x
			{
				if (abs(Msg.x - p * 40) < 20 && abs(Msg.y - i * 40) < 20)//优化鼠标位置
				{
					qx = p * 40; qy = i * 40;
					X = p; Y = i;//i  p
				}

			}
		}
		/*weizhi(qx, qy,X,Y);*/
		printf("x=%d,y=%d", qx, qy);
		if (Msg.uMsg == WM_LBUTTONDOWN)
		{
			if (qx < 620 && qy < 620 && qy >= 40 && qx >= 40)
			{
				if (a[X][Y] == 0)
				{
					push(X, Y);
					if (t % 2 == 0)//谁来下棋
					{
						setfillcolor(BLACK);//黑棋
						solidcircle(qx, qy, 20);
						a[X][Y] = 1;
						if (panduan1() == 1)
						{
							MessageBox(hwnd, "玩家一黑棋胜利！", "Game Over!", MB_OK | MB_SYSTEMMODAL);
							restartGame();
						}
						else
							t++;
					}
					else
						white(qx,qy);
				}
			}
			Return(qx,qy);//返回函数
			hui( qx, qy);
		}
	}
}
int main()
{
	jim();
	return 0;
}
// 判断玩家一是否胜利
int panduan1() {
	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 16; j++)
		{
			// 横向判断
			if (j <= 15) 
			{
				int count = 0;
				for (int k = 0; k < 5; k++) 
				{
					if (a[i][j + k] == 1) 
					{
						count++;
						if (k > 0 && a[i][j + k - 1] != 1) 
							count = 1; // 出现间隔，重新计数						
					}
					else 
						count = 0; // 遇到非己方棋子，重新计数					
				}
				if (count == 5) 
					return 1;
				
			}
			// 纵向判断
			if (i <= 15) 
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j] == 1) 
					{
						count++;
						if (k > 0 && a[i + k - 1][j] != 1) 
							count = 1;
					}
					else 
						count = 0;					
				}
				if (count == 5) 
					return 1;
			}
			// 正斜向判断
			if (i <= 15 && j <= 15) 
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j + k] == 1) 
					{
						count++;
						if (k > 0 && a[i + k - 1][j + k - 1] != 1) 
							count = 1;
					}
					else 
						count = 0;
				}
				if (count == 5) 
					return 1;
				
			}
			// 反斜向判断
			if (i <= 15 && j >= 4)
			{
				int count = 0;
				for (int k = 0; k < 5; k++) 
				{
					if (a[i + k][j - k] == 1)
					{
						count++;
						if (k > 0 && a[i + k - 1][j - k + 1] != 1) 
							count = 1;
					}
					else 
						count = 0;
				}
				if (count == 5) 
					return 1;
			}
		}
	}
	return 0;
}
int panduan2()
{
	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 16; j++)
		{
			// 横向判断
			if (j <= 15)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i][j + k] == 2) 
					{
						count++;
						if (k > 0 && a[i][j + k - 1] != 2) 
							count = 1; // 出现间隔，重新计数
					}
					else 
						count = 0; // 遇到非己方棋子，重新计数
				}
				if (count == 5)
					return 2;
			}
			// 纵向判断
			if (i <= 15) 
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j] == 2)
					{
						count++;
						if (k > 0 && a[i + k - 1][j] != 2) 
							count = 1;
					}
					else
						count = 0;
				}
				if (count == 5) 
					return 2;
			}
			// 正斜向判断
			if (i <= 15 && j <= 15)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j + k] == 2)
					{
						count++;
						if (k > 0 && a[i + k - 1][j + k - 1] != 2) 						
							count = 1;
					}
					else 
						count = 0;					
				}
				if (count == 5) 
					return 2;				
			}
			// 反斜向判断
			if (i <= 15 && j >= 4) 
			{
				int count = 0;
				for (int k = 0; k < 5; k++) 
				{
					if (a[i + k][j - k] == 2) 
					{
						count++;
						if (k > 0 && a[i + k - 1][j - k + 1] != 2) 
							count = 1;
					}
					else 
						count = 0;
				}
				if (count == 5) 
					return 2;			
			}
		}
	}
	return 0;
}

void gui02()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			a[i][j] = 0;
			score[i][j] = 0;
		}
	}
}
void restartGame()// 重新开局函数
{
	HWND hwnd = GetHWnd();
	int result = MessageBox(hwnd, "是否重新开始？", "Game Over", MB_YESNOCANCEL | MB_SYSTEMMODAL);
	if (result == IDYES)
	{
		gui02();
		shunxu = 1;
		jim();
	}
	else
	{
		A = 1;
		shunxu = 0;
		gui02();
		jim();
	}
}
void wen()//用于显示文字并做出选择
{
	settextstyle(30, 0, _T("黑体"));
	settextcolor(BLACK);//文字颜色
	if (shunxu == 0)
	{
		outtextxy(200, 300, _T("双人对战"));
		outtextxy(200, 400, _T("人机对战"));
		outtextxy(200, 500, _T("退出游戏"));
		setlinecolor(BLACK);
		line(200, 490, 200, 550); line(330, 490, 330, 550); line(200, 490, 330, 490); line(200, 550, 330, 550);
		line(200, 390, 200, 450); line(330, 390, 330, 450); line(200, 390, 330, 390); line(200, 450, 330, 450);
		line(200, 290, 200, 350); line(330, 290, 330, 350); line(200, 290, 330, 290); line(200, 350, 330, 350);
	}
	if (shunxu == 1)
	{
		outtextxy(200, 250, _T("请选择您要"));
		outtextxy(200, 300, _T("使用的棋子"));
		outtextxy(200, 400, _T("黑棋（先行）"));
		outtextxy(200, 500, _T("白棋（后行）"));
		setlinecolor(BLACK);
		line(200, 490, 200, 550); line(370, 490, 370, 550); line(200, 490, 370, 490); line(200, 550, 370, 550);
		line(200, 390, 200, 450); line(370, 390, 370, 450); line(200, 390, 370, 390); line(200, 450, 370, 450);
	}
}
void jim()//开始界面
{
	M = 0;
	initgraph(500, 800);
	IMAGE img;
	loadimage(&img, "jie.jpg", 500, 800);
	putimage(0, 0, &img);
	setbkmode(0);//背景透明
	wen();//文字函数
	MOUSEMSG Msg;
	int qx = 0, qy = 0, i, p;//记录棋子坐标
	int X = 0, Y = 0;//记录地图下标
	HWND hwnd = GetHWnd();
	while (A)
	{
		Msg = GetMouseMsg();
		weizhi(qx, qy, X, Y);
		if (Msg.uMsg == WM_LBUTTONDOWN)
		{
			if (shunxu == 0)
			{
				if (qx < 330 && qy < 350 && qy >= 290 && qx >= 200)
				{
					beij();
					two = WHITE;
					shubiao();
					A = 0;
				}
				if (qx < 330 && qy < 550 && qy >= 490 && qx >= 200)
					exit(0);
				if (qx < 330 && qy < 450 && qy >= 390 && qx >= 200)
				{
					shunxu = 1;
					jim();
				}
			}
			if (shunxu == 1) 
			{
				if (qx < 370 && qy < 550 && qy >= 490 && qx >= 200)
				{
					one = BLACK;
					two = WHITE;
					t = 0;
					M = 1;
					renji();
				}
				if (qx < 370 && qy < 450 && qy >= 390 && qx >= 200)
				{
					two = BLACK;
					one = WHITE;
					t = 1;
					M = 1;
					renji();
				}
			}
		}
	}
	closegraph();
}
//人机对战
int as[8][2] = { {-1,-1},{-1,0} ,{-1,1},{0,1},{0,-1},{1,1} ,{1,0},{1,-1} };
void renji()//人机下棋
{
	beij();//背景函数
	settextcolor(BLACK);
	/*outtextxy(680, 130, "电脑：黑棋");
	outtextxy(680, 160, "玩家：白棋");*/
	MOUSEMSG Msg;
	int qx = 0, qy = 0;//记录棋子坐标
	int X = 0, Y = 0;//记录地图下标
	int cou = 0;
	HWND hwnd = GetHWnd();
	while (1)
	{
		Msg = GetMouseMsg();
		for (int i = 0; i < 20; i++)//行y
		{
			for (int p = 0; p < 20; p++)//列x
			{
				if (abs(Msg.x - p * 40) < 20 && abs(Msg.y - i * 40) < 20)//优化鼠标位置
				{
					qx = p * 40; qy = i * 40;
					X = p; Y = i;
				}
			}
		}
		//weizhi(qx, qy, X, Y);
		/*printf("x=%d,y=%d\n", qx, qy);*/
if (Msg.uMsg == WM_LBUTTONDOWN)
		{
			printf("读取鼠标位置\n");
			if (a[X][Y] == 0)
			{
				
				if (t % 2 != 0)
				{
					white(qx, qy);
				}
			}
			hui(qx, qy);
			Return(qx, qy);
			printf("\n");
		}

		if (t % 2 == 0)//电脑
		{
			quan();
			int max = 0;
			int wei[50][2] = { 0 };
			for (int i = 1; i < 16; i++)
			{
				for (int j = 1; j < 16; j++)
				{
					if (score[i][j] > max)
					{
						max = score[i][j];//最大值
						cou = 0;
						wei[cou][0] = i;//最大值位置
						wei[cou][1] = j;
						cou++;
						printf("寻找最大值\n");
					}
					else if (score[i][j] == max && max != 0)
					{
						wei[cou][0] = i;
						wei[cou][1] = j;
						cou++;
					}
				}
			}
			if (cou > 0) {
				printf("寻找位置\n");
				srand((unsigned int)time(NULL));
				int found = 0;
				while (!found) {
					int randomIndex = rand() % cou;
					int hx = wei[randomIndex][0] * 40;
					int hy = wei[randomIndex][1] * 40;
					if (a[wei[randomIndex][0]][wei[randomIndex][1]] == 0)
					{
						printf("电脑落子\n");
						setfillcolor(one);
						solidcircle(hx, hy, 20);
						a[wei[randomIndex][0]][wei[randomIndex][1]] = 1;
						push(wei[randomIndex][0], wei[randomIndex][1]);
						if (panduan1() == 1)
						{
							MessageBox(hwnd, "电脑胜利！", "Game Over!", MB_OK | MB_SYSTEMMODAL);
							restartGame();
						}
						else
						{
							t++;
							printf("黑t+\n");
							printf("t=%d\n ", t);
						}
						found = 1;
					}
				}
			}
		}
		quan();
		//printf("t=%d\n ", t);
		
	}
}
void gui0()//清空权值数组
{
	for (int i = 0; i < 16; i++)//行y
	{
		for (int p = 0; p < 16; p++)//列x
				score[i][p] = 0;
	}
	//for (int i = 1; i <= 16; i++)	//0  20
	//{
	//	for (int j = 1; j <= 16; j++)
	//	{
	//		if (a[i][j] != 0)
	//			score[i][j] = 0;
	//	}
	//}///
}
void jianyan()//检验权值
{
	for (int i = 1; i < 16; i++)//行y
	{
		for (int p = 1; p < 16; p++)//列x
		{
			printf("%8d", score[p][i]);
		}
		printf("\n");
	}
}
	//					0			1			2			3		 4			5
	int qzhi[15] = { {10000000},{ 9000000 },{ 600000 },{ 550000 },{290000},{250000},
			{200000},{150000},{100000},{90000},{3000},{-1000000000} };
	//		   6		 7		8		   9	 10		  11	 
void yizi()
{
	for (int i = 1; i < 16; i++)
	{
		for (int j = 1; j < 16; j++)
		{
			if (a[i][j] == 1 || a[i][j] == 2)
			{
				if (i != 1 && i != 16 && j != 1 && j != 16)
				{
					for (int s = 0; s < 8; s++)
					{
						int	qw = i + as[s][0];
						int	zx = j + as[s][1];
						score[qw][zx] += qzhi[10];//每个棋子周围加5000；
					}
				}
			}
		}
	}	
}
void heiping()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (a[i][j] != 0 || i < 1 || i>16 || j < 1 || j>16)
				score[i][j] = 0;
			if (j <= 16)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i][j + k] == 1 && j + k <= 15)//16
						count++;
					else break;
				}
				if (count == 4)
				{
					if (j + 4 <= 15)
						score[i][j + count] += qzhi[0];
					if (j - 1 >= 1)
						score[i][j - 1] += qzhi[0];
				}
				if (count == 3)
				{
					if (a[i][j + count] == 2 || a[i][j - 1] == 2)
					{
						score[i][j + count] += qzhi[4];
						if (j - 1 > 0)
							score[i][j - 1] += qzhi[4];
					}
					else
					{
						score[i][j + count] += qzhi[2];
						if (j - 1 > 0)
							score[i][j - 1] += qzhi[2];
					}
					if (a[i][j + count + 1] == 1)
						score[i][j + count] += qzhi[2];//基础上再加
					if (a[i][j + count + 1] == 2 && a[i][j - 1] == 2)
						score[i][j + count] -= qzhi[4];
					if (j - 1 >= 1 && j + count + 1 <= 15)
					{
						if (a[i][j - 2] == 2 && a[i][j + count + 1] == 2 && j - 1 > 0)
							score[i][j - 1] -= qzhi[4];
						if (a[i][j - 2] == 1)
							score[i][j - 1] += qzhi[2];
					}
				}
				if (count == 2)
				{
					if (a[i][j + count] == 2 || a[i][j - 1] == 2)
					{
						score[i][j + count] += qzhi[8];
						if (j - 1 >= 1)
							score[i][j - 1] += qzhi[8];
					}
					else
					{
						score[i][j + count] += qzhi[6];
						if (j - 1 >= 1)
							score[i][j - 1] += qzhi[6];
					}
					if (a[i][j + count + 1] == 1 && a[i][j + count + 2] != 2)//只有两个棋子时加入限制
						score[i][j + count] += qzhi[6];
					if (a[i][j + count + 1] == 2 && a[i][j - 1] == 2)
						score[i][j + count] -= qzhi[8];
					if (j - 2 >= 1)
					{
						if (a[i][j - 2] == 1 && a[i][j - 3] != 2)
							score[i][j - 1] += qzhi[6];
						if (a[i][j - 2] == 2 && a[i][j + count + 1] == 2)
							score[i][j - 1] -= qzhi[8];
					}
				}
			}
		}
	}
}
void heishu()
{
	for (int i = 1; i < 16; i++)
	{
		for (int j = 1; j < 16; j++)
		{
			if (i < 16)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j] == 1 && i + k <= 15)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j] += qzhi[0];
					if (i - 1 >= 1)
						score[i - 1][j] += qzhi[0];
				}
				if (count == 3)
				{
					if (a[i + count][j] == 2 || a[i - 1][j] == 2)
					{
						score[i + count][j] += qzhi[4];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[4];
					}
					else
					{
						score[i + count][j] += qzhi[2];
						if (i > 1)
							score[i - 1][j] += qzhi[2];
					}
					if (i - 1 >= 1)
					{
						if (a[i - 2][j] == 1)
							score[i - 1][j] += qzhi[2];
						if (a[i - 2][j] == 2 && a[i + count][j] == 2)
							score[i - 1][j] -= qzhi[4];
					}
					if (a[i + count + 1][j] == 2 && a[i - 1][j] == 2)
						score[i + count][j] -= qzhi[4];
					if (a[i + count + 1][j] == 1)
						score[i + count][j] += qzhi[2];
				}
				if (count == 2)
				{
					if (a[i + count][j] == 2 || a[i - 1][j] == 2)
					{
						score[i + count][j] += qzhi[8];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[8];
					}
					else
					{
						score[i + count][j] += qzhi[6];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[6];
					}
					if (a[i + count + 1][j] == 1 && a[i + count + 2][j] != 2)
						score[i + count][j] += qzhi[6];
					if (a[i + count + 1][j] == 2 && a[i - 1][j] == 2)
						score[i + count][j] -= qzhi[8];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j] == 2 && a[i + count][j] == 2)
							score[i - 1][j] -= qzhi[8];
						if (a[i - 2][j] == 1 && a[i - 3][j] != 2)
							score[i - 1][j] += qzhi[6];
					}
				}
			}
		}
	}
}
void heixie()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (i <= 15 && j <= 15)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j + k] == 1 && i + k <= 15 && j + k <= 15)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j + count] += qzhi[0];
					if (i - 1 >= 1 && j - 1 >= 1)
						score[i - 1][j - 1] += qzhi[0];
				}
				if (count == 3)
				{
					if (a[i + count][j + count] == 2 || a[i - 1][j - 1] == 2)
					{
						score[i + count][j + count] += qzhi[4];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[4];
					}
					else
					{
						score[i + count][j + count] += qzhi[2];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[2];
					}
					if (a[i + count + 1][j + count + 1] == 1)
						score[i + count][j + count] += qzhi[2];
					if (a[i + count + 1][j + count + 1] == 2 && a[i - 1][j - 1] == 2)
						score[i + count][j + count] -= qzhi[4];
					if (i - 1 >= 1 && j - 1 >= 1)
					{
						if (a[i - 2][j - 2] == 2 && a[i + count][j + count] == 2)
							score[i - 1][j - 1] -= qzhi[4];
						if (a[i - 2][j - 2] == 1)
							score[i - 1][j - 1] += qzhi[2];
					}
				}
				if (count == 2)
				{
					if (a[i + count][j + count] == 2 || a[i - 1][j - 1] == 2)
					{
						score[i + count][j + count] += qzhi[8];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[8];
					}
					else
					{
						score[i + count][j + count] += qzhi[6];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[6];
					}
					if (a[i + count + 1][j + count + 1] == 1 && a[i + count + 2][i + count + 2] != 2)
						score[i + count][j + count] += qzhi[6];
					if (a[i + count + 1][j + count + 1] == 2 && a[i - 1][j - 1] == 2)
						score[i + count][j + count] -= qzhi[8];
					if (i - 1 >= 1 && j - 1 >= 1)
					{
						if (a[i - 2][j - 2] == 2 && a[i + count][j + count] == 2)
							score[i - 1][j - 1] -= qzhi[8];
						if (a[i - 2][j - 2] == 1 && a[i - 3][j - 3] != 2)
							score[i - 1][j - 1] += qzhi[6];
					}
				}
			}
		}
	}
}
void heifan()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (i <= 15 && j >= 4)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j - k] == 1 && i + k <= 15 && j - k >= 1)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j - count] += qzhi[0];
					if (i - 1 >= 1)
						score[i - 1][j + 1] += qzhi[0];
				}
				if (count == 3)
				{
					if (a[i + count][j - count] == 2 || a[i - 1][j + 1] == 2)
					{
						score[i + count][j - count] += qzhi[4];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[4];
					}
					else
					{
						score[i + count][j - count] += qzhi[2];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[2];
					}
					if (a[i + count + 1][j - count - 1] == 1)
						score[i + count][j - count] += qzhi[2];
					if (a[i + count + 1][j - count - 1] == 2 && a[i - 1][j + 1] == 2)
						score[i + count][j - count] -= qzhi[4];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j + 2] == 2 && a[i + count][j - count] == 2)
							score[i - 1][j + 1] -= qzhi[4];
						if (a[i - 2][j + 2] == 1)
							score[i - 1][j + 1] += qzhi[2];
					}
				}
				if (count == 2)
				{
					if (a[i + count][j - count] == 2 || a[i - 1][j + 1] == 2)
					{
						score[i + count][j - count] += qzhi[8];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[8];
					}
					else
					{
						score[i + count][j - count] += qzhi[6];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[6];
					}
					if (a[i + count + 1][j - count - 1] == 1 && a[i + count + 2][j - count - 2] != 2)
						score[i + count][j - count] += qzhi[6];
					if (a[i + count + 1][j - count - 1] == 2 && a[i - 1][j + 1] == 2)
						score[i + count][j - count] -= qzhi[8];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j + 2] == 2 && a[i + count][j - count] == 2)
							score[i - 1][j + 1] -= qzhi[8];
						if (a[i - 2][j + 2] == 1 && a[i - 3][i - 3] != 2)
							score[i - 1][j + 1] += qzhi[6];
					}
				}
			}
		}
	}
}
void baiping()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (j <= 15)//白棋权重
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i][j + k] == 2 && j + k <= 15)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i][j + count] += qzhi[1];
					if (j - 1)
						score[i][j - 1] += qzhi[1];
				}
				if (count == 3)
				{
					if (a[i][j + count] == 1 || a[i][j - 1] == 1)
					{
						score[i][j + count] += qzhi[5];
						if (j - 1)
							score[i][j - 1] += qzhi[5];
					}
					else
					{
						score[i][j + count] += qzhi[3];
						if (j - 1)
							score[i][j - 1] += qzhi[3];
					}
					if (a[i][j + count + 1] == 2)
						score[i][j + count] += qzhi[3];
					if (a[i][j + count + 1] == 1 && a[i][j - 1] == 1)
						score[i][j + count] -= qzhi[5];
					if (j - 1)
					{
						if (a[i][j - 2] == 1 && a[i][j + count + 1] == 1)
							score[i][j - 1] -= qzhi[5];
						if (a[i][j - 2] == 2)
							score[i][j - 1] += qzhi[3];
					}
				}
				if (count == 2)
				{
					if (a[i][j + count] == 1 || a[i][j - 1] == 1)
					{
						score[i][j + count] += qzhi[9];
						if (j - 1)
							score[i][j - 1] += qzhi[9];
					}
					else
					{
						score[i][j + count] += qzhi[7];
						if (j - 1)
							score[i][j - 1] += qzhi[7];
					}
					if (a[i][j + count + 1] == 2 && a[i][j + count + 2] != 1)
						score[i][j + count] += qzhi[9];
					if (a[i][j + count + 1] == 1 && a[i][j - 1] == 1)
						score[i][j + count] -= qzhi[7];
					if (j - 1)
					{
						if (a[i][j - 2] == 1 && a[i][j + count] == 1)
							score[i][j - 1] -= qzhi[7];
						if (a[i][j - 2] == 2 && a[i][j - 3] != 1)
							score[i][j - 1] += qzhi[9];
					}
				}
			}
		}
	}
}
void baishu()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (i <= 15)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j] == 2 && i + k <= 15)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j] += qzhi[1];
					if (i - 1 >= 1)
						score[i - 1][j] += qzhi[1];
				}
				if (count == 3)
				{
					if (a[i + count][j] == 1 || a[i - 1][j] == 1)
					{
						score[i + count][j] += qzhi[5];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[5];
					}
					else
					{
						score[i + count][j] += qzhi[3];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[3];
					}
					if (a[i + count + 1][j] == 2)
						score[i + count][j] += qzhi[3];
					if (a[i + count + 1][j] == 1 && a[i - 1][j] == 1)
						score[i + count][j] -= qzhi[5];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j] == 1 && a[i + count][j] == 1)
							score[i - 1][j] -= qzhi[5];
						if (a[i - 2][j] == 2)
							score[i - 1][j] += qzhi[3];
					}
				}
				if (count == 2)
				{
					if (a[i + count][j] == 1 || a[i - 1][j] == 1)
					{
						score[i + count][j] += qzhi[9];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[9];
					}
					else
					{
						score[i + count][j] += qzhi[7];
						if (i - 1 >= 1)
							score[i - 1][j] += qzhi[7];
					}
					if (a[i + count + 1][j] == 2)
						score[i + count][j] += qzhi[7];
					if (a[i + count + 1][j] == 1 && a[i - 1][j] == 1)
						score[i + count][j] -= qzhi[9];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j] == 1 && a[i + count][j] == 1)
							score[i - 1][j] -= qzhi[9];
						if (a[i - 2][j] == 2)
							score[i - 1][j] += qzhi[7];
					}
				}
			}
		}
	}
}
void baixie()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (i <= 15 && j <= 15)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j + k] == 2 && i + k <= 15 && j + k <= 15)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j + count] += qzhi[1];
					if (i - 1 >= 1 && j - 1 >= 1)
						score[i - 1][j - 1] += qzhi[1];
				}
				if (count == 3)
				{
					if (a[i + count][j + count] == 1 || a[i - 1][j - 1] == 1)
					{
						score[i + count][j + count] += qzhi[5];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[5];
					}
					else
					{
						score[i + count][j + count] += qzhi[3];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[3];
					}
					if (a[i + count + 1][j + count + 1] == 2)
						score[i + count][j + count] += qzhi[3];
					if (a[i + count + 1][j + count + 1] == 1 && a[i - 1][j - 1] == 1)
						score[i + count][j + count] -= qzhi[5];
					if (i - 1 >= 1 && j - 1 >= 1)
					{
						if (a[i - 2][j - 2] == 1 && a[i + count][j + count] == 1)
							score[i - 1][j - 1] -= qzhi[5];
						if (a[i - 2][j - 2] == 2)
							score[i - 1][j - 1] += qzhi[3];
					}
				}
				if (count == 2)
				{
					if (a[i + count][j + count] == 1 || a[i - 1][j - 1] == 1)
					{
						score[i + count][j + count] += qzhi[9];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[9];
					}
					else
					{
						score[i + count][j + count] += qzhi[7];
						if (i - 1 >= 1 && j - 1 >= 1)
							score[i - 1][j - 1] += qzhi[7];
					}
					if (a[i + count + 1][j + count + 1] == 2 && a[i + count + 2][j + count + 2] != 1)
						score[i + count][j + count] += qzhi[7];
					if (a[i + count + 1][j + count + 1] == 1 && a[i - 1][j - 1] == 1)
						score[i + count][j + count] -= qzhi[9];
					if (i - 1 >= 1 && j - 1 >= 1)
					{
						if (a[i - 2][j - 2] == 1 && a[i + count][j + count] == 1)
							score[i - 1][j - 1] -= qzhi[9];
						if (a[i - 2][j - 2] == 2 && a[i - 3][j - 3] != 1)
							score[i - 1][j - 1] += qzhi[7];
					}
				}
			}
		}
	}
}
void baifan()
{
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (i <= 15 && j >= 4)
			{
				int count = 0;
				for (int k = 0; k < 5; k++)
				{
					if (a[i + k][j - k] == 2 && i + k <= 15 && j - k >= 1)
						count++;
					else
						break;
				}
				if (count == 4)
				{
					score[i + count][j - count] += qzhi[1];
					if (i - 1 >= 1)
						score[i - 1][j + 1] += qzhi[1];
				}
				if (count == 3)
				{
					if (a[i + count][j - count] == 1 || a[i - 1][j + 1] == 1)
					{
						score[i + count][j - count] += qzhi[5];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[5];
					}
					else
					{
						score[i + count][j - count] += qzhi[3];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[3];
					}
					if (a[i + count + 1][j - count - 1] == 2)
						score[i + count][j - count] += qzhi[3];
					if (a[i + count + 1][j - count - 1] == 1 && a[i - 1][j + 1] == 1)
						score[i + count][j - count] -= qzhi[5];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j + 2] == 1 && a[i + count][j - count] == 1)
							score[i - 1][j + 1] -= qzhi[5];
						if (a[i - 2][j + 2] == 2)
							score[i - 1][j + 1] += qzhi[3];
					}
				}
				if (count == 2)
				{
					if (a[i + count][j - count] == 1 || a[i - 1][j + 1] == 1)
					{
						score[i + count][j - count] += qzhi[9];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[9];
					}
					else
					{
						score[i + count][j - count] += qzhi[7];
						if (i - 1 >= 1)
							score[i - 1][j + 1] += qzhi[7];
					}
					if (a[i + count + 1][j - count - 1] == 2 && a[i + count + 2][j - count - 2] != 1)
						score[i + count][j - count] += qzhi[7];
					if (a[i + count + 1][j - count - 1] == 1 && a[i - 1][j + 1] == 1)
						score[i + count][j - count] -= qzhi[9];
					if (i - 1 >= 1)
					{
						if (a[i - 2][j + 2] == 1 && a[i + count][j - count] == 1)
							score[i - 1][j + 1] -= qzhi[9];
						if (a[i - 2][j + 2] == 2 && a[i - 3][j + 3] != 1)
							score[i - 1][j + 1] += qzhi[7];
					}
				}
			}
			if (a[i][j] == 1||a[i][j]==2||i < 1 || i>16 || j < 1 || j>16)
				score[i][j] = 0; 
		}
	}
}
void quan()//人机判断
{
	printf("1t=%d\n", t);
	gui0();
	printf("2t=%d\n", t);
	score[8][8] = 1000;
	yizi();
	heiping();
	heishu();
	heixie();
	heifan();
	baiping();
	baishu();
	baifan();
	baixie();
	jianyan();
	for (int i = 1; i < 16; i++)	//0  20
	{
		for (int j = 1; j < 16; j++)
		{
			if (a[i][j] != 0)
				score[i][j] = 0;
		}
	}
}