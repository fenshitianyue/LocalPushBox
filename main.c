#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>

/******************************
元素映射：
**	0表示空白
**  1表示砖块
**  2表示箱子
**	3表示小人的位置
**	4表示目标位置
**	5表示箱子到达目标后的位置
**	6表示小人到达目标后的位置
******************************/
int x = 0, y = 0;
int map[10][10] = { 0 };

int map_1[10][10] = {

	{ 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 1, 4, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 2, 4, 1 },
	{ 1, 4, 2, 2, 0, 1, 1, 1 },
	{ 1, 1, 1, 3, 2, 1, 0, 0 },
	{ 0, 0, 0, 1, 4, 1, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0 }
};
int map_2[10][10] = {
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 0, 0, 1, 0, 3, 1 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 0, 0, 1, 2, 0, 2, 0, 2, 0, 1 },
	{ 0, 0, 1, 0, 2, 1, 1, 0, 0, 1 },
	{ 1, 1, 1, 0, 2, 0, 1, 0, 1, 1 },
	{ 1, 4, 4, 4, 4, 4, 0, 0, 1, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
};

int map_3[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 0, 0},
	{1, 0, 0, 4, 2, 0, 1, 1, 1},
	{1, 0, 4, 2, 4, 2, 0, 0, 1},
	{1, 5, 2, 4, 2, 4, 3, 0, 1},
	{1, 0, 4, 2, 4, 2, 0, 1, 1},
	{1, 0, 0, 4, 2, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 0},
};
int finish();
void render();
void find();
void setmap(int n);
void color(int m);
void move(int x1, int y1, int x2, int y2);

void menu_one()
{
	printf("***************  推箱子游戏  ****************\n"
		"*                                           *\n"
		"*                  >请选择<                 *\n"
		"*                 1.开始游戏                *\n"
		"*                 2.游戏说明                *\n"
		"*                 0.退出游戏                *\n"
		"*                                           *\n"
		"*********************************************\n");
}
void menu_two()
{

	printf("***************   游戏规则   ****************\n"
		"*                                           *\n"
		"*     控制♀将■推到☆的位置，按 wasd 控制♀*\n"
		"*的移动,按 r 重新开始游戏,按 g 退出游戏.    *\n"
		"*                                           *\n"
		"*                                           *\n"
		"*                                           *\n"
		"*            按任意键返回主菜单.            *\n"
		"*                                           *\n"
		"*********************************************\n");
}
int main(void)
{
	int option = 0;
	char dir;
	system("mode con cols=50 lines=20");
	while (1)
	{
		system("cls");
		menu_one();
		scanf("%d", &option);
		getchar();
		if (0 == option)
		{
			return 0;
		}
		if (2 == option)
		{
			system("cls");
			menu_two();
			getch();
			continue;
		}
		if (1 == option)
		{
			while (1)
			{
				system("cls");
				setmap(option);
				render();
				while ((dir = getch()) != EOF)
				{
					system("cls");
					find();
					switch (dir)
					{
					case 'w':
						move(x - 1, y, x - 2, y);
						break;
					case 's':
						move(x + 1, y, x + 2, y);
						break;
					case 'a':
						move(x, y - 1, x, y - 2);
						break;
					case 'd':
						move(x, y + 1, x, y + 2);
						break;
					case 'q':
						return 0;
						break;
					case 'g':
						setmap(option);
						break;
					default:
						break;
					}
					render();
					if (finish()){
						if (option == 3)
						{
							printf("恭喜通关！\n");
							getch();
							return 0;
						}
						printf("胜利！按任意键进入下一关！\n");
						getch();
						option++;
						break;
					}
				}
			}
		}
		else
		{
			printf("输入错误，请重新选择！\n");
		}
	}
	system("pause");
	return 0;
}

void setmap(int n)
{
	switch (n)
	{
	case 1:memcpy(map, map_1, sizeof(map_1)); break;	
	case 2:memcpy(map, map_2, sizeof(map_2)); break;
	case 3:memcpy(map, map_3, sizeof(map_3)); break;
	default:
		break;
	}
}
void render()
{
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			switch (map[x][y])
			{
			case 0:
				color(0xF);
				printf("  ");
				break;
			case 1:
				color(8);//灰色
				printf("■");//砖块
				break;
			case 2:
				color(6);//淡黄色
				printf("■");//箱子
				break;
			case 3:
				color(0xC);//红色
				printf("♀");
				break;
			case 4:
				color(6);//黄色
				printf("☆");
				break;
			case 5:
				color(6);//黄色
				printf("★");
				break;
			case 6:
				color(0xC);
				printf("♀");
				break;
			}
		}
		printf("\n");
	}
}

void find()
{
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			if (map[x][y] == 3 || map[x][y] == 6)
			{
				return;
			}
		}
	}
}
void move(int x1, int y1, int x2, int y2)//一共考虑12种情况
{
	if (map[x][y] == 3)//小人处在空白位置
	{
		if (map[x1][y1] == 0)
		{
			map[x1][y1] = 3;
			map[x][y] = 0;
		}
		else if (map[x1][y1] == 4)
		{
			map[x1][y1] = 6;
			map[x][y] = 0;
		}
		else if (map[x1][y1] == 2)
		{
			if (map[x2][y2] == 0)
			{
				map[x2][y2] = 2;
				map[x1][y1] = 3;
				map[x][y] = 0;
			}
			else if (map[x2][y2] == 4)
			{
				map[x2][y2] = 5;
				map[x1][y1] = 3;
				map[x][y] = 0;
			}
		}
		else if (map[x1][y1] == 5)
		{
			if (map[x2][y2] == 4)
			{
				map[x2][y2] = 5;
				map[x1][y1] = 6;
				map[x][y] = 0;
			}
			else if (map[x2][y2] == 0)
			{
				map[x2][y2] = 2;
				map[x1][y1] = 6;
				map[x][y] = 0;
			}
		}

	}
	else if (map[x][y] == 6)//小人处在目标位置
	{
		if (map[x1][y1] == 0)
		{
			map[x1][y1] = 3;
			map[x][y] = 4;
		}
		else if (map[x1][y1] == 4)
		{
			map[x1][y1] = 6;
			map[x][y] = 4;
		}
		else if (map[x1][y1] == 2)
		{
			if (map[x2][y2] == 0)
			{
				map[x2][y2] = 2;
				map[x1][y1] = 3;
				map[x][y] = 4;
			}
			else if (map[x2][y2] == 4)
			{
				map[x2][y2] = 5;
				map[x1][y1] = 3;
				map[x][y] = 4;
			}
		}
		else if (map[x1][y1] == 5)
		{
			if (map[x2][y2] == 0)
			{
				map[x2][y2] = 2;
				map[x1][y1] = 6;
				map[x][y] = 4;
			}
			else if (map[x2][y2] == 4)
			{
				map[x2][y2] = 5;
				map[x1][y1] = 6;
				map[x][y] = 4;
			}
		}
	}
}
int finish()
{
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 10; y++)
		{
			if (map[x][y] == 4)
				return 0;
		}
	}
	return 1;
}
void color(int m)
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, m);
}