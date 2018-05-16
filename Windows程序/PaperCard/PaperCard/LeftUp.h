#pragma once
#include "Cards.h"
#include "DownCards.h"


//���ϽǷ�����
class CLeftUp
{
public:
	CLeftUp();
	~CLeftUp();

private:
	List* m_pCloseCardsHead;//���������泯�µ��Ƶ�����ͷ
	List* m_pCloseCardsRear;
	List* m_pOpenCardsHead;//���������泯�ϵ��Ƶ�����ͷ
	List* m_pOpenCardsRear;
	HBITMAP m_hBackCardsBitmap;

public:
	bool m_bCanRecycle;//�Ƿ��ܻ�����
	

public:
	//������
	void InitLeftUpCards(Cards cardsArr[], vector<int>& vtr, HINSTANCE hInstance);
	//��ʾ��
	void ShowLeftUpCards(HDC hMemDC);
	//�ܷ����
	bool CanOpenLeftUpCards(POINT pt);
	//����
	void OpenLeftUpCards();
	//������
	void CloseLeftUpCards();
	//���Ϸ�����
	bool CanGetLeftUpCards(POINT pt);
	//����
	void GetLeftUpCards(List* &pMouseLinkHead, List* &pMouseLinkRear);
	//��λ
	void RecoverLeftUpCard(List* &pMouseLinkHead, List* &pMouseLinkRear);
};

