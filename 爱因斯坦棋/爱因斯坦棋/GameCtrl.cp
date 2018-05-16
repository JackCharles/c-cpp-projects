#include "GameCtrl.h"
#include "stdio.h"

//构造函数，主要赋初值，初始化指针等操作
GameCtrl::GameCtrl() :vtr(6)
{
	turn = -2;
	m_hInstance = NULL;
	m_hwnd = NULL;
	hChessMap = NULL;
	hBackground = NULL;
	for(int i=0;i<6;i++)
	{
		hDice[i] = NULL;
	}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			map[i][j] = -1;//-1表示无棋子
	for (int i = 0; i < 6; i++)//初始化向量
		vtr[i] = i;
	SelectID = -1;
	nRand = 1;
	nRedLeftCount = 6;
	nBlueLeftCount = 6;
	nRedOddCount = 3;
	nRedEvenCount = 3;
	nBlueEvenCount = 3;
	nBlueOddCount = 3;
	CanFullClip = true;
}

//显示或更新图像
void GameCtrl::OnPaint()
{
	//此处采用兼容性DC防止窗口移动时图像闪动
	HDC hdc = GetDC(m_hwnd);//获取设备DC
	HDC hMemDC1 = CreateCompatibleDC(hdc);//创建一级内存DC

	hBackground = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP14));
	SelectObject(hMemDC1, hBackground);//为一级内存DC绑定一张位图(选为背景)，然后再往上贴图(棋盘和棋子)
	DeleteObject(hBackground);//删除此对象,因为SelectObject中的object不可重复,因此每次执行PAINT都要重新加载

	this->ShowChessMap(hMemDC1);
	this->ShowSelected(hMemDC1);
	this->ShowChessMan(hMemDC1);
	this->ShowDice(hMemDC1);

	//调试信息
	char m[15] = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (map[i][j] > 5)
				sprintf_s(m, "%d %d=%2d flag:%d", i, j, map[i][j], Red[map[i][j] - 6].flag);
			else if (map[i][j] > -1 && map[i][j] < 6)
				sprintf_s(m, "%d %d=%2d flag:%d", i, j, map[i][j], Red[map[i][j]].flag);
			else
				sprintf_s(m, "%d %d=%2d", i, j, map[i][j]);

			//TextOut(hMemDC1, 0, 16 * (i * 5 + j) + 16, m, 13);
		}
	}


	BitBlt(hdc, 0, 0, 700, 500, hMemDC1, 0, 0, SRCCOPY);//最后把一级内存DC作为一张图片一次性贴上屏幕
	DeleteDC(hMemDC1);
	DeleteDC(hdc);
}

//定时器处理，任意一方用时超过四分钟判为输（目前没有处理）
void GameCtrl::OnTimer(UINT nTimerID)
{
}

//处理鼠标按下消息
void GameCtrl::OnLButtonDown(POINT pt)
{
	if(pt.x > 26 && pt.x < 168 && pt.y>132 && pt.y < 190)
	{
		if (turn != -2)
		{
			MessageBox(m_hwnd, "棋局尚未初始化或正在进行中,\n请点击Reset进行棋盘重置！"
				, "提示", MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			int x = MessageBox(m_hwnd, "要先手走棋吗?", "选择", MB_YESNO|MB_ICONQUESTION);
			if (x == IDYES)
			{
				turn = 1;
			}
			else
			{
				turn = 0;
			}
			GetRandom();
		}
	}

	if (pt.x > 26 && pt.x < 168 && pt.y>323 && pt.y < 384)
	{
		ResetGame();
		turn = -2;
	}

	if (turn == 1)
	{
		if (CanSelect(pt))
		{
			OnPaint();
		}

		else
		{
			if (CanPlace(pt))
			{
				PlaceChessman(pt);
				SelectID = -1;
				OnPaint();
				turn = 0;

				if (WinTheGame())
				{
					turn = -1;
				}
				GetRandom();
			}
		}
	}

	if(turn == 0)
	{
		Sleep(1000);
		bool flag = ComputerTurn();
		if (!flag)//调试
			MessageBox(m_hwnd, "Computer missed this step!!!", "Error", MB_OK | MB_ICONERROR);
		OnPaint();
		turn = 1;
		if (WinTheGame())
		{
			turn = -1;
		}
		GetRandom();
	}
}

//初始化游戏数据
void GameCtrl::InitGameDate()
{
	hChessMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP13));//加载棋盘
	//初始化红方棋子
	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//产生1-6的随机序列
	int k = 0;//临时变量，遍历棋子和向量
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 - i; j++)
		{
			Red[vtr[k]].flag = true;
			Red[vtr[k]].hChessBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + vtr[k]));
			Red[vtr[k]].num = vtr[k] + 1;//遍历初始的在左上角6个位置，每个位置随机选一枚棋放置
			Red[vtr[k]].type = 0;
			Red[vtr[k]].x = 200 + 100 * j + 5;
			Red[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k] + 6;//记录棋子
			k++;
		}
	}

	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//再次产生1-6的随机序列
	k = 0;
	for (int i = 2; i < 5; i++)
	{
		for (int j = 6 - i; j < 5; j++)
		{
			Blue[vtr[k]].flag = true;
			Blue[vtr[k]].hChessBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP7 + vtr[k]));
			Blue[vtr[k]].num = vtr[k] + 1;//遍历初始的在左上角6个位置，每个位置随机选一枚棋放置
			Blue[vtr[k]].type = 1;
			Blue[vtr[k]].x = 200 + 100 * j + 5;
			Blue[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k];
			k++;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		hDice[i] = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP16 + i));
	}
}

//设置句柄数据
void GameCtrl::SetDataValue(HINSTANCE hInst, HWND hwnd)
{
	m_hInstance = hInst;
	m_hwnd = hwnd;
}

//显示棋盘
void GameCtrl::ShowChessMap(HDC hMemDC1)
{
	//创建二级DC
	HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
	SelectObject(hMemDC2, hChessMap);
	BitBlt(hMemDC1, 200, 0, 500, 500, hMemDC2, 0, 0, SRCCOPY);
	DeleteDC(hMemDC2);
}

//显示棋子
void GameCtrl::ShowChessMan(HDC hMemDC1)
{
	for (int i = 0; i < 6; i++)
	{
		if (Red[i].flag == true)
		{
			HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
			SelectObject(hMemDC2, Red[i].hChessBitmap);
			BitBlt(hMemDC1, Red[i].x, Red[i].y, 90, 90, hMemDC2, 0, 0, SRCCOPY);
			DeleteDC(hMemDC2);
		}
		if (Blue[i].flag == true)
		{
			HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
			SelectObject(hMemDC2, Blue[i].hChessBitmap);
			BitBlt(hMemDC1, Blue[i].x, Blue[i].y, 90, 90, hMemDC2, 0, 0, SRCCOPY);
			DeleteDC(hMemDC2);
		}
	}
}

//获取随机数
void GameCtrl::GetRandom()
{
	if (turn == -1)
		return;
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		nRand = rand() % 6 + 1;
		OnPaint();
		Sleep(100);

	}
}

void GameCtrl::ShowDice(HDC hMemDC1)
{
	HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
	SelectObject(hMemDC2, hDice[nRand - 1]);
	BitBlt(hMemDC1, 20, 20, 75, 75, hMemDC2, 0, 0, SRCCOPY);
	DeleteDC(hMemDC2);

}

//是否可选中
bool GameCtrl::CanSelect(POINT pt)
{
	if (SelectID != -1)
	{
		return false;
	}
	if (pt.x > 200)//粗略范围
	{
		int index_x = (pt.x - 200) / 100;
		int index_y = pt.y / 100;

		if (pt.x > index_x * 100 + 205 && pt.x<index_x * 100 + 295 &&
			pt.y>index_y * 100 + 5 && pt.y < index_y * 100 + 95)//精确范围
		{
			if (map[index_y][index_x] >= 0 && map[index_y][index_x] <= 5)//选定我方棋子
			{

				if (Blue[map[index_y][index_x]].num == nRand)
				{
					SelectID = map[index_y][index_x];
					map[index_y][index_x] = -1;
					return true;
				}
				else
				{

					int min, max;//离随机数最近的两个棋子编号

					for (min = nRand - 1; Blue[min].flag == false && min > 0; min--);
					for (max = nRand - 1; Blue[max].flag == false && max < 5; max++);

					if (map[index_y][index_x] == min || map[index_y][index_x] == max)
					{
						SelectID = map[index_y][index_x];
						map[index_y][index_x] = -1;
						return true;
					}
				}
			}
		}
	}
	return false;
}

//是否可放置
bool GameCtrl::CanPlace(POINT pt)
{
	if (SelectID > -1)
	{
		if ((pt.x >= Blue[SelectID].x&&pt.x <= Blue[SelectID].x + 90 && pt.y <= Blue[SelectID].y - 10 && pt.y >= Blue[SelectID].y - 100) ||
			(pt.x >= Blue[SelectID].x - 100 && pt.x <= Blue[SelectID].x - 10 && pt.y <= Blue[SelectID].y - 10 && pt.y >= Blue[SelectID].y - 100) ||
			(pt.x >= Blue[SelectID].x - 100 && pt.x <= Blue[SelectID].x - 10 && pt.y <= Blue[SelectID].y + 90 && pt.y >= Blue[SelectID].y))//上，左上，左
		{
			return true;
		}
	}
	return false;
}

//显示选中框
void GameCtrl::ShowSelected(HDC hMemDC1)
{
	//图像显示选定
	if (SelectID > -1)
	{
		HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
		HBITMAP hBound = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP15));
		SelectObject(hMemDC2, hBound);
		BitBlt(hMemDC1, Blue[SelectID].x - 5, Blue[SelectID].y - 5, 100, 100, hMemDC2, 0, 0, SRCCOPY);
		DeleteDC(hMemDC2);
	}
}

//放置棋子
void GameCtrl::PlaceChessman(POINT pt)
{
	if (pt.x > 200)//粗略范围
	{
		int index_x = (pt.x - 200) / 100;
		int index_y = pt.y / 100;
		int sindex_x = (Blue[SelectID].x - 200) / 100;
		int sindex_y = Blue[SelectID].y / 100;

		if (map[index_y][index_x] == -1)
		{
			Blue[SelectID].x = index_x * 100 + 205;
			Blue[SelectID].y = index_y * 100 + 5;
			map[index_y][index_x] = Blue[SelectID].num - 1;
			map[sindex_y][sindex_x] = -1;
		}
		else
		{

			if (map[index_y][index_x] < 6)//has a blue one
			{
				Blue[map[index_y][index_x]].flag = false;
				nBlueLeftCount--;
				if (Blue[map[index_y][index_x]].num % 2 == 0)
				{
					nBlueEvenCount--;
				}
				else
				{
					nBlueOddCount--;
				}
				Blue[SelectID].x = index_x * 100 + 205;
				Blue[SelectID].y = index_y * 100 + 5;
				map[index_y][index_x] = Blue[SelectID].num - 1;
				map[sindex_y][sindex_x] = -1;
			}
			else// has a red one
			{
				Red[map[index_y][index_x] - 6].flag = false;
				nRedLeftCount--;
				if (Red[map[index_y][index_x] - 6].num % 2 == 0)
				{
					nRedEvenCount--;//偶数--
				}
				else
				{
					nRedOddCount--;
				}
				Blue[SelectID].x = index_x * 100 + 205;
				Blue[SelectID].y = index_y * 100 + 5;
				map[index_y][index_x] = Blue[SelectID].num - 1;
				map[sindex_y][sindex_x] = -1;
			}
		}
	}
}

//判断输赢
bool GameCtrl::WinTheGame()
{
	if (map[0][0] < 6 && map[0][0] != -1)
	{
		MessageBox(m_hwnd, "恭喜你，你赢了", "你赢了", 0);
		return true;
	}
	if (map[4][4] > 5)
	{
		MessageBox(m_hwnd, "很遗憾，你输了", "你输了", 0);
		return true;
	}
	bool redOver = true;
	bool blueOver = true;
	for (int i = 0; i < 6; i++)
	{
		if (Red[i].flag == true)
		{
			redOver = false;
		}
		if (Blue[i].flag == true)
		{
			blueOver = false;
		}
	}
	if (redOver)
	{
		MessageBox(m_hwnd, "恭喜你，你赢了", "你赢了", 0);
		return true;
	}
	if (blueOver)
	{
		MessageBox(m_hwnd, "很遗憾，你输了", "你输了", 0);
		return true;
	}
	return false;
}

//重新开始
void GameCtrl::ResetGame()
{
	//重置数据
	nRedLeftCount = 6;
	nRedOddCount = 3;
	nRedEvenCount = 3;
	nBlueLeftCount = 6;
	nBlueEvenCount = 3;
	nBlueOddCount = 3;
	SelectID = -1;
	CanFullClip = true;
	//重置棋盘
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			map[i][j] = -1;//-1表示无棋子
	//重置红方棋子
	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//产生1-6的随机序列
	int k = 0;//临时变量，遍历棋子和向量
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 - i; j++)
		{
			Red[vtr[k]].flag = true;
			Red[vtr[k]].x = 200 + 100 * j + 5;
			Red[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k] + 6;//记录棋子
			k++;
		}
	}

	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//再次产生1-6的随机序列
	k = 0;
	for (int i = 2; i < 5; i++)
	{
		for (int j = 6 - i; j < 5; j++)
		{
			Blue[vtr[k]].flag = true;
			Blue[vtr[k]].x = 200 + 100 * j + 5;
			Blue[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k];
			k++;
		}
	}
	OnPaint();
}

////////////////////////////////////////////////////////////////////////////////////////////
//开局
void GameCtrl::StartGame(int num)//num传入选定棋子的下标
{
	//找到选择的棋子或靠近的棋子
	if (Red[num].flag == false)
	{
		num = IsExist(num);
	}
	//找到选择的棋子在地图上索引
	int index_x = (Red[num].x - 200) / 100;
	int index_y = Red[num].y / 100;
	//判断是否地图越界并进行移动
	if (index_x < 4 && index_y < 4)
	{
		int rd = map[index_x + 1][index_y + 1];//右下方位置的棋子
		int down = map[index_x][index_y + 1];//下方位置的棋子
		int right = map[index_x + 1][index_y];//右方位置的棋子

		if (nRedEvenCount >= nRedOddCount)//偶数个数 >= 奇数个数，吃掉奇数
		{
			//如果右下方有己方奇数棋子，吃掉
			if ((rd >= 6) && (Red[rd - 6].num % 2 == 1))
			{
				EatRightDown(index_x, index_y, num, rd);
				nRedOddCount--;//奇数棋子数--
			}
			//如果下方有己方奇数棋子，吃掉
			else if ((down >= 6) && (Red[down - 6].num % 2 == 1))
			{
				EatDown(index_x, index_y, num, down);
				nRedOddCount--;//奇数棋子数--
			}
			//如果右方有己方奇数棋子，吃掉
			else if ((right >= 6) && (Red[right - 6].num % 2 == 1))
			{
				EatRight(index_x, index_y, num, right);
				nRedOddCount--;//奇数棋子数--
			}
			//如果右下方为空，移动至右下方
			else if (rd == -1)
			{
				RightDownEmpty(index_x, index_y, num);
			}
			//如果下方为空，移动至下方
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
			//如果右方为空，移动至右方
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
		else//奇数个数 >= 偶数个数，吃掉偶数
		{
			//如果右下方有己方偶数棋子，吃掉
			if ((rd >= 6) && (Red[rd - 6].num % 2 == 0))
			{
				EatRightDown(index_x, index_y, num, rd);
				nRedEvenCount--;//偶数棋子数--
			}
			//如果下方有己方偶数棋子，吃掉
			else if ((down >= 6) && (Red[down - 6].num % 2 == 0))
			{
				EatDown(index_x, index_y, num, down);
				nRedEvenCount--;//偶数棋子数--
			}
			//如果右方有己方偶数棋子，吃掉
			else if ((right >= 6) && (Red[right - 6].num % 2 == 0))
			{
				EatRight(index_x, index_y, num, right);
				nRedEvenCount--;//偶数棋子数--
			}
			//如果右下方为空，移动至右下方
			else if (rd == -1)
			{
				RightDownEmpty(index_x, index_y, num);
			}
			//如果下方为空，移动至下方
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
			//如果右方为空，移动至右方
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
	}
	else if (index_x == 4 && index_y < 4)
	{
		int down = map[index_x][index_y + 1];//下方位置的棋子
		if (nRedEvenCount >= nRedOddCount)//偶数个数 >= 奇数个数，吃掉奇数
		{
			//如果下方有己方奇数棋子，吃掉
			if ((down >= 6) && (Red[down - 6].num % 2 == 1))
			{
				EatDown(index_x, index_y, num, down);
				nRedOddCount--;//奇数棋子数--
			}
			//如果下方为空，移动至下方
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
		}
		else//奇数个数 >= 偶数个数，吃掉偶数
		{
			//如果下方有己方偶数棋子，吃掉
			if ((down >= 6) && (Red[down - 6].num % 2 == 0))
			{
				EatDown(index_x, index_y, num, down);
				nRedEvenCount--;//偶数棋子数--
			}
			//如果下方为空，移动至下方
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
		}
	}
	else if (index_x < 4 && index_y == 4)
	{
		int right = map[index_x + 1][index_y];//右方位置的棋子
		if (nRedEvenCount >= nRedOddCount)//偶数个数 >= 奇数个数，吃掉奇数
		{
			//如果右方有己方奇数棋子，吃掉
			if ((right >= 6) && (Red[right - 6].num % 2 == 1))
			{
				EatRight(index_x, index_y, num, right);
				nRedOddCount--;//奇数棋子数--
			}
			//如果右方为空，移动至右方
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
		else//奇数个数 >= 偶数个数，吃掉偶数
		{
			//如果右方有己方偶数棋子，吃掉
			if ((right >= 6) && (Red[right - 6].num % 2 == 0))
			{
				EatRight(index_x, index_y, num, right);
				nRedEvenCount--;//偶数棋子数--
			}
			//如果右方为空，移动至右方
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
	}
}

//检查棋子是否存在，并找出靠近且存在的棋子
int GameCtrl::IsExist(int num)
{
	int m, n;//上下检索存在的棋子m, n
	for (m = num; Red[m].flag == false && m > 0; m--);
	for (n = num; Red[n].flag == false && n < 5; n++);
	int index_mx = (Red[m].x - 200) / 100;//找到随机数对应的坐标
	int index_my = Red[m].y / 100;
	int index_nx = (Red[n].x - 200) / 100;//找到随机数对应的坐标
	int index_ny = Red[n].y / 100;

	bool fm = true, fn = true;
	if ((m == 0 || m == 5) && Red[m].flag == false)
	{
		fm = false;
	}
	if ((n == 0 || n == 5) && Red[n].flag == false)
	{
		fn = false;
	}
	if (fm) return m;
	else return n;
}
//吃掉右下方己方棋子
void GameCtrl::EatRightDown(int index_x, int index_y, int num, int rd)
{
	Red[rd - 6].flag = false;//被吃掉的棋子从棋盘消失
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x + 1][index_y + 1] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].x = (index_x + 1) * 100 + 205;
	Red[num].y = (index_y + 1) * 100 + 5;//更新棋子的坐标
	nRedLeftCount--; //己方棋子数--
}
//吃掉下方己方棋子
void GameCtrl::EatDown(int index_x, int index_y, int num, int down)
{
	Red[down - 6].flag = false;//被吃掉的棋子从棋盘消失
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x][index_y + 1] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].y = (index_y + 1) * 100 + 5; //更新棋子的坐标
	nRedLeftCount--; //己方棋子数--
}
//吃掉右方己方棋子
void GameCtrl::EatRight(int index_x, int index_y, int num, int right)
{
	Red[right - 6].flag = false;//被吃掉的棋子从棋盘消失
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x + 1][index_y] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].x = (index_x + 1) * 100 + 205; //更新棋子的坐标
	nRedLeftCount--; //己方棋子数--
}
//右下方为空，棋子移动至右下方
void GameCtrl::RightDownEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x + 1][index_y + 1] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].x = (index_x + 1) * 100 + 205;
	Red[num].y = (index_y + 1) * 100 + 5;//更新棋子的坐标
}
//下方为空，棋子移动至下方
void GameCtrl::DownEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x][index_y + 1] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].y = (index_y + 1) * 100 + 5; //更新棋子的坐标
}
//右方为空，棋子移动至右方
void GameCtrl::RightEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//将移动的棋子从棋盘旧位置移开
	map[index_x + 1][index_y] = Red[num].num + 6-1;//将移动的棋子放置在棋盘新位置
	Red[num].x = (index_x + 1) * 100 + 205; //更新棋子的坐标
}

/////////////////////////////////////////////////////////////////////////////////////////////
void GameCtrl::IsFullClip()
{
	if (CanFullClip == true)//如果上次我方具有全歼能力，判断这一次
	{
		for (int i = 0; i < 6; i++)//blue
		{
			if (Blue[i].flag == true)//棋子存在
			{
				bool flag = false;//假设我方失去全歼能力
				for (int j = 0; j < 6; j++)//red
				{
					if (Red[j].flag == true)
						if (Blue[i].x > Red[j].x || Blue[i].y > Red[j].y)
						{
							flag = true;//对于敌方来说blue[i]未能到达我方后方，我方仍具有全歼能力
							break;
						}
				}

				if (!flag)
				{
					CanFullClip = false;
					break;
				}
			}//if
		}//for
	}//if
}

bool GameCtrl::ToDestWithOneStep(int index_x, int index_y, int num)
{
	if ((index_x + 1 == 4) && (index_y + 1 == 4))
	{
		if (map[4][4] == -1)
		{
			Red[num - 1].x = 605;
			Red[num - 1].y = 405;
			map[4][4] = num - 1 + 6;
		}
		else
		{
			KillEnemy(index_x, index_y, num, 2);
		}
		return true;
	}
	else if ((index_x + 1 == 4) && index_y == 4)
	{
		if (map[4][4] == -1)
		{
			Red[num - 1].x = 605;
			map[4][4] = num - 1 + 6;
		}
		else
		{
			KillEnemy(index_x, index_y, num, 3);
		}
		return true;
	}
	else if ((index_x == 4) && index_y + 1 == 4)
	{
		if (map[4][4] == -1)
		{
			Red[num - 1].y = 405;
			map[4][4] = num - 1 + 6;
		}
		else
		{
			KillEnemy(index_x, index_y, num, 1);
		}
		return true;
	}
	return false;
}

bool GameCtrl::FullClip(int index_x, int index_y, int num)
{
	if (nBlueLeftCount > 1)
	{
		return false;
	}
	else
	{
		if (index_x < 4 && index_y < 4)//选定的棋子在中间(不靠边)
		{
			if (map[index_y + 1][index_x + 1] > -1 && map[index_y + 1][index_x + 1] < 6)//敌人在右下方
			{
				KillEnemy(index_x, index_y, num, 2);
				return true;
			}
			else if (map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)//敌人在下方
			{
				KillEnemy(index_x, index_y, num, 1);
				return true;
			}
			else if (map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)//敌人在右方
			{
				KillEnemy(index_x, index_y, num, 3);
				return true;
			}
		}
		else if (index_x == 4 && map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)//选定棋子在最右边（敌人在下边）
		{
			KillEnemy(index_x, index_y, num, 1);
			return true;
		}
		else if (index_y == 4 && map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)//选定棋子在最下边（敌人在右边）
		{
			KillEnemy(index_x, index_y, num, 3);
			return true;
		}
		return false;
	}
}

void GameCtrl::KillEnemy(int index_x, int index_y, int num, int type)
{
	switch (type)
	{
		case 1://敌人在下方
		{
			Blue[map[index_y + 1][index_x]].flag = false;
			nBlueLeftCount--;
			if (Blue[map[index_y + 1][index_x]].num % 2 == 0)
				nBlueEvenCount--;
			else
				nBlueOddCount--;
			Red[num - 1].y = (index_y + 1) * 100 + 5;
			map[index_y][index_x] = -1;
			map[index_y + 1][index_x] = num - 1 + 6;
			break;
		}
		case 2://敌人右下方
		{
			Blue[map[index_y + 1][index_x + 1]].flag = false;
			nBlueLeftCount--;
			if (Blue[map[index_y + 1][index_x + 1]].num % 2 == 0)
				nBlueEvenCount--;
			else
				nBlueOddCount--;
			Red[num - 1].x = (index_x + 1) * 100 + 205;
			Red[num - 1].y = (index_y + 1) * 100 + 5;
			map[index_y][index_x] = -1;
			map[index_y + 1][index_x + 1] = num - 1 + 6;//+6对应红色棋子
			break;
		}
		case 3://敌人在右边
		{
			Blue[map[index_y][index_x + 1]].flag = false;
			nBlueLeftCount--;
			if (Blue[map[index_y][index_x + 1]].num % 2 == 0)
				nBlueEvenCount--;
			else
				nBlueOddCount--;
			Red[num - 1].x = (index_x + 1) * 100 + 205;
			map[index_y][index_x] = -1;
			map[index_y][index_x + 1] = num - 1 + 6;//+6对应红色棋子
			break;
		}
	}
}

bool GameCtrl::CanStartGame(int index_x, int index_y)
{
	if (nRedLeftCount > 3)
	{
		int temp = 0;//统计可走方向上自己棋子数0-3
		if (map[index_y][index_x + 1] > 5)
		{
			temp++;
		}
		if (map[index_y + 1][index_x + 1] > 5)
		{
			temp++;
		}
		if (map[index_y + 1][index_x] > 5)
		{
			temp++;
		}
		if (temp >= 2)
		{
			return true;
		}
	}
	return false;
}

bool GameCtrl::NormalMove(int index_x, int index_y, int num)
{

	//满足主动吃掉对方棋子情况
	//a.吃掉有威胁的棋子
	if (((index_y == 0 && index_x == 0) || (index_y == 0 && index_x == 1)) &&//下边敌方棋子一步威胁
		map[index_y + 1][index_x]<6 && map[index_y + 1][index_x]>-1)
	{
		KillEnemy(index_x, index_y, num, 1);
		return true;
	}
	else if ((index_y == 0 && index_x == 0) &&		//斜对角敌方棋子一步威胁
		map[index_y + 1][index_x + 1]<6 && map[index_y + 1][index_x + 1]>-1)
	{
		KillEnemy(index_x, index_y, num, 2);
		return true;
	}
	else if (((index_y == 0 && index_x == 0) || (index_y == 1 && index_x == 0)) && //右边敌方棋子一步威胁
		map[index_y][index_x + 1]<6 && map[index_y][index_x + 1]>-1)
	{
		KillEnemy(index_x, index_y, num, 3);
		return true;
	}

	//被包围
	else if ((index_x < 4 && index_y < 4) && (map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6) &&
		(map[index_y + 1][index_x + 1] > -1 && map[index_y][index_x + 1] < 6) &&
		(map[index_y + 1][index_x] > -1 && map[index_y][index_x + 1] < 6))
	{
		if ((nBlueEvenCount > nBlueOddCount && Blue[map[index_y + 1][index_x]].num % 2 == 0) ||
			(nBlueEvenCount < nBlueOddCount && Blue[map[index_y + 1][index_x]].num % 2 != 0))
		{
			KillEnemy(index_x, index_y, num, 1);
			return true;
		}
		else if ((nBlueEvenCount > nBlueOddCount && Blue[map[index_y][index_x + 1]].num % 2 == 0) ||
			(nBlueEvenCount < nBlueOddCount && Blue[map[index_y][index_x + 1]].num % 2 != 0))
		{
			KillEnemy(index_x, index_y, num, 3);
			return true;
		}
		else
		{
			KillEnemy(index_x, index_y, num, 2);
			return true;
		}
	}

	else
	{
		//int 三个或两个方向可走，结合避开我方棋子和静态防守策略选择;
		if (index_x < 4 && index_y < 4)
		{
			int d = 0, r = 0, rd = 0;
			int *temp;//to be honest, it's very ridiculous...
			int EnemyCount = ScanEnemy(index_x, index_y, &d, &r, &rd);
			if (EnemyCount > 0)//周围有敌人 kill
			{
				if (rd == 1)
				{
					KillEnemy(index_x, index_y, num, 2);
					return true;
				}
				if (d == 1)
				{
					KillEnemy(index_x, index_y, num, 1);
					return true;
				}
				if (r == 1)
				{
					KillEnemy(index_x, index_y, num, 3);
					return true;
				}
			}
			else
			{
				if (map[index_y + 1][index_x + 1] == -1)//rightdown
				{
					Red[num - 1].x = (index_x + 1) * 100 + 205;
					Red[num - 1].y = (index_y + 1) * 100 + 5;
					map[index_y][index_x] = -1;
					map[index_y + 1][index_x + 1] = num - 1 + 6;
					return true;
				}
				else if (map[index_y + 1][index_x] == -1)//down
				{
					Red[num - 1].x = index_x * 100 + 205;
					Red[num - 1].y = (index_y + 1) * 100 + 5;
					map[index_y][index_x] = -1;
					map[index_y + 1][index_x] = num - 1 + 6;
					return true;
				}
				else//right
				{
					Red[num - 1].x = (index_x + 1) * 100 + 205;
					Red[num - 1].y = index_y * 100 + 5;
					map[index_y][index_x] = -1;
					map[index_y][index_x + 1] = num - 1 + 6;
					return true;
				}
			}//保底else
		}
		else if (index_x < 4 && index_y == 4)
		{
			if (map[index_y][index_x + 1] == -1)
			{
				Red[num - 1].x = (index_x + 1) * 100 + 205;
				Red[num - 1].y = index_y * 100 + 5;
				map[index_y][index_x] = -1;
				map[index_y][index_x + 1] = num - 1 + 6;
				return true;
			}
			else if(map[index_y][index_x + 1]<6)
			{
				KillEnemy(index_x, index_y, num, 3);
				return true;
			}
			else
			{
				Red[map[index_y][index_x + 1] - 6].flag = false;
				nRedLeftCount--;
				if (Red[map[index_y][index_x + 1] - 6].num % 2 == 0)
					nRedEvenCount--;
				else
					nRedOddCount--;
				Red[num - 1].x = (index_x + 1) * 100 + 205;
				Red[num - 1].y = index_y * 100 + 5;
				map[index_y][index_x] = -1;
				map[index_y][index_x + 1] = num - 1 + 6;
				return true;
			}
		}
		else
		{
			if (map[index_y + 1][index_x] == -1)
			{
				Red[num - 1].x = index_x * 100 + 205;
				Red[num - 1].y = (index_y + 1) * 100 + 5;
				map[index_y][index_x] = -1;
				map[index_y + 1][index_x] = num - 1 + 6;
				return true;
			}
			else if (map[index_y + 1][index_x] < 6)
			{
				KillEnemy(index_x, index_y, num, 1);
				return true;
			}
			else
			{
				Red[map[index_y + 1][index_x] - 6].flag = false;
				nRedLeftCount--;
				if (Red[map[index_y + 1][index_x] - 6].num % 2 == 0)
					nRedEvenCount--;
				else
					nRedOddCount--;
				Red[num - 1].x = index_x * 100 + 205;
				Red[num - 1].y = (index_y + 1) * 100 + 5;
				map[index_y][index_x] = -1;
				map[index_y + 1][index_x] = num - 1 + 6;
				return true;
			}
		}
	}
	return false;
}

//扫描给定坐标周围的敌人,并返回其位置，初始时d,r,dr都为0表示无敌人
int GameCtrl::ScanEnemy(int index_x, int index_y, int* down, int* right, int* rightDown)
{
	if (index_x == 4 && index_y == 4)
	{
		return 0;
	}
	else if (index_x < 4 && index_y == 4)
	{
		if (map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)
		{
			*right = 1;
			return 1;
		}
		else
			return 0;
	}
	else if (index_x == 4 && index_y < 4)
	{
		if (map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)
		{
			*down = 1;
			return 1;
		}
		else
			return 0;
	}
	else
	{
		int enemyCount = 0;
		if (map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)
		{
			*down = 1;
			enemyCount++;
		}
		if (map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)
		{
			*right = 1;
			enemyCount++;
		}
		if (map[index_y + 1][index_x + 1] > -1 && map[index_y + 1][index_x + 1] < 6)
		{
			*rightDown = 1;
			enemyCount++;
		}
		return enemyCount;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool GameCtrl::ComputerTurn()
{
	IsFullClip();//更新CanFullClip状态

	if (CanFullClip == true)//正式走棋具有全歼能力
	{
		if (Red[nRand - 1].flag == true)//选中的棋子存在
		{
			int index_x = (Red[nRand - 1].x - 200) / 100;//找到随机数对应的坐标
			int index_y = Red[nRand - 1].y / 100;
			//走一步到终点
			if (ToDestWithOneStep(index_x, index_y, nRand))
			{
				return true;
			}
			//团灭
			else if (FullClip(index_x, index_y, nRand))
			{
				return true;
			}
			//满足开局情况
			else if (CanStartGame(index_x, index_y))//己方棋子数>3且周围可走向至少两个是己方棋子，条件可更改
			{
				StartGame(nRand - 1);
				return true;
			}
			//一般情况
			else
			{
				return NormalMove(index_x, index_y, nRand);
			}
		}
		/*------------------------------------------------------*/
		else //选择的棋子不存在
		{
			int m, n;//上下检索存在的棋子m, n
			for (m = nRand - 1; Red[m].flag == false && m > 0; m--);
			for (n = nRand - 1; Red[n].flag == false && n < 5; n++);

			int index_mx = (Red[m].x - 200) / 100;//找到随机数对应的坐标
			int index_my = Red[m].y / 100;
			int index_nx = (Red[n].x - 200) / 100;//找到随机数对应的坐标
			int index_ny = Red[n].y / 100;
			bool fm = true, fn = true;
			if ((m == 0 || m == 5) && Red[m].flag == false)
			{
				fm = false;
			}
			if ((n == 0 || n == 5) && Red[n].flag == false)
			{
				fn = false;
			}
			if (fm&&ToDestWithOneStep(index_mx, index_my, m + 1))
			{
				return true;
			}
			else if (fn&&ToDestWithOneStep(index_nx, index_ny, n + 1))
			{
				return true;
			}
			else if (fm&&FullClip(index_mx, index_my, m + 1))
			{
				return true;
			}
			else if (fn&&FullClip(index_nx, index_ny, n + 1))
			{
				return true;
			}
			else if (fm&&CanStartGame(index_mx, index_my))
			{
				StartGame(m);
				return true;
			}
			else if (fn&&CanStartGame(index_nx, index_ny))
			{
				StartGame(n);
				return true;
			}
			else
			{
				if (fm)
				{
					NormalMove(index_mx, index_my, m + 1);
					return true;
				}
				else
				{
					NormalMove(index_nx, index_ny, n + 1);
					return true;
				}
			}
		}
	}


	else //失去全歼能力
	{
		if (Red[nRand - 1].flag == true)//选中的棋子存在
		{
			int index_x = (Red[nRand - 1].x - 200) / 100;//找到随机数对应的坐标
			int index_y = Red[nRand - 1].y / 100;
			if (ToDestWithOneStep(index_x, index_y, nRand))
			{
				return true;
			}
			else if (CanStartGame(index_x, index_y))//己方棋子数>3且周围可走向至少两个是己方棋子，条件可更改
			{
				StartGame(nRand - 1);
				return true;
			}
			else
			{
				return NormalMove(index_x, index_y, nRand);
			}
		}
		else
		{
			int m, n;//上下检索存在的棋子m, n
			for (m = nRand - 1; Red[m].flag == false && m > 0; m--);
			for (n = nRand - 1; Red[n].flag == false && n < 5; n++);
			int index_mx = (Red[m].x - 200) / 100;//找到随机数对应的坐标
			int index_my = Red[m].y / 100;
			int index_nx = (Red[n].x - 200) / 100;//找到随机数对应的坐标
			int index_ny = Red[n].y / 100;

			bool fm = true, fn = true;
			if ((m == 0 || m == 5) && Red[m].flag == false)
			{
				fm = false;
			}
			if ((n == 0 || n == 5) && Red[n].flag == false)
			{
				fn = false;
			}
			if (fm&&ToDestWithOneStep(index_mx, index_my, m + 1))
			{
				return true;
			}
			else if (fn&&ToDestWithOneStep(index_nx, index_ny, n + 1))
			{
				return true;
			}
			else if (fm&&CanStartGame(index_mx, index_my))
			{
				StartGame(m);
				return true;
			}
			else if (fn&&CanStartGame(index_nx, index_ny))
			{
				StartGame(n);
				return true;
			}
			else
			{
				if (fm)
				{
					NormalMove(index_mx, index_my, m + 1);
				}
				else
				{
					NormalMove(index_nx, index_ny, n + 1);
				}
				return true;
			}
		}
	}
	return false;
}

GameCtrl::~GameCtrl()
{

}
