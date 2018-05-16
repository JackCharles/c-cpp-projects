#include "RightUp.h"
#include <stdio.h>
CRightUp::CRightUp()
{
	for (int i = 0; i < 4; i++)
	{
		//初始化链表头尾
		m_pRightUpHead[i] = NULL;
		m_pRightUpRear[i] = NULL;
		m_nLinkID = -1;
		m_nGetCardLinkID = -1;
	}
}

CRightUp::~CRightUp()
{
	//释放右上角4个链表
	List* temp = NULL;
	for (int i = 0; i < 4; i++)
	{
		while (m_pRightUpHead[i] != NULL)
		{
			temp = m_pRightUpHead[i]->m_pNext;
			delete m_pRightUpHead[i];
			m_pRightUpHead[i] = temp;
		}
	}
}

void CRightUp::InitRightUpCards(HINSTANCE hInstance)
{
	//加载牌
	m_hRightUpBackBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP55));
}

void CRightUp::ShowRightUpCards(HDC hMemDC)
{	
	for (int i = 0; i < 4; i++)
	{
		//创建兼容性DC
		HDC hDc = CreateCompatibleDC(hMemDC);

		if (m_pRightUpHead[i] != NULL)
		{
			//绑定一张位图
			SelectObject(hDc, m_pRightUpRear[i]->m_Cards.m_hCardsBitMap);
		}
		else
		{
			SelectObject(hDc, m_hRightUpBackBmp);
		}

		//上传位图
		BitBlt(hMemDC, 330 + 100 * i, 30, 71, 96, hDc, 0, 0, SRCCOPY);
		DeleteDC(hDc);
	}
}

bool CRightUp::CanRightReceiveCard(POINT pt, List* pMouseLinkHead)
{	
	int upLinkID = (pt.x - 330) / 100;	//大致确定上面4个链表的ID

	//鼠标上是不是一张牌或者鼠标越界无法得到正确的upLinkID
	if ((upLinkID<0||upLinkID>3)||(pMouseLinkHead->m_pNext != NULL))
	{
		return false;
	}
	
	if ((pt.x >= 330 + upLinkID * 101 && pt.x <= 330 + upLinkID * 101 + 71) 
		&& (pt.y >= 30 && pt.y <= 126))//判断是不是在位置上
	{
		if (m_pRightUpHead[upLinkID] == NULL)//如果选定位置上没有牌
		{
			if (pMouseLinkHead->m_Cards.m_nCardsNum == 1)
			{
				m_nLinkID = upLinkID;//记录当前ID用于放牌
				return true;
			}
		}
		else//如果有牌
		{
			if (((m_pRightUpRear[upLinkID]->m_Cards.m_nCardsNum + 1) == pMouseLinkHead->m_Cards.m_nCardsNum)
				&& (m_pRightUpRear[upLinkID]->m_Cards.m_nCardsColor == pMouseLinkHead->m_Cards.m_nCardsColor))
			{
				m_nLinkID = upLinkID;//记录当前ID用于放牌
				return true;
			}
		}
	}
	return false;
}

void CRightUp::RightReceiveCard(List* &pMouseLinkHead, List* &pMouseLinkRear,CDownCards& oDownCards)
{
	if (m_pRightUpHead[m_nLinkID] == NULL)
	{
		m_pRightUpHead[m_nLinkID] = pMouseLinkHead;
		m_pRightUpRear[m_nLinkID] = pMouseLinkRear;
	}
	else
	{
		m_pRightUpRear[m_nLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pRightUpRear[m_nLinkID];
		m_pRightUpRear[m_nLinkID] = pMouseLinkHead;
	}
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;
	//修改坐标
	m_pRightUpRear[m_nLinkID]->m_x = 330 + 101 * m_nLinkID;
	m_pRightUpRear[m_nLinkID]->m_y = 30;

	//翻牌
	if (oDownCards.GetDownCardsRear(oDownCards.m_nLinkID) != NULL)
	{
		oDownCards.GetDownCardsRear(oDownCards.m_nLinkID)->bflag = true;
	}
}

bool CRightUp::CanGetCard(POINT pt)
{	
	if (pt.x >= 330)//防止upLinkID出现负数，需要大致确定位置
	{
		int upLinkID = (pt.x - 330) / 100;	//大致确定上面4个链表的ID

		if ((pt.x >= 330 + upLinkID * 101 && pt.x <= 330 + upLinkID * 101 + 71)
			&& (pt.y >= 30 && pt.y <= 126))//判断是不是在位置上
		{
			if (m_pRightUpHead[upLinkID] != NULL)//如果选定位置上没有牌
			{
				m_nGetCardLinkID = upLinkID;
				return true;
			}
		}
	}
	return false;
}

void CRightUp::GetRightCard(List *& pMouseLinkHead, List *& pMouseLinkRear)
{
	if (m_pRightUpHead[m_nGetCardLinkID] == m_pRightUpRear[m_nGetCardLinkID])//只有一张牌
	{
		pMouseLinkHead = pMouseLinkRear = m_pRightUpHead[m_nGetCardLinkID];
		m_pRightUpHead[m_nGetCardLinkID] = m_pRightUpRear[m_nGetCardLinkID] = NULL;
	}
	else
	{
		pMouseLinkHead = pMouseLinkRear = m_pRightUpRear[m_nGetCardLinkID];
		m_pRightUpRear[m_nGetCardLinkID] = m_pRightUpRear[m_nGetCardLinkID]->m_pPre;

		m_pRightUpRear[m_nGetCardLinkID]->m_pNext = NULL;
		pMouseLinkHead->m_pPre = NULL;
	}
}

void CRightUp::RecoverRightUpCard(List *& pMouseLinkHead, List *& pMouseLinkRear)
{
	if (m_pRightUpHead[m_nGetCardLinkID] == NULL)
	{
		m_pRightUpHead[m_nGetCardLinkID] = pMouseLinkHead;
		m_pRightUpRear[m_nGetCardLinkID] = pMouseLinkRear;
	}
	else
	{
		m_pRightUpRear[m_nGetCardLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pRightUpRear[m_nGetCardLinkID];
		m_pRightUpRear[m_nGetCardLinkID] = pMouseLinkRear;
	}

	//鼠标链表头尾赋空
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;
}

bool CRightUp::IsWinTheGame()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_pRightUpRear[i]==NULL || m_pRightUpRear[i]->m_Cards.m_nCardsNum != 13)
		{
			return false;
		}
	}
	return true;
}
