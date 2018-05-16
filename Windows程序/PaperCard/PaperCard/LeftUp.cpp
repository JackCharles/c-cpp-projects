#include "LeftUp.h"
#include "resource.h"

CLeftUp::CLeftUp()
{
	//初始化链表头尾
	m_pCloseCardsHead = NULL;
	m_pCloseCardsRear = NULL;
	m_pOpenCardsHead = NULL;
	m_pOpenCardsRear = NULL;
	m_hBackCardsBitmap = NULL;
	m_bCanRecycle = false;
}


CLeftUp::~CLeftUp()//释放链表
{
	List* temp = NULL;

	while (m_pCloseCardsHead != NULL)
	{
		temp = m_pCloseCardsHead->m_pNext;
		delete m_pCloseCardsHead;
		m_pCloseCardsHead = temp;
	}

	while (m_pOpenCardsHead != NULL)
	{
		temp = m_pOpenCardsHead->m_pNext;
		delete m_pOpenCardsHead;
		m_pOpenCardsHead = temp;
	}
}

void CLeftUp::InitLeftUpCards(Cards cardsArr[], vector<int>& vtr, HINSTANCE hInstance)
{
	//加载背景牌
	m_hBackCardsBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP53));

	//下方牌加载了随机序列的前28个，现在只能加载后边的
	int nIndex = 28;
	for (int i = 0; i < 24; i++)
	{
		List* temp = new List;//申请空间
		temp->m_Cards = cardsArr[vtr[nIndex++]];//随机从剩下的24张牌中加载一张
		temp->bflag = true;//此处为正面方便另外三张的取用，只是贴图为背面的图
		temp->m_x = 30 + 3 * i;//下方每张牌的横坐标(都以左上角像素点为准)
		temp->m_y = 30;
		temp->m_pNext = NULL;
		temp->m_pPre = NULL;

		//链接链表
		if (m_pCloseCardsHead == NULL)
		{
			m_pCloseCardsHead = temp;
			m_pCloseCardsRear = temp;
		}
		else
		{
			m_pCloseCardsRear->m_pNext = temp;
			temp->m_pPre = m_pCloseCardsRear;
			m_pCloseCardsRear = temp;
		}
	}
}

void CLeftUp::ShowLeftUpCards(HDC hMemDC)
{
	List* temp = m_pCloseCardsHead;
	//显示关闭链表
	while (temp!= NULL)
	{
		//创建兼容性DC
		HDC hdc = CreateCompatibleDC(hMemDC);
		SelectObject(hdc, m_hBackCardsBitmap);
		BitBlt(hMemDC, temp->m_x, temp->m_y, 71, 96, hdc, 0, 0, SRCCOPY);

		DeleteDC(hdc);

		temp = temp->m_pNext;
	}

	//显示打开链表
	temp = m_pOpenCardsHead;
	while (temp != NULL)
	{
		//创建兼容性DC
		HDC hdc = CreateCompatibleDC(hMemDC);
		SelectObject(hdc, temp->m_Cards.m_hCardsBitMap);
		BitBlt(hMemDC, temp->m_x, temp->m_y, 71, 96, hdc, 0, 0, SRCCOPY);

		DeleteDC(hdc);

		temp = temp->m_pNext;
	}
}

bool CLeftUp::CanOpenLeftUpCards(POINT pt)
{
	//是否有牌
	if (m_pCloseCardsHead == NULL)
	{
		if ((pt.x >= 30 && pt.x <= 101) && (pt.y >= 30 && pt.y <= 126))
		{
			m_bCanRecycle = true;
			return false;
		}
	}
	
	else
	{
		if ((pt.x >=m_pCloseCardsRear->m_x && pt.x<= m_pCloseCardsRear->m_x + 71)
			&& (pt.y >= 30 && pt.y <= 126))
		{
			return true;
		}
	}
	return false;
}

void CLeftUp::OpenLeftUpCards()
{
	//把已经打开的牌摞在一起,摞在链表头,实际上只改变后两张牌的横坐标
	List* temp = m_pOpenCardsRear;
	if (temp != NULL)
	{
		if (temp->m_pPre != NULL)
		{
			temp->m_pPre->m_x = 190;
		}
		temp->m_x = 190;
	}

	for (int i = 0; i < 3; i++)
	{
		//取下关着链表尾的一个
		temp = m_pCloseCardsRear;//记录尾结点	
		if (temp == NULL)
		{
			return;
		}
		else if (m_pCloseCardsHead == m_pCloseCardsRear)
		{
			m_pCloseCardsHead = m_pCloseCardsRear = NULL;
			
		}
		else
		{
			m_pCloseCardsRear = m_pCloseCardsRear->m_pPre;
			m_pCloseCardsRear->m_pNext = NULL;		
		}
		temp->m_pPre = temp->m_pNext = NULL;

		//接在打开的链表尾
		if (m_pOpenCardsHead == NULL)
		{
			m_pOpenCardsHead = m_pOpenCardsRear=temp;
		}
		else
		{
			m_pOpenCardsRear->m_pNext = temp;
			temp->m_pPre = m_pOpenCardsRear;
			m_pOpenCardsRear = temp;
		}

		//修改坐标
		m_pOpenCardsRear->m_x = 190 + 20 * i;		
	}

}

void CLeftUp::CloseLeftUpCards()
{
	List* temp = NULL;
	int i = 0;
	while (m_pOpenCardsRear != NULL)
	{
		//取下关闭着的牌的最后一张
		temp = m_pOpenCardsRear;
		if (m_pOpenCardsRear == m_pOpenCardsHead)//只有一张牌了
		{
			m_pOpenCardsHead = m_pOpenCardsRear = NULL;
		}
		else
		{
			m_pOpenCardsRear = m_pOpenCardsRear->m_pPre;
			m_pOpenCardsRear->m_pNext = NULL;
		}
		temp->m_pPre = temp->m_pNext = NULL;

		//接在开着的链表尾
		if (m_pCloseCardsHead == NULL)
		{
			m_pCloseCardsHead = m_pCloseCardsRear = temp;
		}
		else
		{
			temp->m_pPre = m_pCloseCardsRear;
			m_pCloseCardsRear->m_pNext = temp;
			m_pCloseCardsRear = temp;		
		}
		m_pCloseCardsRear->m_x = 30 + 3 * i;
		i++;
	}
}

bool CLeftUp::CanGetLeftUpCards(POINT pt)
{
	if (m_pOpenCardsHead != NULL)
	{
		if ((pt.x >= m_pOpenCardsRear->m_x&&pt.x <= m_pOpenCardsRear->m_x + 71)
			&& (pt.y >= 30 && pt.y <= 126))
		{
			return true;
		}
	}
	return false;
}

void CLeftUp::GetLeftUpCards(List *& pMouseLinkHead, List *& pMouseLinkRear)
{
	if (m_pOpenCardsHead == m_pOpenCardsRear)//只有一张牌
	{
		pMouseLinkHead = pMouseLinkRear = m_pOpenCardsHead;
		m_pOpenCardsHead = m_pOpenCardsRear = NULL;
	}
	else
	{
		pMouseLinkHead = pMouseLinkRear = m_pOpenCardsRear;
		m_pOpenCardsRear = m_pOpenCardsRear->m_pPre;
		m_pOpenCardsRear->m_pNext = NULL;
	}
	pMouseLinkHead->m_pPre = NULL;

}

void CLeftUp::RecoverLeftUpCard(List* &pMouseLinkHead, List* &pMouseLinkRear)
{
	if (m_pOpenCardsHead == NULL)
	{
		m_pOpenCardsHead = m_pOpenCardsRear = pMouseLinkHead;
	}
	else
	{
		m_pOpenCardsRear->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pOpenCardsRear;
		m_pOpenCardsRear = pMouseLinkRear;
	}
	pMouseLinkHead = pMouseLinkRear = NULL;
}


