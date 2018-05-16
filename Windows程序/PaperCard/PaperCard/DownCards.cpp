#include "DownCards.h"
#include "resource.h"
#include<stdio.h>


CDownCards::CDownCards()
{
	//��ʼ��
	for (int i = 0; i < 7; i++)
	{
		m_pCardsHead[i] = NULL;//7��ͷ��ʼ��
		m_pCardsRear[i] = NULL;
	}
	m_hBackCardsBitmap = NULL;//��ʼ�������ƾ��
	m_pTemp = NULL;
	m_nLinkID = -1;
	m_nReceiveLinkID = -1;
}

CDownCards::~CDownCards()//�ͷ���������
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

void CDownCards::LoadDownCards(Cards cardsArr[], vector<int>& vtr, HINSTANCE hInstance)//vtr�ṩ���������
{
	//���ر�����
	m_hBackCardsBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP53));
	int nIndex = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			List* temp = new List;//����ռ�
			temp->m_Cards = cardsArr[vtr[nIndex++]];//�����52�����м���һ��
			temp->bflag = false;//��ʼ���泯��
			temp->m_x = 30+100*i;//�·�ÿ���Ƶĺ�����(�������Ͻ����ص�Ϊ׼)
			temp->m_y = 156+30*j;//
			temp->m_pNext = NULL;
			temp->m_pPre = NULL;

			//��������
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
		m_pCardsRear[i]->bflag = true;//���һ����Ϊ����
	}
}

void CDownCards::ShowDownCards(HDC hMemDC)//hMenDC�ڴ�DC
{
	List*temp = NULL;
	for (int i = 0; i < 7; i++)
	{
		temp = m_pCardsHead[i];
		while (NULL != temp)
		{
			HDC hdc = CreateCompatibleDC(hMemDC);//����һ���ڴ�DC
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
	//����ȷ�����ѡ���ĸ�����
	int LinkID=pt.x/100;

	List* temp = m_pCardsHead[LinkID];//��������
	while (NULL != temp)
	{
		//��������β�ڵ�
		if (temp == m_pCardsRear[LinkID])
		{
			if ((pt.x >= temp->m_x&&pt.x <= temp->m_x + 71) && (pt.y >= temp->m_y&&pt.y <= temp->m_y + 96))
			{
				m_pTemp = temp;
				m_nLinkID = LinkID;
				return true;
			}
		}
		else//�����м�
		{
			if ((pt.x >= temp->m_x&&pt.x <= temp->m_x + 71) && (pt.y >= temp->m_y&&pt.y <= temp->m_y + 30))
			{
				if (temp->bflag == true)//��������泯��
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
	if (m_pCardsHead[m_nLinkID] == m_pTemp)//���������Ľڵ�m_pTemp��ͷ�����ֱ����������
	{
		pMouseLinkHead = m_pCardsHead[m_nLinkID];
		pMouseLinkRear = m_pCardsRear[m_nLinkID];
		m_pCardsHead[m_nLinkID] = m_pCardsRear[m_nLinkID] = NULL;
	}
	else//�㵽�м�ڵ�
	{
		//����
		pMouseLinkHead = m_pTemp;
		pMouseLinkRear = m_pCardsRear[m_nLinkID];

		//���
		m_pCardsRear[m_nLinkID] = m_pTemp->m_pPre;
		m_pCardsRear[m_nLinkID]->m_pNext = NULL;
		pMouseLinkHead->m_pPre = NULL;
	}
	m_pTemp = NULL;
	//�˴�m_nLinkID�������ã��п�������ϵ���Ҫ��λ��m_nLinkID��·
}

bool CDownCards::CanReceiveCards(POINT pt, List* pMouseLinkHead)
{
	//����ȷ�����ѡ��Ŀ������
	int LinkID = pt.x / 100;
	if (LinkID < 0 || LinkID>6)//�������Խ�絼�µĴ���
	{
		return false;
	}

	List* temp = m_pCardsHead[LinkID];

	if (temp == NULL)//Ŀ������Ϊ�գ��������ƣ�����ʱֻ�ܷ�k
	{
		//������жϲ��ܸ�����ѡ����ͷ��λ���жϣ�ͷΪ��û��λ����Ϣ
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
	else//Ŀ������Ϊ��
	{
		//�ǲ��ǵ�������β��
		if ((pt.x >= m_pCardsRear[LinkID]->m_x&&pt.x <= m_pCardsRear[LinkID]->m_x + 71)
			&& (pt.y >= m_pCardsRear[LinkID]->m_y&&pt.y <= m_pCardsRear[LinkID]->m_y + 96))
		{
			//�жϵ���
			if ((pMouseLinkHead->m_Cards.m_nCardsNum + 1) == m_pCardsRear[LinkID]->m_Cards.m_nCardsNum)
			{
				/*/�жϻ�ɫ��Ժ�
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
	if (m_pCardsHead[m_nReceiveLinkID] == NULL)//�������λ��Ϊ��
	{
		m_pCardsHead[m_nReceiveLinkID] = pMouseLinkHead;
		m_pCardsRear[m_nReceiveLinkID] = pMouseLinkRear;
	}
	else//��������Ŀ������β��
	{
		m_pCardsRear[m_nReceiveLinkID]->m_pNext = pMouseLinkHead;
		pMouseLinkHead->m_pPre = m_pCardsRear[m_nReceiveLinkID];

		m_pCardsRear[m_nReceiveLinkID] = pMouseLinkRear;
	}
	//�������ͷβ����
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;

	//�����·��õ��Ƶ�����
	int i = 0;
	List* temp = m_pCardsHead[m_nReceiveLinkID];
	while (temp != NULL)
	{
		temp->m_x = 100 * m_nReceiveLinkID + 30;
		temp->m_y = 156 + i * 30;
		i++;
		temp = temp->m_pNext;
	}

	//����
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

	//�������ͷβ����
	pMouseLinkHead = NULL;
	pMouseLinkRear = NULL;
}