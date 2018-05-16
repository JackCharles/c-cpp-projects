#include <windows.h>
#include "CardCtrl.h"
#include "resource.h"

#define DownCards    0
#define RightUpCards 1
#define LeftUpCards  2


int CardsSource = -1;//�������λ��
//���캯��
CCardCtrl::CCardCtrl() :m_vtr(52)
{
	m_hWnd = NULL;
	m_hInstance = NULL;
	m_pMouseLinkHead = NULL;
	m_pMouseLinkRear = NULL;

	//������ʼ��
	for (int i = 0; i < 52; i++)
	{
		m_vtr[i] = i;
	}

	//�����������,��ϴ�ƹ���
	srand(time(NULL));
	random_shuffle(m_vtr.begin(), m_vtr.end());
}

//�������ݳ�Ա
void CCardCtrl::SetDataValue(HWND hwnd,HINSTANCE hInstance)
{
	m_hWnd = hwnd;
	m_hInstance = hInstance;
}

//��ʼ����Ϸ����
void CCardCtrl::InitGameData()
{
	//����52����
	LoadCards();
	//�������沿�ֵ���
	m_oDownCards.LoadDownCards(m_cardsArr, m_vtr, m_hInstance);
	//�������Ͻǵ���
	m_oRightUpCards.InitRightUpCards(m_hInstance);
	//�������Ͻǵ���
	m_oLeftUpCars.InitLeftUpCards(m_cardsArr, m_vtr, m_hInstance);
}

//������
void CCardCtrl::LoadCards()
{
	for (int i = 0; i < 13; i++)//÷��
	{
		m_cardsArr[i].m_nCardsNum = i + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_flower;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 13; i < 26; i++)//����
	{
		m_cardsArr[i].m_nCardsNum = i-13 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_square;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 39; i < 52; i++)//����
	{
		m_cardsArr[i].m_nCardsNum = i-39 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_black;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}

	for (int i = 26; i < 39; i++)//����
	{
		m_cardsArr[i].m_nCardsNum = i-26 + 1;
		m_cardsArr[i].m_nCardsColor = enum_cards_heart;
		m_cardsArr[i].m_hCardsBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	}
}

//����paint��Ϣ
void CCardCtrl::OnPaint()/////////////�ѵ�
{
	HDC hDc = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hDc);

	m_hBackGroundBit = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP54));

	SelectObject(hMemDC, m_hBackGroundBit);

	DeleteObject(m_hBackGroundBit);//ɾ��������������SelectObject

	m_oDownCards.ShowDownCards(hMemDC);
	m_oRightUpCards.ShowRightUpCards(hMemDC);
	m_oLeftUpCars.ShowLeftUpCards(hMemDC);
	this->ShowMouseCards(hMemDC);

	BitBlt(hDc, 0, 0, 750, 700, hMemDC, 0, 0, SRCCOPY);
	
	DeleteDC(hMemDC);
	DeleteDC(hDc);
}

//���������Ϣ
void CCardCtrl::OnKeyDown(UINT nKeyID)
{

}

//����ʱ����Ϣ
void CCardCtrl::OnTimer(UINT nTimerID)
{

}

//��������������
void CCardCtrl::OnLButtonDown(POINT pt)
{
	m_LeftButtonDownPos = pt;
	if (m_oDownCards.CanMouseGetCard(pt))//Down����
	{
		CardsSource = DownCards;
		m_oDownCards.MouseGetCard(m_pMouseLinkHead, m_pMouseLinkRear);
	}
	
	else if (m_oRightUpCards.CanGetCard(pt))//RightUp����
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

//��������Ҽ�����
void CCardCtrl::OnRButtonDown(POINT pt)
{

}

//����������̧��
void CCardCtrl::OnLButtonUP(POINT pt)
{
	if (m_pMouseLinkHead != NULL)
	{
		//�ж�Down�Ƿ��ܽ���
		if (m_oDownCards.CanReceiveCards(pt, m_pMouseLinkHead))
		{
			m_oDownCards.ReceiveCards(m_pMouseLinkHead, m_pMouseLinkRear);
		}

		//�ж�RightUp�Ƿ��ܽ���
		else if (m_oRightUpCards.CanRightReceiveCard(pt, m_pMouseLinkHead))
		{
			m_oRightUpCards.RightReceiveCard(m_pMouseLinkHead, m_pMouseLinkRear, m_oDownCards);
		}

		//�������һ�ɸ�λ
		else
		{
			if (CardsSource == DownCards)//�жϻָ�λ��
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
		MessageBox(m_hWnd, "��ϲ����ʤ��!", "��ʾ", MB_OK);
	}
}

//��������Ҽ�̧��
void CCardCtrl::OnRButtonUP(POINT pt)
{

}

//��������ƶ�
void CCardCtrl::OnMouseMOve(POINT pt)
{
	m_MouseMovePos = pt;
	if (m_pMouseLinkHead != NULL)
	{
		this->OnPaint();
	}
}

//��ʾ�����
void CCardCtrl::ShowMouseCards(HDC hMemDC)
{
	int x_added = m_MouseMovePos.x - m_LeftButtonDownPos.x;
	int y_added = m_MouseMovePos.y - m_LeftButtonDownPos.y;
	List* temp = m_pMouseLinkHead;
	while (NULL != temp)
	{
		//����������DC
		HDC hDc = CreateCompatibleDC(hMemDC);
		SelectObject(hDc, temp->m_Cards.m_hCardsBitMap);
		BitBlt(hMemDC, temp->m_x+x_added, temp->m_y+y_added, 71, 96, hDc, 0, 0, SRCCOPY);

		DeleteDC(hDc);

		temp = temp->m_pNext;
	}
}