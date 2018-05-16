#include "DownCards.h"
#include "resource.h"
#include<stdio.h>


CDownCards::CDownCards()
{
	//初始化
	for (int i = 0; i < 7; i++)
	{
		m_pCardsHead[i] = NULL;//7个头初始化
		m_pCardsRear[i] = NULL;
	}
	m_hBackCardsBitmap = NULL;//初始化背景牌句柄
	m_pTemp = NULL;
	m_nLinkID = -1;
	m_nReceiveLinkID = -1;
}

CDownCards::~CDownCards()//释放链表数组
{
	List* temp = NULL;
	for (int i = 0; i < 7; i++)
	{
		temp = m_pCardsHead[i];
		while (NULL != temp)
		{
			m_pCardsHead[i] = m_pCardsHead[i]->m_pNext;
			delete temp;
			temp = m_pCardsHead[i];
		}
	}
}

void CDownCards::LoadDownCards(Cards cardsArr[], vector<int>& vtr, HINSTANCE hInstance)//vtr提供随机数序列
{
	//加载背景牌
	m_hBackCardsBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP53));
	int nIndex = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			List* temp = new List;//申请空间
			temp->m_Cards = cardsArr[vtr[nIndex++]];//随机从52张牌中加载一张
			temp->bflag = false;//开始背面朝上
			temp->m_x = 30+100*i;//下方每张牌的横坐标(都以左上角像素点为准)
			temp->m_y = 156+30*j;//
			temp->m_pNext = NULL;
			temp->m_pPre = NULL;

			//链接链表
			if (m_pCardsHead[i] == NULL)
			{
				m_pCardsHead[i] = temp;
				m_pCardsRear[i] = temp;
			}
			else
			{
				m_pCardsRear[i]->m_pNext = temp;
				temp->m_pPre = m_pCardsRear[i];
				m_pCardsRear[i] = temp;
			}
		}
		m_pCardsRear[i]->bflag = true;//最后一张牌为正面
	}
}

void CDownCards::ShowDownCards(HDC hMemDC)//hMenDC内存DC
{
	List*temp = NULL;
	for (int i = 0; i < 7; i++)
	{
		temp = m_pCardsHead[i];
		while (NULL != temp)
		{
			HDC hdc = CreateCompatibleDC(hMemDC);//创建一个内存DC
			if (temp->bflag == true)
			{
				SelectObject(hdc, temp->m_Cards.m_hCardsBitMap);
			}
			else
			{
				SelectObject(hdc, m_hBackCardsBitmap);
			}

			BitBlt(hMemDC, temp->m_x, temp->m_y, 71, 96,hdc,0,0,SRCCOPY);

			DeleteDC(hdc);

			temp = temp->m_pNext;
		}
		
	}
}

bool CDownCards::CanMouseGetCard(POINT pt)
{
	//粗略确定鼠标选定哪个链表
	int LinkID=pt.x/100;

	List* temp = m_pCardsHead[LinkID];//遍历链表
	while (NULL != temp)
	{
		//如果点击在尾节点
		if (temp == m_pCardsRear[LinkID])
		{
			if ((pt.x >= temp->m_x&&pt.x <= temp->m_x + 71) && (pt.y >= temp->m_y&&pt.y <= temp->m_y + 96))
			{
				m_pTemp = temp;
				m_nLinkID = LinkID;
				return true;
			}
		}
		else//点在中间
		{
			if ((pt.x >= temp->m_x&&pt.x <= temp->m_x + 71) && (pt.y >= temp->m_y&&pt.y <= temp->m_y + 30))
			{
				if (temp->bflag == true)//如果是正面朝上
				{
					m_pTemp = temp;
					m_nLinkID = LinkID;
					return true;
				}
			}
		}

		temp = temp->m_pNext;
	}
	return false;
}

void CDownCards::MouseGetCard(List* &pMouseLinkHead, List* &pMouseLinkRear)
{
	if (m_pCardsHead[m_nLinkID] == m_pTemp)//如果点击到的节点m_pTemp是头结点则直接拿起链表
	{
		pMouseLinkHead = m_pCardsHead[m_nLinkID];
		pMouseLinkRear = m_pCardsRear[m_nLinkID];
		m_pCardsHead[m_nLinkID] = m_pCardsRear[m_nLinkID] = NULL;
	}
	else//点到中间节点
	{
		//先连
		pMouseLinkHead = m_pTemp;
		pMouseLinkRear = m_pCardsRear[m_nLinkID];

		//后断
		m_pCardsRear[m_nLinkID] = m_pTemp->m_pPre;
		m_pCardsRear[m_nLinkID]->m_pNext = NULL;
		pMouseLinkHead->m_pPre = NULL;
	}
	m_pTemp = NULL;
	//此处m_nLinkID不能重置，有可能鼠标上的牌要归位靠m_nLinkID引路
}

bool CDownCards::CanReceiveCards(POINT pt, List* pMouseLinkHead)
{
	//粗略确定鼠标选定目标链表
	int LinkID = pt.x / 100;
	if (LinkID < 0 || LinkID>6)//处理鼠标越界导致的错误
	{
		return false;
	}

	List* temp = m_pCardsHead[LinkID];

	if (temp == NULL)//目标链表为空（该列无牌），此时只能放k
	{
		//下面的判断不能根据所选链表头的位置判断，头为空没有位置信息
		if ((pt.x >= LinkID * 100 + 30 && pt.x <= LinkID * 100 + 30 + 71) 
			&& (pt.y >= 156 && pt.y <= 156 + 96))
		{
			if (pMouseLinkHead->m_Cards.m_nCardsNum == 13)
			{
				m_nReceiveLinkID = LinkID;
				return true;
			}
		}
	}
	else//目标链表不为空
	{
		//是不是点在链表尾上
		if ((pt.x >= m_pCardsRear[LinkID]->m_x&&pt.x <= m_pCardsRear[LinkID]->m_x + 71)
			&& (pt.y >= m_pCardsRear[LinkID]->m_y&&pt.y <= m_pCardsRear[LinkID]->m_y + 96))
		{
			//判断点数
			if ((pMouseLinkHead->m_Cards.m_nCardsNum + 1) == m_pCardsRear[LinkID]->m_Cards.m_nCardsNum)
			{
				/*/判断花色红对黑
				if (((m_pCardsRear[LinkID]->m_Cards.m_nCardsColor == enum_cards_black) || (m_pCardsRear[LinkID]->m_Cards.m_nCardsColor == enum_cards_flower))
					&& ((pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_heart) || (pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_square)))
				{
					m_nReceiveLinkID = LinkID;
					return true;
				}

				else if (((m_pCardsRear[LinkID]->m_Cards.m_nCardsColor == enum_cards_heart) || (m_pCardsRear[LinkID]->m_Cards.m_nCardsColor == enum_cards_square))
					&& ((pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_black) || (pMouseLinkHead->m_Cards.m_nCardsColor == enum_cards_flower)))
				{*/
					m_nReceiveLinkID = LinkID;
					return true;
				//}
			}
		}
	}

	return false;
}

void CDownCards::ReceiveCards(List* &pMouseLinkHead, List* &pMouseLinkRear)
{
	if (m_pCardsHead[m_nReceiveLinkID] == NULL)//如果放置位置为空
	{
		m_pCardsHead[m_nReceiveLinkID] = pMouseLinkHead;
		m_pCardsRear[m_nReceiveLinkID] = pMouseLinkRear;
	}
	else//鼠标链表接目标链表尾上
	{
		m_pCardsRear[m_nReceiveLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pCardsRear[m_nReceiveLinkID];

		m_pCardsRear[m_nReceiveLinkID] = pMouseLinkRear;
	}
	//鼠标链表头尾赋空
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;

	//更新新放置的牌的坐标
	int i = 0;
	List* temp = m_pCardsHead[m_nReceiveLinkID];
	while (temp != NULL)
	{
		temp->m_x = 100 * m_nReceiveLinkID + 30;
		temp->m_y = 156 + i * 30;
		i++;
		temp = temp->m_pNext;
	}

	//翻牌
	if (m_pCardsHead[m_nLinkID] != NULL)
	{
		m_pCardsRear[m_nLinkID]->bflag = true;
	}
}

void CDownCards::RecoverCards(List* &pMouseLinkHead, List* &pMouseLinkRear)
{
	if (m_pCardsHead[m_nLinkID] == NULL)
	{
		m_pCardsHead[m_nLinkID] = pMouseLinkHead;
		m_pCardsRear[m_nLinkID] = pMouseLinkRear;
	}
	else
	{
		m_pCardsRear[m_nLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pCardsRear[m_nLinkID];
		m_pCardsRear[m_nLinkID] = pMouseLinkRear;
	}

	//鼠标链表头尾赋空
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;
}