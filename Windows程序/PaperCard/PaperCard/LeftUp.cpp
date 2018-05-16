#include "LeftUp.h"
#include "resource.h"

CLeftUp::CLeftUp()
{
	//��ʼ������ͷβ
	m_pCloseCardsHead = NULL;
	m_pCloseCardsRear = NULL;
	m_pOpenCardsHead = NULL;
	m_pOpenCardsRear = NULL;
	m_hBackCardsBitmap = NULL;
	m_bCanRecycle = false;
}


CLeftUp::~CLeftUp()//�ͷ�����
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
	//���ر�����
	m_hBackCardsBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP53));

	//�·��Ƽ�����������е�ǰ28��������ֻ�ܼ��غ�ߵ�
	int nIndex = 28;
	for (int i = 0; i < 24; i++)
	{
		List* temp = new List;//����ռ�
		temp->m_Cards = cardsArr[vtr[nIndex++]];//�����ʣ�µ�24�����м���һ��
		temp->bflag = true;//�˴�Ϊ���淽���������ŵ�ȡ�ã�ֻ����ͼΪ�����ͼ
		temp->m_x = 30 + 3 * i;//�·�ÿ���Ƶĺ�����(�������Ͻ����ص�Ϊ׼)
		temp->m_y = 30;
		temp->m_pNext = NULL;
		temp->m_pPre = NULL;

		//��������
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
	//��ʾ�ر�����
	while (temp!= NULL)
	{
		//����������DC
		HDC hdc = CreateCompatibleDC(hMemDC);
		SelectObject(hdc, m_hBackCardsBitmap);
		BitBlt(hMemDC, temp->m_x, temp->m_y, 71, 96, hdc, 0, 0, SRCCOPY);

		DeleteDC(hdc);

		temp = temp->m_pNext;
	}

	//��ʾ������
	temp = m_pOpenCardsHead;
	while (temp != NULL)
	{
		//����������DC
		HDC hdc = CreateCompatibleDC(hMemDC);
		SelectObject(hdc, temp->m_Cards.m_hCardsBitMap);
		BitBlt(hMemDC, temp->m_x, temp->m_y, 71, 96, hdc, 0, 0, SRCCOPY);

		DeleteDC(hdc);

		temp = temp->m_pNext;
	}
}

bool CLeftUp::CanOpenLeftUpCards(POINT pt)
{
	//�Ƿ�����
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
	//���Ѿ��򿪵�������һ��,��������ͷ,ʵ����ֻ�ı�������Ƶĺ�����
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
		//ȡ�¹�������β��һ��
		temp = m_pCloseCardsRear;//��¼β���	
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

		//���ڴ򿪵�����β
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

		//�޸�����
		m_pOpenCardsRear->m_x = 190 + 20 * i;		
	}

}

void CLeftUp::CloseLeftUpCards()
{
	List* temp = NULL;
	int i = 0;
	while (m_pOpenCardsRear != NULL)
	{
		//ȡ�¹ر��ŵ��Ƶ����һ��
		temp = m_pOpenCardsRear;
		if (m_pOpenCardsRear == m_pOpenCardsHead)//ֻ��һ������
		{
			m_pOpenCardsHead = m_pOpenCardsRear = NULL;
		}
		else
		{
			m_pOpenCardsRear = m_pOpenCardsRear->m_pPre;
			m_pOpenCardsRear->m_pNext = NULL;
		}
		temp->m_pPre = temp->m_pNext = NULL;

		//���ڿ��ŵ�����β
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
	if (m_pOpenCardsHead == m_pOpenCardsRear)//ֻ��һ����
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


