#include "GameCtrl.h"
#include "stdio.h"

//���캯������Ҫ����ֵ����ʼ��ָ��Ȳ���
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
			map[i][j] = -1;//-1��ʾ������
	for (int i = 0; i < 6; i++)//��ʼ������
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

//��ʾ�����ͼ��
void GameCtrl::OnPaint()
{
	//�˴����ü�����DC��ֹ�����ƶ�ʱͼ������
	HDC hdc = GetDC(m_hwnd);//��ȡ�豸DC
	HDC hMemDC1 = CreateCompatibleDC(hdc);//����һ���ڴ�DC

	hBackground = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP14));
	SelectObject(hMemDC1, hBackground);//Ϊһ���ڴ�DC��һ��λͼ(ѡΪ����)��Ȼ����������ͼ(���̺�����)
	DeleteObject(hBackground);//ɾ���˶���,��ΪSelectObject�е�object�����ظ�,���ÿ��ִ��PAINT��Ҫ���¼���

	this->ShowChessMap(hMemDC1);
	this->ShowSelected(hMemDC1);
	this->ShowChessMan(hMemDC1);
	this->ShowDice(hMemDC1);

	//������Ϣ
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


	BitBlt(hdc, 0, 0, 700, 500, hMemDC1, 0, 0, SRCCOPY);//����һ���ڴ�DC��Ϊһ��ͼƬһ����������Ļ
	DeleteDC(hMemDC1);
	DeleteDC(hdc);
}

//��ʱ����������һ����ʱ�����ķ�����Ϊ�䣨Ŀǰû�д���
void GameCtrl::OnTimer(UINT nTimerID)
{
}

//������갴����Ϣ
void GameCtrl::OnLButtonDown(POINT pt)
{
	if(pt.x > 26 && pt.x < 168 && pt.y>132 && pt.y < 190)
	{
		if (turn != -2)
		{
			MessageBox(m_hwnd, "�����δ��ʼ�������ڽ�����,\n����Reset�����������ã�"
				, "��ʾ", MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			int x = MessageBox(m_hwnd, "Ҫ����������?", "ѡ��", MB_YESNO|MB_ICONQUESTION);
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
		if (!flag)//����
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

//��ʼ����Ϸ����
void GameCtrl::InitGameDate()
{
	hChessMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP13));//��������
	//��ʼ���췽����
	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//����1-6���������
	int k = 0;//��ʱ�������������Ӻ�����
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 - i; j++)
		{
			Red[vtr[k]].flag = true;
			Red[vtr[k]].hChessBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + vtr[k]));
			Red[vtr[k]].num = vtr[k] + 1;//������ʼ�������Ͻ�6��λ�ã�ÿ��λ�����ѡһö�����
			Red[vtr[k]].type = 0;
			Red[vtr[k]].x = 200 + 100 * j + 5;
			Red[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k] + 6;//��¼����
			k++;
		}
	}

	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//�ٴβ���1-6���������
	k = 0;
	for (int i = 2; i < 5; i++)
	{
		for (int j = 6 - i; j < 5; j++)
		{
			Blue[vtr[k]].flag = true;
			Blue[vtr[k]].hChessBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP7 + vtr[k]));
			Blue[vtr[k]].num = vtr[k] + 1;//������ʼ�������Ͻ�6��λ�ã�ÿ��λ�����ѡһö�����
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

//���þ������
void GameCtrl::SetDataValue(HINSTANCE hInst, HWND hwnd)
{
	m_hInstance = hInst;
	m_hwnd = hwnd;
}

//��ʾ����
void GameCtrl::ShowChessMap(HDC hMemDC1)
{
	//��������DC
	HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
	SelectObject(hMemDC2, hChessMap);
	BitBlt(hMemDC1, 200, 0, 500, 500, hMemDC2, 0, 0, SRCCOPY);
	DeleteDC(hMemDC2);
}

//��ʾ����
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

//��ȡ�����
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

//�Ƿ��ѡ��
bool GameCtrl::CanSelect(POINT pt)
{
	if (SelectID != -1)
	{
		return false;
	}
	if (pt.x > 200)//���Է�Χ
	{
		int index_x = (pt.x - 200) / 100;
		int index_y = pt.y / 100;

		if (pt.x > index_x * 100 + 205 && pt.x<index_x * 100 + 295 &&
			pt.y>index_y * 100 + 5 && pt.y < index_y * 100 + 95)//��ȷ��Χ
		{
			if (map[index_y][index_x] >= 0 && map[index_y][index_x] <= 5)//ѡ���ҷ�����
			{

				if (Blue[map[index_y][index_x]].num == nRand)
				{
					SelectID = map[index_y][index_x];
					map[index_y][index_x] = -1;
					return true;
				}
				else
				{

					int min, max;//�������������������ӱ��

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

//�Ƿ�ɷ���
bool GameCtrl::CanPlace(POINT pt)
{
	if (SelectID > -1)
	{
		if ((pt.x >= Blue[SelectID].x&&pt.x <= Blue[SelectID].x + 90 && pt.y <= Blue[SelectID].y - 10 && pt.y >= Blue[SelectID].y - 100) ||
			(pt.x >= Blue[SelectID].x - 100 && pt.x <= Blue[SelectID].x - 10 && pt.y <= Blue[SelectID].y - 10 && pt.y >= Blue[SelectID].y - 100) ||
			(pt.x >= Blue[SelectID].x - 100 && pt.x <= Blue[SelectID].x - 10 && pt.y <= Blue[SelectID].y + 90 && pt.y >= Blue[SelectID].y))//�ϣ����ϣ���
		{
			return true;
		}
	}
	return false;
}

//��ʾѡ�п�
void GameCtrl::ShowSelected(HDC hMemDC1)
{
	//ͼ����ʾѡ��
	if (SelectID > -1)
	{
		HDC hMemDC2 = CreateCompatibleDC(hMemDC1);
		HBITMAP hBound = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP15));
		SelectObject(hMemDC2, hBound);
		BitBlt(hMemDC1, Blue[SelectID].x - 5, Blue[SelectID].y - 5, 100, 100, hMemDC2, 0, 0, SRCCOPY);
		DeleteDC(hMemDC2);
	}
}

//��������
void GameCtrl::PlaceChessman(POINT pt)
{
	if (pt.x > 200)//���Է�Χ
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
					nRedEvenCount--;//ż��--
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

//�ж���Ӯ
bool GameCtrl::WinTheGame()
{
	if (map[0][0] < 6 && map[0][0] != -1)
	{
		MessageBox(m_hwnd, "��ϲ�㣬��Ӯ��", "��Ӯ��", 0);
		return true;
	}
	if (map[4][4] > 5)
	{
		MessageBox(m_hwnd, "���ź���������", "������", 0);
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
		MessageBox(m_hwnd, "��ϲ�㣬��Ӯ��", "��Ӯ��", 0);
		return true;
	}
	if (blueOver)
	{
		MessageBox(m_hwnd, "���ź���������", "������", 0);
		return true;
	}
	return false;
}

//���¿�ʼ
void GameCtrl::ResetGame()
{
	//��������
	nRedLeftCount = 6;
	nRedOddCount = 3;
	nRedEvenCount = 3;
	nBlueLeftCount = 6;
	nBlueEvenCount = 3;
	nBlueOddCount = 3;
	SelectID = -1;
	CanFullClip = true;
	//��������
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			map[i][j] = -1;//-1��ʾ������
	//���ú췽����
	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//����1-6���������
	int k = 0;//��ʱ�������������Ӻ�����
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 - i; j++)
		{
			Red[vtr[k]].flag = true;
			Red[vtr[k]].x = 200 + 100 * j + 5;
			Red[vtr[k]].y = 100 * i + 5;
			map[i][j] = vtr[k] + 6;//��¼����
			k++;
		}
	}

	srand(time(NULL));
	random_shuffle(vtr.begin(), vtr.end());//�ٴβ���1-6���������
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
//����
void GameCtrl::StartGame(int num)//num����ѡ�����ӵ��±�
{
	//�ҵ�ѡ������ӻ򿿽�������
	if (Red[num].flag == false)
	{
		num = IsExist(num);
	}
	//�ҵ�ѡ��������ڵ�ͼ������
	int index_x = (Red[num].x - 200) / 100;
	int index_y = Red[num].y / 100;
	//�ж��Ƿ��ͼԽ�粢�����ƶ�
	if (index_x < 4 && index_y < 4)
	{
		int rd = map[index_x + 1][index_y + 1];//���·�λ�õ�����
		int down = map[index_x][index_y + 1];//�·�λ�õ�����
		int right = map[index_x + 1][index_y];//�ҷ�λ�õ�����

		if (nRedEvenCount >= nRedOddCount)//ż������ >= �����������Ե�����
		{
			//������·��м����������ӣ��Ե�
			if ((rd >= 6) && (Red[rd - 6].num % 2 == 1))
			{
				EatRightDown(index_x, index_y, num, rd);
				nRedOddCount--;//����������--
			}
			//����·��м����������ӣ��Ե�
			else if ((down >= 6) && (Red[down - 6].num % 2 == 1))
			{
				EatDown(index_x, index_y, num, down);
				nRedOddCount--;//����������--
			}
			//����ҷ��м����������ӣ��Ե�
			else if ((right >= 6) && (Red[right - 6].num % 2 == 1))
			{
				EatRight(index_x, index_y, num, right);
				nRedOddCount--;//����������--
			}
			//������·�Ϊ�գ��ƶ������·�
			else if (rd == -1)
			{
				RightDownEmpty(index_x, index_y, num);
			}
			//����·�Ϊ�գ��ƶ����·�
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
			//����ҷ�Ϊ�գ��ƶ����ҷ�
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
		else//�������� >= ż���������Ե�ż��
		{
			//������·��м���ż�����ӣ��Ե�
			if ((rd >= 6) && (Red[rd - 6].num % 2 == 0))
			{
				EatRightDown(index_x, index_y, num, rd);
				nRedEvenCount--;//ż��������--
			}
			//����·��м���ż�����ӣ��Ե�
			else if ((down >= 6) && (Red[down - 6].num % 2 == 0))
			{
				EatDown(index_x, index_y, num, down);
				nRedEvenCount--;//ż��������--
			}
			//����ҷ��м���ż�����ӣ��Ե�
			else if ((right >= 6) && (Red[right - 6].num % 2 == 0))
			{
				EatRight(index_x, index_y, num, right);
				nRedEvenCount--;//ż��������--
			}
			//������·�Ϊ�գ��ƶ������·�
			else if (rd == -1)
			{
				RightDownEmpty(index_x, index_y, num);
			}
			//����·�Ϊ�գ��ƶ����·�
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
			//����ҷ�Ϊ�գ��ƶ����ҷ�
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
	}
	else if (index_x == 4 && index_y < 4)
	{
		int down = map[index_x][index_y + 1];//�·�λ�õ�����
		if (nRedEvenCount >= nRedOddCount)//ż������ >= �����������Ե�����
		{
			//����·��м����������ӣ��Ե�
			if ((down >= 6) && (Red[down - 6].num % 2 == 1))
			{
				EatDown(index_x, index_y, num, down);
				nRedOddCount--;//����������--
			}
			//����·�Ϊ�գ��ƶ����·�
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
		}
		else//�������� >= ż���������Ե�ż��
		{
			//����·��м���ż�����ӣ��Ե�
			if ((down >= 6) && (Red[down - 6].num % 2 == 0))
			{
				EatDown(index_x, index_y, num, down);
				nRedEvenCount--;//ż��������--
			}
			//����·�Ϊ�գ��ƶ����·�
			else if (down == -1)
			{
				DownEmpty(index_x, index_y, num);
			}
		}
	}
	else if (index_x < 4 && index_y == 4)
	{
		int right = map[index_x + 1][index_y];//�ҷ�λ�õ�����
		if (nRedEvenCount >= nRedOddCount)//ż������ >= �����������Ե�����
		{
			//����ҷ��м����������ӣ��Ե�
			if ((right >= 6) && (Red[right - 6].num % 2 == 1))
			{
				EatRight(index_x, index_y, num, right);
				nRedOddCount--;//����������--
			}
			//����ҷ�Ϊ�գ��ƶ����ҷ�
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
		else//�������� >= ż���������Ե�ż��
		{
			//����ҷ��м���ż�����ӣ��Ե�
			if ((right >= 6) && (Red[right - 6].num % 2 == 0))
			{
				EatRight(index_x, index_y, num, right);
				nRedEvenCount--;//ż��������--
			}
			//����ҷ�Ϊ�գ��ƶ����ҷ�
			else if (right == -1)
			{
				RightEmpty(index_x, index_y, num);
			}
		}
	}
}

//��������Ƿ���ڣ����ҳ������Ҵ��ڵ�����
int GameCtrl::IsExist(int num)
{
	int m, n;//���¼������ڵ�����m, n
	for (m = num; Red[m].flag == false && m > 0; m--);
	for (n = num; Red[n].flag == false && n < 5; n++);
	int index_mx = (Red[m].x - 200) / 100;//�ҵ��������Ӧ������
	int index_my = Red[m].y / 100;
	int index_nx = (Red[n].x - 200) / 100;//�ҵ��������Ӧ������
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
//�Ե����·���������
void GameCtrl::EatRightDown(int index_x, int index_y, int num, int rd)
{
	Red[rd - 6].flag = false;//���Ե������Ӵ�������ʧ
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x + 1][index_y + 1] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].x = (index_x + 1) * 100 + 205;
	Red[num].y = (index_y + 1) * 100 + 5;//�������ӵ�����
	nRedLeftCount--; //����������--
}
//�Ե��·���������
void GameCtrl::EatDown(int index_x, int index_y, int num, int down)
{
	Red[down - 6].flag = false;//���Ե������Ӵ�������ʧ
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x][index_y + 1] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].y = (index_y + 1) * 100 + 5; //�������ӵ�����
	nRedLeftCount--; //����������--
}
//�Ե��ҷ���������
void GameCtrl::EatRight(int index_x, int index_y, int num, int right)
{
	Red[right - 6].flag = false;//���Ե������Ӵ�������ʧ
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x + 1][index_y] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].x = (index_x + 1) * 100 + 205; //�������ӵ�����
	nRedLeftCount--; //����������--
}
//���·�Ϊ�գ������ƶ������·�
void GameCtrl::RightDownEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x + 1][index_y + 1] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].x = (index_x + 1) * 100 + 205;
	Red[num].y = (index_y + 1) * 100 + 5;//�������ӵ�����
}
//�·�Ϊ�գ������ƶ����·�
void GameCtrl::DownEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x][index_y + 1] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].y = (index_y + 1) * 100 + 5; //�������ӵ�����
}
//�ҷ�Ϊ�գ������ƶ����ҷ�
void GameCtrl::RightEmpty(int index_x, int index_y, int num)
{
	map[index_x][index_y] = -1;//���ƶ������Ӵ����̾�λ���ƿ�
	map[index_x + 1][index_y] = Red[num].num + 6-1;//���ƶ������ӷ�����������λ��
	Red[num].x = (index_x + 1) * 100 + 205; //�������ӵ�����
}

/////////////////////////////////////////////////////////////////////////////////////////////
void GameCtrl::IsFullClip()
{
	if (CanFullClip == true)//����ϴ��ҷ�����ȫ���������ж���һ��
	{
		for (int i = 0; i < 6; i++)//blue
		{
			if (Blue[i].flag == true)//���Ӵ���
			{
				bool flag = false;//�����ҷ�ʧȥȫ������
				for (int j = 0; j < 6; j++)//red
				{
					if (Red[j].flag == true)
						if (Blue[i].x > Red[j].x || Blue[i].y > Red[j].y)
						{
							flag = true;//���ڵз���˵blue[i]δ�ܵ����ҷ��󷽣��ҷ��Ծ���ȫ������
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
		if (index_x < 4 && index_y < 4)//ѡ�����������м�(������)
		{
			if (map[index_y + 1][index_x + 1] > -1 && map[index_y + 1][index_x + 1] < 6)//���������·�
			{
				KillEnemy(index_x, index_y, num, 2);
				return true;
			}
			else if (map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)//�������·�
			{
				KillEnemy(index_x, index_y, num, 1);
				return true;
			}
			else if (map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)//�������ҷ�
			{
				KillEnemy(index_x, index_y, num, 3);
				return true;
			}
		}
		else if (index_x == 4 && map[index_y + 1][index_x] > -1 && map[index_y + 1][index_x] < 6)//ѡ�����������ұߣ��������±ߣ�
		{
			KillEnemy(index_x, index_y, num, 1);
			return true;
		}
		else if (index_y == 4 && map[index_y][index_x + 1] > -1 && map[index_y][index_x + 1] < 6)//ѡ�����������±ߣ��������ұߣ�
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
		case 1://�������·�
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
		case 2://�������·�
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
			map[index_y + 1][index_x + 1] = num - 1 + 6;//+6��Ӧ��ɫ����
			break;
		}
		case 3://�������ұ�
		{
			Blue[map[index_y][index_x + 1]].flag = false;
			nBlueLeftCount--;
			if (Blue[map[index_y][index_x + 1]].num % 2 == 0)
				nBlueEvenCount--;
			else
				nBlueOddCount--;
			Red[num - 1].x = (index_x + 1) * 100 + 205;
			map[index_y][index_x] = -1;
			map[index_y][index_x + 1] = num - 1 + 6;//+6��Ӧ��ɫ����
			break;
		}
	}
}

bool GameCtrl::CanStartGame(int index_x, int index_y)
{
	if (nRedLeftCount > 3)
	{
		int temp = 0;//ͳ�ƿ��߷������Լ�������0-3
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

	//���������Ե��Է��������
	//a.�Ե�����в������
	if (((index_y == 0 && index_x == 0) || (index_y == 0 && index_x == 1)) &&//�±ߵз�����һ����в
		map[index_y + 1][index_x]<6 && map[index_y + 1][index_x]>-1)
	{
		KillEnemy(index_x, index_y, num, 1);
		return true;
	}
	else if ((index_y == 0 && index_x == 0) &&		//б�Խǵз�����һ����в
		map[index_y + 1][index_x + 1]<6 && map[index_y + 1][index_x + 1]>-1)
	{
		KillEnemy(index_x, index_y, num, 2);
		return true;
	}
	else if (((index_y == 0 && index_x == 0) || (index_y == 1 && index_x == 0)) && //�ұߵз�����һ����в
		map[index_y][index_x + 1]<6 && map[index_y][index_x + 1]>-1)
	{
		KillEnemy(index_x, index_y, num, 3);
		return true;
	}

	//����Χ
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
		//int ����������������ߣ���ϱܿ��ҷ����Ӻ;�̬���ز���ѡ��;
		if (index_x < 4 && index_y < 4)
		{
			int d = 0, r = 0, rd = 0;
			int *temp;//to be honest, it's very ridiculous...
			int EnemyCount = ScanEnemy(index_x, index_y, &d, &r, &rd);
			if (EnemyCount > 0)//��Χ�е��� kill
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
			}//����else
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

//ɨ�����������Χ�ĵ���,��������λ�ã���ʼʱd,r,dr��Ϊ0��ʾ�޵���
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
	IsFullClip();//����CanFullClip״̬

	if (CanFullClip == true)//��ʽ�������ȫ������
	{
		if (Red[nRand - 1].flag == true)//ѡ�е����Ӵ���
		{
			int index_x = (Red[nRand - 1].x - 200) / 100;//�ҵ��������Ӧ������
			int index_y = Red[nRand - 1].y / 100;
			//��һ�����յ�
			if (ToDestWithOneStep(index_x, index_y, nRand))
			{
				return true;
			}
			//����
			else if (FullClip(index_x, index_y, nRand))
			{
				return true;
			}
			//���㿪�����
			else if (CanStartGame(index_x, index_y))//����������>3����Χ���������������Ǽ������ӣ������ɸ���
			{
				StartGame(nRand - 1);
				return true;
			}
			//һ�����
			else
			{
				return NormalMove(index_x, index_y, nRand);
			}
		}
		/*------------------------------------------------------*/
		else //ѡ������Ӳ�����
		{
			int m, n;//���¼������ڵ�����m, n
			for (m = nRand - 1; Red[m].flag == false && m > 0; m--);
			for (n = nRand - 1; Red[n].flag == false && n < 5; n++);

			int index_mx = (Red[m].x - 200) / 100;//�ҵ��������Ӧ������
			int index_my = Red[m].y / 100;
			int index_nx = (Red[n].x - 200) / 100;//�ҵ��������Ӧ������
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


	else //ʧȥȫ������
	{
		if (Red[nRand - 1].flag == true)//ѡ�е����Ӵ���
		{
			int index_x = (Red[nRand - 1].x - 200) / 100;//�ҵ��������Ӧ������
			int index_y = Red[nRand - 1].y / 100;
			if (ToDestWithOneStep(index_x, index_y, nRand))
			{
				return true;
			}
			else if (CanStartGame(index_x, index_y))//����������>3����Χ���������������Ǽ������ӣ������ɸ���
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
			int m, n;//���¼������ڵ�����m, n
			for (m = nRand - 1; Red[m].flag == false && m > 0; m--);
			for (n = nRand - 1; Red[n].flag == false && n < 5; n++);
			int index_mx = (Red[m].x - 200) / 100;//�ҵ��������Ӧ������
			int index_my = Red[m].y / 100;
			int index_nx = (Red[n].x - 200) / 100;//�ҵ��������Ӧ������
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
