#include <windows.h>
#include "CardCtrl.h"
#include "resource.h"

#define DownCards    0
#define RightUpCards 1
#define LeftUpCards  2


int CardsSource = -1;//标记拿牌位置
//构造函数
CCardCtrl::CCardCtrl() :m_vtr(52)
{
	m_hWnd = NULL;
	m_hInstance = NULL;
	m_pMouseLinkHead = NULL;
	m_pMouseLinkRear = NULL;

	//向量初始化
	for (int i = 0; i < 52; i++)
	{
		m_vtr[i] = i;
	}

	//向量随机排列,即洗牌过程
	srand(time(NULL));
	random_shuffle(m_vtr.begin(), m_vtr.end());
}

//设置数据成员
void CCardCtrl::SetDataValue(HWND hwnd,HINSTANCE hInstance)
{
	m_hWnd = hwnd;
	m_hInstance = hInstance;
}

//初始化游戏数据
void CCardCtrl::InitGameData()
{
	//加载52张牌
	LoadCards();
	//加载下面部分的牌
	m_oDownCards.LoadDownCards(m_cardsArr, m_vtr, m_hInstance);
	//加载右上角的牌
	m_oRightUpCards.InitRightUpCards(m_hInstance);
	//加载左上角的牌
	m_oLeftUpCars.InitLeftUpCards(m_cardsArr, m_vtr, m_hInstance);
}

//加载牌
void CCardCtrl::LoadCards()
{
	for (int i = 0; i < 13; i++)//梅花
	{
		m_cardsArr[i].m_nCardsNum = i + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_flower;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 13; i < 26; i++)//方块
	{
		m_cardsArr[i].m_nCardsNum = i-13 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_square;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 39; i < 52; i++)//黑桃
	{
		m_cardsArr[i].m_nCardsNum = i-39 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_black;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 26; i < 39; i++)//红桃
	{
		m_cardsArr[i].m_nCardsNum = i-26 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_heart;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}
}

//处理paint消息
void CCardCtrl::OnPaint()/////////////难点
{
	HDC hDc = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hDc);

	m_hBackGroundBit = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP54));

	SelectObject(hMemDC, m_hBackGroundBit);

	DeleteObject(m_hBackGroundBit);//删除背景对象，由于SelectObject

	m_oDownCards.ShowDownCards(hMemDC);
	m_oRightUpCards.ShowRightUpCards(hMemDC);
	m_oLeftUpCars.ShowLeftUpCards(hMemDC);
	this->ShowMouseCards(hMemDC);

	BitBlt(hDc, 0, 0, 750, 700, hMemDC, 0, 0, SRCCOPY);
	
	DeleteDC(hMemDC);
	DeleteDC(hDc);
}

//处理键盘消息
void CCardCtrl::OnKeyDown(UINT nKeyID)
{

}

//处理定时器消息
void CCardCtrl::OnTimer(UINT nTimerID)
{

}

//处理鼠标左键按下
void CCardCtrl::OnLButtonDown(POINT pt)
{
	m_LeftButtonDownPos = pt;
	if (m_oDownCards.CanMouseGetCard(pt))//Down拿牌
	{
		CardsSource = DownCards;
		m_oDownCards.MouseGetCard(m_pMouseLinkHead, m_pMouseLinkRear);
	}
	
	else if (m_oRightUpCards.CanGetCard(pt))//RightUp拿牌
	{
		CardsSource = RightUpCards;
		m_oRightUpCards.GetRightCard(m_pMouseLinkHead, m_pMouseLinkRear);
	}

	else if (m_oLeftUpCars.CanGetLeftUpCards(pt))
	{
		CardsSource = LeftUpCards;
		m_oLeftUpCars.GetLeftUpCards(m_pMouseLinkHead, m_pMouseLinkRear);
	}
	////////////////////////////////////////////////////////////////

	if (m_oLeftUpCars.CanOpenLeftUpCards(pt))
	{
		m_oLeftUpCars.OpenLeftUpCards();
	}
	else
	{
		if (m_oLeftUpCars.m_bCanRecycle)
		{
			m_oLeftUpCars.m_bCanRecycle = false;
			m_oLeftUpCars.CloseLeftUpCards();
		}
	}	
	this->OnPaint();
}

//处理鼠标右键按下
void CCardCtrl::OnRButtonDown(POINT pt)
{

}

//处理鼠标左键抬起
void CCardCtrl::OnLButtonUP(POINT pt)
{
	if (m_pMouseLinkHead != NULL)
	{
		//判断Down是否能接收
		if (m_oDownCards.CanReceiveCards(pt, m_pMouseLinkHead))
		{
			m_oDownCards.ReceiveCards(m_pMouseLinkHead, m_pMouseLinkRear);
		}

		//判断RightUp是否能接收
		else if (m_oRightUpCards.CanRightReceiveCard(pt, m_pMouseLinkHead))
		{
			m_oRightUpCards.RightReceiveCard(m_pMouseLinkHead, m_pMouseLinkRear, m_oDownCards);
		}

		//其他情况一律复位
		else
		{
			if (CardsSource == DownCards)//判断恢复位置
			{
				m_oDownCards.RecoverCards(m_pMouseLinkHead, m_pMouseLinkRear);
			}
			else if(CardsSource == RightUpCards)
			{
				m_oRightUpCards.RecoverRightUpCard(m_pMouseLinkHead, m_pMouseLinkRear);
			}
			else if (CardsSource == LeftUpCards)
			{
				m_oLeftUpCars.RecoverLeftUpCard(m_pMouseLinkHead, m_pMouseLinkRear);
			}
		}

		this->OnPaint();
	}

	if (m_oRightUpCards.IsWinTheGame())
	{
		MessageBox(m_hWnd, "恭喜你获得胜利!", "提示", MB_OK);
	}
}

//处理鼠标右键抬起
void CCardCtrl::OnRButtonUP(POINT pt)
{

}

//处理鼠标移动
void CCardCtrl::OnMouseMOve(POINT pt)
{
	m_MouseMovePos = pt;
	if (m_pMouseLinkHead != NULL)
	{
		this->OnPaint();
	}
}

//显示鼠标牌
void CCardCtrl::ShowMouseCards(HDC hMemDC)
{
	int x_added = m_MouseMovePos.x - m_LeftButtonDownPos.x;
	int y_added = m_MouseMovePos.y - m_LeftButtonDownPos.y;
	List* temp = m_pMouseLinkHead;
	while (NULL != temp)
	{
		//创建兼容性DC
		HDC hDc = CreateCompatibleDC(hMemDC);
		SelectObject(hDc, temp->m_Cards.m_hCardsBitMap);
		BitBlt(hMemDC, temp->m_x+x_added, temp->m_y+y_added, 71, 96, hDc, 0, 0, SRCCOPY);

		DeleteDC(hDc);

		temp = temp->m_pNext;
	}
}